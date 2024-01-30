#include "FBXManager.h"
#include "defines.h"
#include <vector>
#include "RenderManager.h"
#include "FBXStaticMesh.h"
#include "RenderableObjectManager.h"
#include "RenderableObject.h"
#include "MeshInstance.h"
#include "UOCEngine.h"

CFBXManager::CFBXManager()
{
	m_Manager=FbxManager::Create();
	FbxIOSettings *l_IOSettings=FbxIOSettings::Create(m_Manager, IOSROOT);
	m_Manager->SetIOSettings(l_IOSettings);
}

CFBXManager::~CFBXManager()
{
	if(m_Manager!=NULL)
	{
		m_Manager->Destroy();
		m_Manager=NULL;
	}
	for(size_t i=0; i<m_StaticMeshes.size(); ++i)
	{
		CHECKED_DELETE(m_StaticMeshes[i]);
	}
}

void CFBXManager::Load(const std::string &Filename)
{
	FbxImporter *l_FbxImporter;
	l_FbxImporter=FbxImporter::Create(m_Manager, Filename.c_str());
	l_FbxImporter->Initialize(Filename.c_str(), -1, m_Manager->GetIOSettings());
	FbxScene *l_FbxScene=FbxScene::Create(m_Manager, "tempName");
	l_FbxImporter->Import(l_FbxScene);
	FbxNode *l_RootNode=l_FbxScene->GetRootNode();
	ImportNode(l_RootNode);
	l_FbxImporter->Destroy();
}

void CFBXManager::ImportNode(FbxNode *Node)
{
	CRenderableObjectManager *l_RenderableObjectManager=CUOCEngine::GetEngine()->GetRenderableObjectManager();
	if(Node!=NULL)
	{
		for(int i=0; i<Node->GetChildCount(); ++i)
		{
			FbxNode *l_FbxNode=Node->GetChild(i);
			FbxMesh *l_FbxMesh=l_FbxNode->GetMesh();
			if(l_FbxMesh!=NULL)
			{
				CFBXStaticMesh *l_FBXStaticMesh=new CFBXStaticMesh();
				l_FBXStaticMesh->Generate(l_FbxNode, l_FbxMesh);
				m_StaticMeshes.push_back(l_FBXStaticMesh);
				
				const char *l_Name=l_FbxMesh->GetName();
				
				FbxDouble3 l_Position=l_FbxNode->LclTranslation.Get();
				FbxDouble3 l_Rotation=l_FbxNode->LclRotation.Get();
				FbxDouble3 l_Scale=l_FbxNode->LclScaling.Get();
				CRenderableObject *l_RenderableObject=new CMeshInstance(l_FBXStaticMesh);
				l_RenderableObject->SetPosition(XMFLOAT3(-(float)l_Position[0], (float)l_Position[1], -(float)l_Position[2]));
				l_RenderableObject->SetRotation(XMFLOAT3(DEG2RAD((float)-l_Rotation[0]), DEG2RAD((float)l_Rotation[2]), DEG2RAD((float)l_Rotation[1])));
				l_RenderableObject->SetScale(XMFLOAT3((float)l_Scale[0], (float)l_Scale[1], (float)l_Scale[2]));
				l_RenderableObjectManager->AddRenderableObject(l_RenderableObject);
			}
			ImportNode(l_FbxNode);
		}
	}
}
