#ifndef PHYSICS_MANAGER_H_
#define PHYSICS_MANAGER_H_

#include <PxPhysicsAPI.h>
#include <geometry/PxTriangleMesh.h>

#include "defines.h"

using namespace physx;

enum TPhysicsGroup
{
	SCENARY = (1<<0),
	PLAYER = (1<<1),
	BOT = (1<<2)
};

class CPhysicsManager
{
private:
	static PxDefaultErrorCallback					m_DefaultErrorCallback;
	static PxDefaultAllocator						m_DefaultAllocatorCallback;
	PxFoundation									*m_Foundation;
	//PxProfileZoneManager							*m_ProfileZoneManager;
	PxPhysics										*m_Physics;
	PxCooking 										*m_Cooking;
	//PxVisualDebuggerConnection						*m_Connection;
	PxScene											*m_Scene;
	PxMaterial										*m_DefaultMaterial;
	PxDefaultCpuDispatcher							*m_CPUDispatcher;
	PxControllerManager								*m_ControllerManager;
public:
	CPhysicsManager();
	virtual ~CPhysicsManager();
	void Init();
	void Destroy();

	PxTriangleMesh * CreateTriangleMesh(void *Vertexs, unsigned int *Indices, unsigned short NumVertexs, unsigned short FacesCount, unsigned int VertexStride);
	void Update(float ElapsedTime);
	PxRigidStatic * CreateRigidStatic(physx::PxTriangleMesh *TriangleMesh, const PxVec3 &Position);
	PxController * CreateCharacterController(const XMFLOAT3 &Position, float Height, float Radius, float StepOffset, float SlopeLimitInRadians, TPhysicsGroup PhysicsGroup);
	bool TestRaycast(const XMFLOAT3 &Origin, const XMFLOAT3 &Destiny, unsigned short PhysicsGroupFilterMask, XMFLOAT3 &OutPosition, void **OutUserData);
	bool TestRaycast(const XMFLOAT3 &Origin, const XMFLOAT3 &Direction, float Distance, unsigned short PhysicsGroupFilterMask, XMFLOAT3 &OutPosition, void **OutUserData);
};

#endif
