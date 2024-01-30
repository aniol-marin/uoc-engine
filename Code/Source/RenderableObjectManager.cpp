#include "RenderableObjectManager.h"
#include "RenderableObject.h"
#include "defines.h"
#include "AnimatedInstanceModel.h"
#include "UOCEngine.h"
#include "RenderManager.h"

CRenderableObjectManager::CRenderableObjectManager()
{
}

CRenderableObjectManager::~CRenderableObjectManager()
{
	for(size_t i=0; i<m_RenderableObjects.size(); ++i)
	{
		CHECKED_DELETE(m_RenderableObjects[i]);
	}
}

void CRenderableObjectManager::Update(float ElapsedTime)
{
	for(size_t i=0; i<m_RenderableObjects.size(); ++i)
		m_RenderableObjects[i]->Update(ElapsedTime);
}

void CRenderableObjectManager::Render(ID3D11DeviceContext *DeviceContext)
{
	for(size_t i=0; i<m_RenderableObjects.size(); ++i)
		m_RenderableObjects[i]->Render(DeviceContext);
}

void CRenderableObjectManager::AddRenderableObject(CRenderableObject *RenderableObject)
{
	m_RenderableObjects.push_back(RenderableObject);
}

void CRenderableObjectManager::AddAnimatedModel(CAnimatedCoreModel *AnimatedCoreModel, const XMFLOAT3 &Position, const XMFLOAT3 &Rotation, const XMFLOAT3 &Scale)
{
	CAnimatedInstanceModel *l_AnimatedInstanceModel = new CAnimatedInstanceModel;
	l_AnimatedInstanceModel->Initialize(AnimatedCoreModel);
	l_AnimatedInstanceModel->InitD3D(CUOCEngine::GetEngine()->GetRenderManager()->GetDevice());
	l_AnimatedInstanceModel->SetPosition(Position);
	l_AnimatedInstanceModel->SetRotation(Rotation);
	l_AnimatedInstanceModel->SetScale(Scale);
	AddRenderableObject(l_AnimatedInstanceModel);
}
