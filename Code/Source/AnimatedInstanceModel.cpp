#include "AnimatedCoreModel.h"
#include "ApplicationDX.h"
#include "EffectManager.h"
#include "RenderableVertexs.h"
#include "AnimatedInstanceModel.h"
#include "cal3d/cal3d.h"
#include "defines.h"
#include "TextureManager.h"
#include <vector>
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"

CAnimatedInstanceModel::CAnimatedInstanceModel()
: m_AnimatedCoreModel(NULL)
, m_CalModel(NULL)
, m_CurrentAnimationId(-1)
, m_CurrentCycle(-1)
, m_NumVertices(0)
, m_NumFaces(0)
, m_CurrentAnimationTime(0.0f)
, m_RenderableVertexs(NULL)
, m_Effect(NULL)
{
}

CAnimatedInstanceModel::~CAnimatedInstanceModel()
{
	Destroy();
}

void CAnimatedInstanceModel::Render(ID3D11DeviceContext *DeviceContext)
{
	CEffectManager *l_EffectManager=CUOCEngine::GetEngine()->GetEffectManager();
	CEffectManager::m_ObjectConstantBufferParameters.m_World=XMMatrixTranspose(GetTransform());
	l_EffectManager->SetObjectConstantBuffer(DeviceContext);

	for(int hardwareMeshId=0;hardwareMeshId<m_CalHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
	{
		m_TextureList[hardwareMeshId]->Activate(DeviceContext, 0);
		m_CalHardwareModel->selectHardwareMesh(hardwareMeshId);
		XMMATRIX l_Transformations[MAXBONES];
		for(int l_BoneId=0; l_BoneId<m_CalHardwareModel->getBoneCount(); ++l_BoneId)
		{	
			XMVECTOR l_Quaternion=XMLoadFloat4((const XMFLOAT4 *)&m_CalHardwareModel->getRotationBoneSpace(l_BoneId, m_CalModel->getSkeleton()).x);
			l_Transformations[l_BoneId]=DirectX::XMMatrixRotationQuaternion(l_Quaternion);
			CalVector translationBoneSpace = m_CalHardwareModel->getTranslationBoneSpace(l_BoneId, m_CalModel->getSkeleton());
			l_Transformations[l_BoneId]._14=translationBoneSpace.x;
			l_Transformations[l_BoneId]._24=translationBoneSpace.y;
			l_Transformations[l_BoneId]._34=translationBoneSpace.z;
			l_Transformations[l_BoneId]=XMMatrixTranspose(l_Transformations[l_BoneId]);
		}
		memcpy(&CEffectManager::m_AnimatedModelConstantBufferParameters.m_Bones, l_Transformations, MAXBONES*sizeof(float)*4*4);
		l_EffectManager->SetAnimatedModelConstantBuffer(DeviceContext);
		m_RenderableVertexs->DrawIndexed(DeviceContext, m_Effect, m_CalHardwareModel->getFaceCount()*3, m_CalHardwareModel->getStartIndex(), m_CalHardwareModel->getBaseVertexIndex());
	}
}

void CAnimatedInstanceModel::Update(float ElapsedTime)
{
	m_CalModel->update(ElapsedTime);
	m_CurrentAnimationTime+=ElapsedTime;
	if(m_CurrentAnimationId!=-1 && m_CalModel->getCoreModel()->getCoreAnimation(m_CurrentAnimationId)->getDuration()<m_CurrentAnimationTime)
	{
		m_CurrentAnimationTime=0.0f;
		m_CurrentAnimationId=-1;
	}
}

void CAnimatedInstanceModel::Initialize(CAnimatedCoreModel *AnimatedCoreModel)
{
	m_AnimatedCoreModel=AnimatedCoreModel;
	m_CalModel=new CalModel(m_AnimatedCoreModel->GetCoreModel());
	m_CalHardwareModel=new CalHardwareModel(m_AnimatedCoreModel->GetCoreModel());
	int l_MeshId;
	for(l_MeshId=0; l_MeshId<m_AnimatedCoreModel->GetCoreModel()->getCoreMeshCount(); l_MeshId++)
		m_CalModel->attachMesh(l_MeshId);
	BlendCycle(0,0);
	Update(0.0f);
}

void CAnimatedInstanceModel::InitD3D(ID3D11Device *Device)
{
	m_Effect=CUOCEngine::GetEngine()->GetEffectManager()->GetEffect(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX::GetVertexType());
	LoadVertexBuffer(Device);
	LoadTexture(Device);
}

void CAnimatedInstanceModel::LoadTexture(ID3D11Device *Device)
{
	CTextureManager *l_TM=CUOCEngine::GetEngine()->GetTextureManager();
	for(size_t i=0; i<m_AnimatedCoreModel->GetNumTextures(); ++i)
		m_TextureList.push_back(l_TM->LoadTexture(Device, m_AnimatedCoreModel->GetTextureName(i)));
}

void CAnimatedInstanceModel::Destroy()
{
	CHECKED_DELETE(m_RenderableVertexs);
	CHECKED_DELETE(m_CalHardwareModel);
	CHECKED_DELETE(m_CalModel);
}

void CAnimatedInstanceModel::ExecuteAction(int Id, float Time)
{
	m_CurrentAnimationTime=0.0f;
	m_CurrentAnimationId=Id;
	assert(Id!=-1);
	m_CalModel->getMixer()->executeAction(Id, Time, 0.0f, 1.0f, false );
}

void CAnimatedInstanceModel::BlendCycle(int Id, float Time)
{
	assert(Id!=-1);
	if(m_CurrentCycle!=-1)
		m_CalModel->getMixer()->clearCycle(m_CurrentCycle,Time);	
	m_CalModel->getMixer()->blendCycle(Id, 1.0f, Time);
	m_CurrentCycle=Id;
}

void CAnimatedInstanceModel::ClearCycle(float Time)
{
	m_CalModel->getMixer()->clearCycle(m_CurrentCycle,Time);
}

int CAnimatedInstanceModel::GetCurrentCycle() const
{
	return m_CurrentCycle;
}

int CAnimatedInstanceModel::GetAnimationId() const
{
	return m_CurrentAnimationId;
}

bool CAnimatedInstanceModel::LoadVertexBuffer(ID3D11Device *Device)
{
	CalRenderer *pCalRenderer;
	int meshCount;
	int meshId;
	int submeshId;

	m_NumVertices=0;
	m_NumFaces=0;
	pCalRenderer = m_CalModel->getRenderer();
	meshCount = pCalRenderer->getMeshCount();
	for(meshId=0; meshId<meshCount; ++meshId)
	{
		int submeshCount;
		submeshCount = pCalRenderer->getSubmeshCount(meshId);
		for(submeshId=0; submeshId<submeshCount; ++submeshId)
		{		
			if(pCalRenderer->selectMeshSubmesh(meshId, submeshId))
			{
				m_NumFaces=m_NumFaces+pCalRenderer->getFaceCount();
				m_NumVertices=m_NumVertices+pCalRenderer->getVertexCount();
			}
		}
	}

	UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX *l_Vertexs=(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX *)malloc(m_NumVertices*3*sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	CalIndex *l_Faces=(CalIndex *)malloc(m_NumFaces*3*sizeof(CalIndex));

	m_CalHardwareModel->setVertexBuffer((char*)l_Vertexs, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	m_CalHardwareModel->setWeightBuffer(((char*)l_Vertexs) + 12, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	m_CalHardwareModel->setMatrixIndexBuffer(((char*)l_Vertexs) + 28, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	m_CalHardwareModel->setNormalBuffer(((char*)l_Vertexs)+44, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	m_CalHardwareModel->setTextureCoordNum(1);
	m_CalHardwareModel->setTextureCoordBuffer(0, ((char*)l_Vertexs)+56, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	m_CalHardwareModel->setIndexBuffer(l_Faces);

	m_CalHardwareModel->load( 0, 0, MAXBONES);

	m_NumFaces=m_CalHardwareModel->getTotalFaceCount();
	m_NumVertices=m_CalHardwareModel->getTotalVertexCount();

	if(sizeof(CalIndex)==2)
		m_RenderableVertexs=new CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(Device, l_Vertexs, m_NumVertices, l_Faces, m_NumFaces*3);
	else
		m_RenderableVertexs=new CTriangleListRenderableIndexed32Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(Device, l_Vertexs, m_NumVertices, l_Faces, m_NumFaces*3);
	free(l_Vertexs);
	free(l_Faces);

	return true;
}
