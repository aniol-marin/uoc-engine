#include "RenderManager.h"

CRenderManager::CRenderManager()
: m_D3DDevice(NULL)
, m_DeviceContext(NULL)
, m_SwapChain(NULL)
, m_RenderTargetView(NULL)
, m_DepthStencil(NULL)
, m_DepthStencilView(NULL)
, m_hWnd(NULL)
, m_BackgroundColor(0.0f, 0.0f, 1.0f, 1.0f)
, m_PaintSolid(true)
, m_DrawAxisGrid(true)
{

}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Destroy()
{
	if(m_DeviceContext)
		m_DeviceContext->ClearState();
	m_DeviceContext=NULL;
	CHECKED_RELEASE(m_WireframeRenderState);
	CHECKED_RELEASE(m_SolidRenderState);
	CHECKED_RELEASE(m_RenderTargetView);
	CHECKED_RELEASE(m_SwapChain);
	CHECKED_RELEASE(m_DeviceContext);
	CHECKED_RELEASE(m_D3DDevice);
}

void CRenderManager::Init(HWND hWnd, int Width, int Height)
{
	m_hWnd=hWnd;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

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

	if(FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_D3DDevice, NULL, &m_DeviceContext)))
	{
		return;
	}
	ID3D11Texture2D *pBackBuffer;
	if(FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return;
	HRESULT hr = m_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
	pBackBuffer->Release();
	if(FAILED(hr))
		return;

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
	if(FAILED(hr))
		return;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_D3DDevice->CreateDepthStencilView(m_DepthStencil, &descDSV, &m_DepthStencilView);
	if(FAILED(hr))
		return;

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)Width;
	vp.Height = (FLOAT)Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

	//RENDER STATES
	D3D11_RASTERIZER_DESC l_WireframeDesc;
	ZeroMemory(&l_WireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_WireframeDesc.FillMode=D3D11_FILL_WIREFRAME;
	l_WireframeDesc.CullMode=D3D11_CULL_FRONT;

	HRESULT l_HR=m_D3DDevice->CreateRasterizerState(&l_WireframeDesc, &m_WireframeRenderState);

	D3D11_RASTERIZER_DESC l_SolidDesc;
	ZeroMemory(&l_SolidDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_SolidDesc.FillMode=D3D11_FILL_SOLID;
	l_SolidDesc.CullMode=D3D11_CULL_FRONT;

	l_HR=m_D3DDevice->CreateRasterizerState(&l_SolidDesc, &m_SolidRenderState);
}

void CRenderManager::BeginRenderDX()
{
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, &m_BackgroundColor.x);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CRenderManager::EndRenderDX()
{
	m_SwapChain->Present(0, 0);
}

void CRenderManager::SetSolidRenderState(ID3D11DeviceContext *Device)
{
	Device->RSSetState(m_SolidRenderState);
}

void CRenderManager::SetWireframeRenderState(ID3D11DeviceContext *Device)
{
	Device->RSSetState(m_WireframeRenderState);
}