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
	std::vector<PxTriangleMesh *> &l_PxTriangleMeshes;
	//TO DO : Asignar en l_PxTriangleMeshes el resultado de la llamada al m�todo GetPxTriangleMeshes de la variable miembro m_StaticMesh
	//TO DO : Implementar el for para recorrer desde 0 hasta el n�mero de elementos que contiene el vector l_PxTriangleMeshes
	for ()
		//TO DO : Utilizar el m�todo CreateRigidStatic de la clase PhysicsManager que se encuentra en la clase singleton CUOCEngine pasando la malla de tri�ngulos que se encuentra en el vector seg�n el �ndice del for y la posici�n de la instancia m_Position
}

void CMeshInstance::Render(ID3D11DeviceContext *DeviceContext)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_World=XMMatrixTranspose(GetTransform());
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_StaticMesh->Render(DeviceContext);
}
