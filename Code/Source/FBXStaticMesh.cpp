#include "FBXStaticMesh.h"
#include "defines.h"
#include "RenderableVertexs.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include <functional>

CFBXStaticMesh::CFBXStaticMesh() :
	//TO DO : Inicializar la variable miembro m_Effect a NULL
	m_Effect{ nullptr },
	m_BBMax{},
	m_BBMin{},
	m_Position{},
	m_Radius{}
{
}

bool CFBXStaticMesh::Generate(FbxNode* Node, FbxMesh* Mesh)
{
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	ID3D11Device* l_Device = l_Engine->GetRenderManager()->GetDevice();

	const char* l_Name = Node->GetName();
	int l_MaterialCount = Node->GetMaterialCount();
	for (int i = 0; i < l_MaterialCount; ++i)
	{
		FbxSurfaceMaterial* l_FbxSurfaceMaterial = Node->GetMaterial(i);
		const char* l_MaterialName = l_FbxSurfaceMaterial->GetName();

		FbxProperty l_Property = l_FbxSurfaceMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		int lLayeredTextureCount = l_Property.GetSrcObjectCount<FbxLayeredTexture>();
		int lNbTextures = l_Property.GetSrcObjectCount<FbxTexture>();
		int l_TexturesCount = l_Property.GetSrcObjectCount<FbxTexture>();
		for (int j = 0; j < l_TexturesCount; j++)
		{
			const FbxFileTexture* l_FbxFileTexture = FbxCast<FbxFileTexture>(l_Property.GetSrcObject<FbxTexture>(j));
			const char* l_FileName = l_FbxFileTexture->GetFileName();
			CTexture* l_Texture = l_Engine->GetTextureManager()->LoadTexture(l_Device, l_FileName);
			m_Textures.push_back(l_Texture);
		}
	}

	FbxVector4* l_Vertexs = Mesh->GetControlPoints();
	FbxLayerElementArrayTemplate<FbxVector4>* l_Normals;
	FbxLayerElementArrayTemplate<FbxVector2>* l_TexCoords;

	bool l_Loaded = Mesh->GetNormals(&l_Normals);
	Mesh->GetTextureUV(&l_TexCoords, FbxLayerElement::eTextureDiffuse);
	FbxLayerElementArrayTemplate<int>* l_MaterialIndices;
	Mesh->GetMaterialIndices(&l_MaterialIndices);
	std::vector<std::vector<UOC_POSITION_NORMAL_TEXTURE_VERTEX>> l_FullVertexs;
	std::vector<std::vector<unsigned short>> l_Indices;

	auto l_Comparator = [](const FbxVector4& a, const FbxVector4& b) {
		return
			a.SquareLength() > b.SquareLength();
	};


	for (int i = 0; i < m_Textures.size(); ++i)
	{
		l_FullVertexs.push_back(std::vector<UOC_POSITION_NORMAL_TEXTURE_VERTEX>());
		l_Indices.push_back(std::vector<unsigned short>());
	}

	for (int l_MeshVertex = 0; l_MeshVertex < Mesh->GetPolygonCount(); ++l_MeshVertex)
	{
		int l_MaterialId = l_MaterialIndices->GetAt(l_MeshVertex);
		int l_PolygonVertexsCount = Mesh->GetPolygonSize(l_MeshVertex);
		std::map< FbxVector4, unsigned short, decltype(l_Comparator)> l_CachedVertices{};

		for (int l_SubPosition = 0; l_SubPosition < 3; ++l_SubPosition) {

			int l_MeshIndex = Mesh->GetPolygonVertex(l_MeshVertex, l_SubPosition);
			FbxVector4 l_Vertex = l_Vertexs[l_MeshIndex].mData;

			if (l_CachedVertices.contains(l_Vertex)) {
				l_Indices[l_MaterialId].push_back(l_CachedVertices[l_Vertex]);
			}
			else {
				FbxVector4 l_Normal = l_Normals->GetAt(l_MeshVertex * 3 + l_SubPosition);
				int l_TexCoordIndex = Mesh->GetTextureUVIndex(l_MeshVertex, l_SubPosition, FbxLayerElement::eTextureDiffuse);
				FbxVector2 l_TexCoord = l_TexCoords->GetAt(l_TexCoordIndex);
				UOC_POSITION_NORMAL_TEXTURE_VERTEX l_FullVertex(XMFLOAT3(-(float)l_Vertex.mData[0], (float)l_Vertex.mData[2], (float)l_Vertex.mData[1]), XMFLOAT3(-(float)l_Normal.mData[0], (float)l_Normal.mData[2], (float)l_Normal.mData[1]), XMFLOAT2((float)l_TexCoord.mData[0], 1.0f - (float)l_TexCoord.mData[1]));

				l_FullVertexs[l_MaterialId].push_back(l_FullVertex);
				unsigned short l_BufferIndex = (unsigned short)l_Indices[l_MaterialId].size();
				l_Indices[l_MaterialId].push_back(l_BufferIndex);
				l_CachedVertices.insert({ l_Vertex, l_BufferIndex });

				if (l_FullVertex.Position.x < m_BBMin.x || l_MeshVertex == 0)
					m_BBMin.x = l_FullVertex.Position.x;
				if (l_FullVertex.Position.y < m_BBMin.y || l_MeshVertex == 0)
					m_BBMin.y = l_FullVertex.Position.y;
				if (l_FullVertex.Position.z < m_BBMin.z || l_MeshVertex == 0)
					m_BBMin.z = l_FullVertex.Position.z;

				if (l_FullVertex.Position.x > m_BBMax.x || l_MeshVertex == 0)
					m_BBMax.x = l_FullVertex.Position.x;
				if (l_FullVertex.Position.y > m_BBMax.y || l_MeshVertex == 0)
					m_BBMax.y = l_FullVertex.Position.y;
				if (l_FullVertex.Position.z > m_BBMax.z || l_MeshVertex == 0)
					m_BBMax.z = l_FullVertex.Position.z;
			}
		}
	}

	m_Position = XMFLOAT3((m_BBMin.x + m_BBMax.x) / 2.0f, (m_BBMin.y + m_BBMax.y) / 2.0f, (m_BBMin.z + m_BBMax.z) / 2.0f);
	for (size_t i = 0; i < m_Textures.size(); ++i)
	{
		for (int j = 0; j < l_FullVertexs[i].size(); ++j)
		{
			float l_Radius = LENGTH(m_Position, l_FullVertexs[i][j].Position);
			if (l_Radius > m_Radius || (i == 0 && j == 0))
				m_Radius = l_Radius;
		}
	}
	for (size_t i = 0; i < m_Textures.size(); ++i)
	{
		CRenderableVertexs* l_RenderableVertexs = new CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_NORMAL_TEXTURE_VERTEX>(l_Device, &l_FullVertexs[i][0].Position.x, (unsigned int)l_FullVertexs[i].size(), &l_Indices[i][0], (unsigned int)l_Indices[i].size());
		m_RenderableVertexs.push_back(l_RenderableVertexs);
	}

	m_Effect = l_Engine->GetEffectManager()->GetEffect(UOC_POSITION_NORMAL_TEXTURE_VERTEX::GetVertexType());
	return true;
}

void CFBXStaticMesh::Render(ID3D11DeviceContext* DeviceContext)
{
	//TO DO : Recorrer el vector m_RenderableVertexs
	for (int i = 0; i < m_RenderableVertexs.size(); ++i) {
		//TO DO : Activar la textura utilizando el m�todo Activate que se encuentra en el vector de texturas seg�n el �ndice del for que hemos creado previamente en la etapa 0
		m_Textures[i]->Activate(DeviceContext, 0); //TODO check where to retrieve StageID from
		//TO DO : Renderizar la malla m_RenderableVertexs seg�n el �ndice del for utilizando el m�todo DrawIndexed pasando el efecto m_Effect
		m_RenderableVertexs[i]->DrawIndexed(DeviceContext, m_Effect);
	}
}

CFBXStaticMesh::~CFBXStaticMesh()
{
	//TO DO : Eliminar todos los elementos del vector de m_RenderableVertexs utilizando la macro CHECKED_DELETE
	for (CRenderableVertexs* l_Element : m_RenderableVertexs) {
		CHECKED_DELETE(l_Element);
	}
}

bool CFBXStaticMesh::IsInBoundingBox(const XMFLOAT3& Pos)
{
	//TO DO : Devolver true si la posici�n Pos est� dentro de la caja contenedora alineada a los ejes definida por las posiciones m_BBMin y m_BBMax
	return Pos.x > m_BBMin.x
		&& Pos.y > m_BBMin.y
		&& Pos.z > m_BBMin.z
		&& Pos.x < m_BBMax.x
		&& Pos.y < m_BBMax.y
		&& Pos.z < m_BBMax.z;
}
