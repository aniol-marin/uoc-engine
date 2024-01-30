#include "MeshInstance.h"
#include "FBXStaticMesh.h"
#include "EffectManager.h"
#include "UOCEngine.h"

CMeshInstance::CMeshInstance(CFBXStaticMesh *StaticMesh)
: CRenderableObject()
, m_StaticMesh(StaticMesh)
{
}

CMeshInstance::~CMeshInstance()
{
}

void CMeshInstance::Render(ID3D11DeviceContext *DeviceContext)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_World=XMMatrixTranspose(GetTransform());
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_StaticMesh->Render(DeviceContext);
}
