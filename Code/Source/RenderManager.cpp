#include "RenderManager.h"

CRenderManager::CRenderManager() :
	//TO DO : Inicializar la variable miembro m_D3DDevice a NULL
	m_D3DDevice{ nullptr },
	//TO DO : Inicializar la variable miembro m_DeviceContext a NULL
	m_DeviceContext{ nullptr },
	//TO DO : Inicializar la variable miembro m_SwapChain a NULL
	m_SwapChain{ nullptr },
	//TO DO : Inicializar la variable miembro m_RenderTargetView a NULL
	m_RenderTargetView{ nullptr },
	//TO DO : Inicializar la variable miembro m_DepthStencil a NULL
	m_DepthStencil{ nullptr },
	//TO DO : Inicializar la variable miembro m_DepthStencilView a NULL
	m_DepthStencilView{ nullptr },
	//TO DO : Inicializar la variable miembro m_hWnd a NULL
	m_hWnd{ nullptr },
	//TO DO : Inicializar la variable miembro m_BackgroundColor a (0.0f, 0.0f, 1.0f, 1.0f)
	m_BackgroundColor{ g_Blue },
	//TO DO : Inicializar la variable miembro m_PaintSolid a true
	m_PaintSolid{ true },
	//TO DO : Inicializar la variable miembro m_DrawAxisGrid a true
	m_DrawAxisGrid{ true },
	m_SolidRenderState{ nullptr },
	m_WireframeRenderState{ nullptr }
{

}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Destroy()
{
	//TO DO : Si la variable miembro m_DeviceContext es diferente de NULL llamar al m�todo ClearState de la variable miembro m_DeviceContext
	if (m_DeviceContext) {
		m_DeviceContext->ClearState();
	}
	//TO DO : Asignar el valor NULL A m_DeviceContext 
	m_DeviceContext = nullptr;
	//TO DO : Destruir el objeto m_WireframeRenderState utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_WireframeRenderState);
	//TO DO : Destruir el objeto m_SolidRenderState utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_SolidRenderState);
	//TO DO : Destruir el objeto m_RenderTargetView utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_RenderTargetView);
	//TO DO : Destruir el objeto m_SwapChain utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_SwapChain);
	//TO DO : Destruir el objeto m_DeviceContext utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_DeviceContext);
	//TO DO : Destruir el objeto m_D3DDevice utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_D3DDevice);
}

void CRenderManager::Init(HWND hWnd, int Width, int Height)
{
	m_hWnd = hWnd;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//NOTA : Creamos el descriptor de DirectX que inicializa el tipo de buffer que utilizamos y el modo en ventana o pantalla completa que utilizamos para inicializar el Device
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	//NOTA : Creamos el Device y el DeviceContext de DirectX 11 seg�n el descriptor creado previamente en modo HARDWARE
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_D3DDevice, NULL, &m_DeviceContext)))
	{
		return;
	}
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return;

	//NOTA : Creamos el RenderTarget para el backbuffer
	HRESULT hr = m_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return;

	//NOTA : Creamos el descriptor para el ZBuffer
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = Width;
	descDepth.Height = Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_D3DDevice->CreateTexture2D(&descDepth, NULL, &m_DepthStencil);
	if (FAILED(hr))
		return;

	//NOTA : Creamos el DepthStencilView de DirectX 11 para el ZBuffer
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_D3DDevice->CreateDepthStencilView(m_DepthStencil, &descDSV, &m_DepthStencilView);
	if (FAILED(hr))
		return;

	//NOTA : Establecemos los RenderTargets del m_RenderTargetView y el m_DepthStencilView
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//NOTA : Creamos el viewport con el que pintamos en pantalla
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)Width;
	vp.Height = (FLOAT)Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

	//NOTA : Creamos el Rasterizer State para el modo wireframe utilizando el m�todo de DirectX CreateRasterizerState
	D3D11_RASTERIZER_DESC l_WireframeDesc;
	ZeroMemory(&l_WireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_WireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	l_WireframeDesc.CullMode = D3D11_CULL_FRONT;

	HRESULT l_HR = m_D3DDevice->CreateRasterizerState(&l_WireframeDesc, &m_WireframeRenderState);

	//NOTA : Creamos el Rasterizer State para el modo s�lido utilizando el m�todo de DirectX CreateRasterizerState
	D3D11_RASTERIZER_DESC l_SolidDesc;
	ZeroMemory(&l_SolidDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_SolidDesc.FillMode = D3D11_FILL_SOLID;
	l_SolidDesc.CullMode = D3D11_CULL_FRONT;

	l_HR = m_D3DDevice->CreateRasterizerState(&l_SolidDesc, &m_SolidRenderState);
}

void CRenderManager::BeginRenderDX()
{
	//TO DO : Llamar al m�todo ClearRenderTargetView de la variable miembro m_DeviceContext pas�ndole el m_RenderTargetView y el color m_BackgroundColor para que limpie la pantalla
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, (FLOAT*)GetBackgroundColorAddress());
	//TO DO : Llamar al m�todo ClearDepthStencilView de la variable miembro m_DeviceContext pas�ndole el m_DepthStencilView y los par�metros D3D11_CLEAR_DEPTH, 1.0f, 0 para que limpie el ZBuffer
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CRenderManager::EndRenderDX()
{
	//TO DO : Llamar al m�todo Present de la variable miembro m_SwapChain pas�ndole como par�metros 0, 0 para que haga el swap de backbuffer al frontbuffer
	m_SwapChain->Present(0, 0);
}

void CRenderManager::SetSolidRenderState(ID3D11DeviceContext* Device)
{
	//TO DO : Establecer el estado de render state m_SolidRenderState utilizando el m�todo del Device RSSetState
	Device->RSSetState(m_SolidRenderState);
}

void CRenderManager::SetWireframeRenderState(ID3D11DeviceContext* Device)
{
	//TO DO : Establecer el estado de render state m_WireframeRenderState utilizando el m�todo del Device RSSetState
	Device->RSSetState(m_WireframeRenderState);
}