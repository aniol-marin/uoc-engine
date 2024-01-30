#include "TextureManager.h"
#include <assert.h>
#include "defines.h"
#include "DDSTextureLoader11.h"

CTexture::CTexture() :
	//TO DO : Inicializar la variable miembro m_Texture a NULL
	m_Texture{ nullptr },
	//TO DO : Inicializar la variable miembro m_SamplerState a NULL
	m_SamplerState{ nullptr }
{
}

CTexture::~CTexture()
{
	//TO DO : Destruir la variable miembro m_SamplerState utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_SamplerState);
	//TO DO : Destruir la variable miembro m_Texture utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_Texture);
}

bool CTexture::Load(ID3D11Device* Device, const std::string& Filename)
{
	//INFO : Este método carga una textura de fichero Filename en la variable m_Texture 
	HRESULT l_HR = DirectX::CreateDDSTextureFromFile(Device, str2wstr(Filename.substr(0, Filename.length() - 4) + ".dds").c_str(), NULL, &m_Texture);

	//INFO : El siguiente fragmento de código construye una descripción del Sampler State 
	D3D11_SAMPLER_DESC l_SampDesc;
	ZeroMemory(&l_SampDesc, sizeof(l_SampDesc));
	l_SampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	l_SampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	l_SampDesc.MinLOD = 0;
	l_SampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//INFO : La siguiente llamada crea el sampler state que utilizaremos después para poder pintar una malla de triángulos con texturas
	l_HR = Device->CreateSamplerState(&l_SampDesc, &m_SamplerState);
	return !FAILED(l_HR);
}

void CTexture::Activate(ID3D11DeviceContext* ImmediateContext, unsigned int StageId)
{
	//TO DO : Establecer el sampler state m_SamplerState en StageId utilizando el mï¿½todo PSSetSamplers de la instancia ImmediateContext
	ImmediateContext->PSSetSamplers(StageId, 1, &m_SamplerState);
	//TO DO : Establecer el resource de textura m_Texture en StageId utilizando el mï¿½todo PSSetShaderResources de la instancia ImmediateContext
	ImmediateContext->PSSetShaderResources(StageId, 1, &m_Texture);
}

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
	//TO DO : Llamar al mï¿½toco CleanUp
	CleanUp();
}

void CTextureManager::CleanUp()
{
	//TO DO : Recorrer el mapa m_TextureMap y eliminar todos los objetos second del mapa utilizando la macro CHECKED_DELETE
	for (auto& l_Pair : m_TextureMap) {
		CHECKED_DELETE(l_Pair.second);
	}
	//TO DO : Realizar un clear de la variable miembro m_TextureMap
	m_TextureMap.clear();
}

CTexture* CTextureManager::LoadTexture(ID3D11Device* Device, const std::string& Filename)
{
	CTexture* l_Texture{};

	//TO DO : Si la textura por nombre Filename existe en el mapa m_TextureMap, asignamos el valor del mapa segï¿½n Filename en l_Texture
	if (m_TextureMap.contains(Filename)) {
		l_Texture = m_TextureMap[Filename];
	}
	//TO DO : En caso contrario (TODO LOS TO DO DENTRO DEL ELSE)
	else {
		std::string l_Name;

		//TO DO: Extraemos el nombre del fichero sin path de Filename utilizando la funciï¿½n GetFilename
		GetFilename(Filename.c_str(), &l_Name);
		//TO DO: Creamos un string con PATH_TEXTURES mï¿½s el nombre del fichero sin path que hemos extraï¿½do en el TO DO anterior
		const std::string l_Path = PATH_TEXTURES + l_Name;
		//TO DO: Construye una textura y asignarla a la variable l_Texture
		l_Texture = new CTexture();
		//TO DO: Llamar al mï¿½todo Load pasï¿½ndole el nombre del fichero con path completo construï¿½do previamente
		l_Texture->Load(Device, l_Path);
		//TO DO: Insertar en el mapa m_TextureMap segï¿½n el nombre Filename la textura creada l_Texture
		m_TextureMap.insert({ l_Name, l_Texture });
	}

	return l_Texture;
}
