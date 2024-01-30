#include "TextureManager.h"
#include <assert.h>
#include "defines.h"
#include "DDSTextureLoader11.h"

CTexture::CTexture()
	: m_Texture(NULL)
	, m_SamplerState(NULL)
{
}

CTexture::~CTexture()
{
	CHECKED_RELEASE(m_SamplerState);
	CHECKED_RELEASE(m_Texture);
}

bool CTexture::Load(ID3D11Device *Device, const std::string &Filename)
{
	HRESULT l_HR = DirectX::CreateDDSTextureFromFile(Device, str2wstr(Filename.substr(0, Filename.length() - 4) + ".dds").c_str(), NULL, &m_Texture);
	//HRESULT l_HR = DirectX::CreateDDSTextureFromFile(Device, str2wstr("Data/Models/Textures/flame2.dds").c_str(), NULL, &m_Texture);
	
	//return true;
	//HRESULT l_HR=D3DX11CreateShaderResourceViewFromFile( Device, Filename.c_str(), NULL, NULL, &m_Texture, NULL );

	D3D11_SAMPLER_DESC l_SampDesc;
	ZeroMemory(&l_SampDesc, sizeof(l_SampDesc));
	l_SampDesc.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	l_SampDesc.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.ComparisonFunc=D3D11_COMPARISON_NEVER;
	l_SampDesc.MinLOD=0;
	l_SampDesc.MaxLOD=D3D11_FLOAT32_MAX;
	l_HR=Device->CreateSamplerState(&l_SampDesc, &m_SamplerState);
	return !FAILED(l_HR);
}

void CTexture::Activate(ID3D11DeviceContext *ImmediateContext, unsigned int StageId)
{
	ImmediateContext->PSSetSamplers(StageId, 1, &m_SamplerState);
	ImmediateContext->PSSetShaderResources(StageId, 1, &m_Texture);
}

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
	CleanUp();
}

void CTextureManager::CleanUp()
{
	for(TTextureIterator it=m_TextureMap.begin();it!=m_TextureMap.end();++it)
	{
		CHECKED_DELETE(it->second);
	}
	m_TextureMap.clear();
}

CTexture *  CTextureManager::LoadTexture(ID3D11Device *Device, const std::string &Filename)
{
	CTexture * l_Texture=NULL;
	if(m_TextureMap.find(Filename)!=m_TextureMap.end())
		l_Texture=m_TextureMap[Filename];
	else
	{
		std::string l_FilenameWithoutPath, l_FilenameComplete;
		GetFilename(Filename.c_str(),&l_FilenameWithoutPath);

		l_FilenameComplete=PATH_TEXTURES;
		l_FilenameComplete+=l_FilenameWithoutPath;
		l_Texture=new CTexture;
		l_Texture->Load(Device, l_FilenameComplete);
		m_TextureMap[Filename]=l_Texture;
	}
	assert(l_Texture!=NULL);
	return l_Texture;
}
