#include "PhysicsManager.h"
#include "defines.h"
#include <assert.h>
#include <string>

#define UOC_USE_VISUAL_DEBUGGER

PxDefaultErrorCallback CPhysicsManager::m_DefaultErrorCallback;
PxDefaultAllocator CPhysicsManager::m_DefaultAllocatorCallback;

static PxFilterFlags SampleBridgesFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	return PxFilterFlags();
}

CPhysicsManager::CPhysicsManager() :
	//TO DO : Inicializar la variable miembro m_Foundation a NULL
	m_Foundation{ NULL },
	//TO DO : Inicializar la variable miembro m_Physics a NULL
	m_Physics{ NULL },
	//TO DO : Inicializar la variable miembro m_Cooking a NULL
	m_Cooking{ NULL },
	//TO DO : Inicializar la variable miembro m_Scene a NULL
	m_Scene{ NULL },
	//TO DO : Inicializar la variable miembro m_DefaultMaterial a NULL
	m_DefaultMaterial{ NULL },
	//TO DO : Inicializar la variable miembro m_CPUDispatcher a NULL
	m_CPUDispatcher{ NULL },
	//TO DO : Inicializar la variable miembro m_ControllerManager a NULL
	m_ControllerManager{ NULL }
{
}

CPhysicsManager::~CPhysicsManager()
{
	//TO DO : Llamar al método Destroy
	Destroy();
}

void CPhysicsManager::Init()
{
	//INFO: Este método inicializa la librería de física Physx
	m_Foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
	assert(m_Foundation != NULL);

	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true);
	assert(m_Physics != NULL);
	PxTolerancesScale l_Scale;

	//INFO: Inicializa la cooking que nos va a permitir cocinar las mallas para poder generar mallas de triángulos
	m_Cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_Foundation, PxCookingParams(l_Scale));
	assert(m_Cooking != NULL);

	bool l_ExtensionsInitialized = PxInitExtensions(*m_Physics, NULL);
	assert(l_ExtensionsInitialized);

	PxU32 l_GroupCollisionFlags[32];

	for (unsigned i = 0; i < 32; ++i)
		l_GroupCollisionFlags[i] = 0xffffffff;
	m_DefaultMaterial = m_Physics->createMaterial(0.5f, 0.5f, 0.1f);

	int l_NbThreads = 2;

	//INFO: Inicializa la escena de física
	PxSceneDesc l_SceneDesc(m_Physics->getTolerancesScale());
	l_SceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	l_SceneDesc.filterShader = SampleBridgesFilterShader;

	if (!l_SceneDesc.cpuDispatcher)
	{
		m_CPUDispatcher = PxDefaultCpuDispatcherCreate(l_NbThreads);
		l_SceneDesc.cpuDispatcher = m_CPUDispatcher;
	}

	m_Scene = m_Physics->createScene(l_SceneDesc);

	//INFO: Inicializa el mánager de controladores de Physx
	m_ControllerManager = PxCreateControllerManager(*m_Scene);
}

void CPhysicsManager::Destroy()
{
	//TO DO : Destruir la variable miembro m_ControllerManager utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_ControllerManager);
	//TO DO : Destruir la variable miembro m_CPUDispatcher utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_CPUDispatcher);
	//TO DO : Destruir la variable miembro m_Scene utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_Scene);
	//TO DO : Destruir la variable miembro m_Cooking utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_Cooking);
	//TO DO : Cerrar las extensiones de PhyX utilizando la función de la librería de Physx PxCloseExtensions
	PxCloseExtensions();
	//TO DO : Destruir la variable miembro m_Physics utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_Physics);
	//TO DO : Destruir la variable miembro m_Foundation utilizando la macro CHECKED_PX_RELEASE
	CHECKED_PX_RELEASE(m_Foundation);
}

PxTriangleMesh* CPhysicsManager::CreateTriangleMesh(void* Vertexs, unsigned int* Indices, unsigned short NumVertexs, unsigned short FacesCount, unsigned int VertexStride)
{
	//INFO: Crea una malla de triángulos física a partir de los vértices e índices de una malla geométrica de triángulos
	PxTriangleMeshDesc l_MeshDesc;
	l_MeshDesc.points.count = NumVertexs;
	l_MeshDesc.points.stride = VertexStride;
	l_MeshDesc.points.data = Vertexs;

	l_MeshDesc.triangles.count = FacesCount;
	l_MeshDesc.triangles.stride = 3 * sizeof(unsigned int);
	l_MeshDesc.triangles.data = Indices;

	PxDefaultMemoryOutputStream l_WriteBuffer;
	bool l_Status = m_Cooking->cookTriangleMesh(l_MeshDesc, l_WriteBuffer);
	if (!l_Status)
		return NULL;

	PxDefaultMemoryInputData l_ReadBuffer(l_WriteBuffer.getData(), l_WriteBuffer.getSize());
	return m_Physics->createTriangleMesh(l_ReadBuffer);
}

PxRigidStatic* CPhysicsManager::CreateRigidStatic(physx::PxTriangleMesh* TriangleMesh, const PxVec3& Position)
{
	//INFO: Crea un objeto rígido estático a partir de una malla de triángulos con el que podemos colisionar
	PxRigidStatic* l_Actor = m_Physics->createRigidStatic(PxTransform(Position));
	PxMeshScale l_MeshScale;
	PxShape* l_Shape = l_Actor->createShape(PxTriangleMeshGeometry(TriangleMesh, l_MeshScale), *m_DefaultMaterial);
	PxFilterData l_FilterData;
	l_FilterData.word0 = SCENARY;
	l_Shape->setQueryFilterData(l_FilterData);
	m_Scene->addActor(*l_Actor);
	return l_Actor;
}

PxRigidDynamic* CPhysicsManager::CreateRigidDynamic(float Radius, const PxVec3& Position)
{
	PxRigidDynamic* l_Actor{ m_Physics->createRigidDynamic(PxTransform(Position)) };
	l_Actor->setMass(PxReal{ 0.1f });
	l_Actor->setContactReportThreshold(PxReal{ 0.0f });
	l_Actor->setMaxContactImpulse(PxReal{ 10.0f });
	l_Actor->setMassSpaceInertiaTensor(PxVec3{ 1.0f });

	PxMaterial* l_SphereMaterial{ m_Physics->createMaterial(0.1f, 0.3f, 0.9f) };
	PxShape* l_Shape{ l_Actor->createShape(PxSphereGeometry{ Radius }, *l_SphereMaterial) };
	
	PxFilterData l_FilterData;
	l_FilterData.word0 = SCENARY;
	l_Shape->setQueryFilterData(l_FilterData);

	l_Actor->wakeUp();
	m_Scene->addActor(*l_Actor);

	return l_Actor;
}

void CPhysicsManager::Update(float ElapsedTime)
{
	//TO DO : Simular la escena utilizando el método simulate de la variable miembro m_Scene pasando el ElapsedTime
	m_Scene->simulate(ElapsedTime);
	//TO DO : Hacer un fetch de los resultados utilizando el método fetchResults de la variable miembro m_Scene pasando un true como parámetro al block
	PxU32* l_ErrorState{};
	const bool _ = m_Scene->fetchResults(true, l_ErrorState);
}

PxController* CPhysicsManager::CreateCharacterController(const XMFLOAT3& Position, float Height, float Radius, float StepOffset, float SlopeLimitInRadians, TPhysicsGroup PhysicsGroup)
{
	//INFO: Crea un character controller definido por una cápsula según las propiedades de altura, radio, stepOffset, slopeLimit y el grupo físico al que pertenece el controlador
	PxCapsuleControllerDesc l_Desc;
	l_Desc.height = Height;
	l_Desc.radius = Radius;
	l_Desc.slopeLimit = SlopeLimitInRadians;
	l_Desc.stepOffset = StepOffset;
	l_Desc.material = m_DefaultMaterial;
	l_Desc.position = PxExtendedVec3(Position.x, Position.y, Position.z);

	PxController* l_Controller = m_ControllerManager->createController(l_Desc);
	PxShape* l_Shapes = NULL;
	int l_ShapesCount = l_Controller->getActor()->getNbShapes();
	l_Controller->getActor()->getShapes(&l_Shapes, l_ShapesCount, 0);
	PxFilterData l_FilterData;
	l_FilterData.word0 = PhysicsGroup;
	for (int i = 0; i < l_ShapesCount; ++i)
		l_Shapes[i].setQueryFilterData(l_FilterData);
	assert(l_Controller != NULL);
	return l_Controller;
}

bool CPhysicsManager::TestRaycast(const XMFLOAT3& Origin, const XMFLOAT3& Destiny, unsigned short PhysicsGroupFilterMask, XMFLOAT3& OutPosition, void** OutUserData)
{
	//INFO: Este método nos permite comprobar si un rayo definido por un origen y un punto de destino colisiona con la escena
	XMVECTOR l_DirectionVector = XMLoadFloat3(&Destiny) - XMLoadFloat3(&Origin);
	l_DirectionVector = XMVector3Normalize(l_DirectionVector);
	XMFLOAT3 l_Direction = XMFLOAT3(l_DirectionVector.vector4_f32[0], l_DirectionVector.vector4_f32[1], l_DirectionVector.vector4_f32[2]);
	float l_Distance = LENGTH(Origin, Destiny);
	return TestRaycast(Origin, l_Direction, l_Distance, PhysicsGroupFilterMask, OutPosition, OutUserData);
}

bool CPhysicsManager::TestRaycast(const XMFLOAT3& Origin, const XMFLOAT3& Direction, float Distance, unsigned short PhysicsGroupFilterMask, XMFLOAT3& OutPosition, void** OutUserData)
{
	//INFO: Este método nos permite comprobar si un rayo definido por un origen y una dirección colisiona con la escena
	PxVec3 l_Origin(Origin.x, Origin.y, Origin.z);
	PxVec3 l_Direction(Direction.x, Direction.y, Direction.z);

	PxRaycastBuffer l_Hit;
	PxQueryFilterData l_Filter(PxQueryFlag::eSTATIC);

	PxQueryFilterData l_QueryFilterData;
	l_QueryFilterData.data.word0 = PhysicsGroupFilterMask;
	if (m_Scene->raycast(l_Origin, l_Direction, Distance, l_Hit, PxHitFlag::eDEFAULT, l_Filter))
	{
		PxRaycastHit l_HitInfo = l_Hit.getTouch(0);
		*OutUserData = l_HitInfo.actor->userData;
		float l_Distance = l_HitInfo.distance;
		OutPosition = XMFLOAT3(l_HitInfo.position.x, l_HitInfo.position.y, l_HitInfo.position.z);
		return true;
	}
	else
		return false;
}
