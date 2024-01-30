#include "EffectManager.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include <d3d11shader.h>

CSceneConstantBufferParameters CEffectManager::m_SceneConstantBufferParameters;
CObjectConstantBufferParameters CEffectManager::m_ObjectConstantBufferParameters;
CAnimatedModelConstantBufferParameters CEffectManager::m_AnimatedModelConstantBufferParameters;

CEffectManager::~CEffectManager()
{
	std::map<unsigned int, CEffect *>::iterator l_ItByUint;
	std::map<std::string, CEffect *>::iterator l_ItByString;

	CHECKED_RELEASE(m_SceneConstantBuffer);
	CHECKED_RELEASE(m_ObjectConstantBuffer);
	CHECKED_RELEASE(m_AnimatedModelConstantBuffer);

	for(std::map<unsigned int, CEffect *>::iterator it=m_EffectsByVertexType.begin(); it!=m_EffectsByVertexType.end(); ++it)
	{
		CHECKED_DELETE(it->second);
	}
	for(std::map<std::string, CEffect *>::iterator it=m_Effects.begin(); it!=m_Effects.end(); ++it)
	{
		CHECKED_DELETE(it->second);
	}
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	CEffect *l_Effect=(CEffect *)new CEffectTemplated<T>();
	l_Effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_EffectsByVertexType[T::GetVertexType()]=l_Effect;
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Name, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	CEffect *l_Effect=(CEffect *)new CEffectTemplated<T>();
	l_Effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_Effects[Name]=l_Effect;
}

CEffectManager::CEffectManager()
{
	ID3D11Device *l_Device=CUOCEngine::GetEngine()->GetRenderManager()->GetDevice();
	AddEffect<UOC_POSITION_COLOR_VERTEX>(l_Device, "./Data/Effects/DebugRender.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_TEXTURE_VERTEX>(l_Device, "./Data/Effects/UOC_POSITION_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_NORMAL_TEXTURE_VERTEX>(l_Device, "./Data/Effects/UOC_POSITION_NORMAL_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_COLOR_TEXTURE_VERTEX>(l_Device, "./Data/Effects/UOC_POSITION_COLOR_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(l_Device, "./Data/Effects/UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	
	CreateConstantBuffer(l_Device, sizeof(m_SceneConstantBufferParameters), &m_SceneConstantBuffer);
	CreateConstantBuffer(l_Device, sizeof(m_ObjectConstantBufferParameters), &m_ObjectConstantBuffer);
	CreateConstantBuffer(l_Device, sizeof(m_AnimatedModelConstantBufferParameters), &m_AnimatedModelConstantBuffer);
}

bool CEffectManager::CreateConstantBuffer(ID3D11Device *Device, UINT ConstantBufferSize, ID3D11Buffer **ConstantBuffer)
{
	D3D11_BUFFER_DESC l_BufferDescription;
	ZeroMemory(&l_BufferDescription, sizeof(l_BufferDescription));

	l_BufferDescription.Usage=D3D11_USAGE_DEFAULT;
	l_BufferDescription.ByteWidth=ConstantBufferSize;
	l_BufferDescription.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	l_BufferDescription.CPUAccessFlags=0;
	if(FAILED(Device->CreateBuffer(&l_BufferDescription, NULL, ConstantBuffer)))
		return false;

	return true;
}

void CEffectManager::SetConstantBuffer(ID3D11DeviceContext *DeviceContext, ID3D11Buffer *ConstantBuffer, void *Data, UINT IdSlot)
{
	DeviceContext->UpdateSubresource(ConstantBuffer, 0, NULL, Data, 0, 0);
	DeviceContext->VSSetConstantBuffers(IdSlot, 1, &ConstantBuffer);
	DeviceContext->PSSetConstantBuffers(IdSlot, 1, &ConstantBuffer);
}

void CEffectManager::SetSceneConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_SceneConstantBuffer, &m_SceneConstantBufferParameters, 0);
}

void CEffectManager::SetObjectConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_ObjectConstantBuffer, &m_ObjectConstantBufferParameters, 1);
}

void CEffectManager::SetAnimatedModelConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_AnimatedModelConstantBuffer, &m_AnimatedModelConstantBufferParameters, 2);
}

CEffect * CEffectManager::GetEffect(const std::string &Name)
{
	std::map<std::string, CEffect *>::iterator l_It=m_Effects.find(Name);
	if(l_It!=m_Effects.end())
		return l_It->second;
	return NULL;
}

CEffect * CEffectManager::GetEffect(unsigned int VertexType)
{
	std::map<unsigned int, CEffect *>::iterator l_It=m_EffectsByVertexType.find(VertexType);
	if(l_It!=m_EffectsByVertexType.end())
		return l_It->second;
	return NULL;
}

template<class T>
CEffectTemplated<T>::CEffectTemplated()
: m_VertexShader(NULL)
, m_PixelShader(NULL)
, m_VertexLayout(NULL)
{
}

template<class T>
CEffectTemplated<T>::~CEffectTemplated()
{
	CleanUp();
}

template<class T>
void CEffectTemplated<T>::CleanUp()
{
	CHECKED_RELEASE(m_VertexShader);
	CHECKED_RELEASE(m_PixelShader);
	CHECKED_RELEASE(m_VertexLayout);
}

template<class T>
bool CEffectTemplated<T>::Reload(ID3D11Device *Device)
{
	CleanUp();
	return Load(Device, m_Filename, m_PointEntryVS, m_ShaderModelVS, m_PointEntryPS, m_ShaderModelPS);
}

template<class T>
bool CEffectTemplated<T>::LoadShader(const std::string &Filename, const std::string &EntryPoint, const std::string &ShaderModel, ID3DBlob **BlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob= NULL;
	hr = D3DCompileFromFile(str2wstr(Filename).c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryPoint.c_str(), ShaderModel.c_str(), 	dwShaderFlags, 0, BlobOut, &pErrorBlob);
	
	if(FAILED(hr))
	{
		if(pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if(pErrorBlob)
			pErrorBlob->Release();
		return false;
	}
	if(pErrorBlob)
		pErrorBlob->Release();

	return true;
}

template<class T>
bool CEffectTemplated<T>::Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	m_Filename=Filename;
	m_PointEntryVS=PointEntryVS;
	m_ShaderModelVS=ShaderModelVS;
	m_PointEntryPS=PointEntryPS;
	m_ShaderModelPS=ShaderModelPS;

	ID3DBlob *l_VSBlob=NULL;
	bool l_Loaded=LoadShader(Filename, PointEntryVS, ShaderModelVS, &l_VSBlob);
	if(!l_Loaded)
		return false;
	HRESULT l_HR=Device->CreateVertexShader(l_VSBlob->GetBufferPointer(), l_VSBlob->GetBufferSize(), NULL, &m_VertexShader);
	if(FAILED(l_HR))
	{
		l_VSBlob->Release();
		return false;
	}
	l_Loaded=T::CreateInputLayout(Device, l_VSBlob, &m_VertexLayout);

	l_VSBlob->Release();

	if(!l_Loaded)
		return false;

	ID3DBlob *l_PSBlob=NULL;
	l_Loaded=LoadShader(Filename.c_str(), PointEntryPS.c_str(), ShaderModelPS.c_str(), &l_PSBlob);
	if(!l_Loaded)
		return false;

	l_HR=Device->CreatePixelShader(l_PSBlob->GetBufferPointer(), l_PSBlob->GetBufferSize(), NULL, &m_PixelShader);
	l_PSBlob->Release();

	return !FAILED(l_HR);
}
