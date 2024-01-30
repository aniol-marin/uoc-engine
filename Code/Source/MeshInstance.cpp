#include "MeshInstance.h"
#include "FBXStaticMesh.h"
#include "EffectManager.h"
#include "PhysicsManager.h"
#include "UOCEngine.h"

CMeshInstance::CMeshInstance(CFBXStaticMesh *StaticMesh)
: CRenderableObject()
, m_StaticMesh(StaticMesh)
{
}

CMeshInstance::~CMeshInstance()
{
}

void CMeshInstance::CreatePhysx()
{
	//TO DO : Asignar en l_PxTriangleMeshes el resultado de la llamada al método GetPxTriangleMeshes de la variable miembro m_StaticMesh
	std::vector<PxTriangleMesh*>& l_PxTriangleMeshes = m_StaticMesh->GetPxTriangleMeshes();
	//TO DO : Implementar el for para recorrer desde 0 hasta el número de elementos que contiene el vector l_PxTriangleMeshes
	CPhysicsManager* l_Manager = CUOCEngine::GetEngine()->GetPhysicsManager();
	PxVec3 l_Position = PxVec3(m_Position.x, m_Position.y, m_Position.z);
	for (int i = 0; i < l_PxTriangleMeshes.size(); ++i) {
		//TO DO : Utilizar el método CreateRigidStatic de la clase PhysicsManager que se encuentra en la clase singleton CUOCEngine pasando la malla de triángulos que se encuentra en el vector según el índice del for y la posición de la instancia m_Position
		l_Manager->CreateRigidStatic(l_PxTriangleMeshes[i], l_Position);
	}
}

void CMeshInstance::Render(ID3D11DeviceContext *DeviceContext)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_World=XMMatrixTranspose(GetTransform());
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_StaticMesh->Render(DeviceContext);
}
