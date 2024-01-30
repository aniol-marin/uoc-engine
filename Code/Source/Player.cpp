#include "UOCEngine.h"
#include "RenderManager.h"
#include "DebugRender.h"
#include "Player.h"
#include <assert.h>
#include <math.h>
#include "defines.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "FPSCameraController.h"
#include "EffectManager.h"
#include "PhysicsManager.h"

CPlayer::CPlayer(void)
	: m_Speed(10.0f)
	, m_FastSpeed(20.0f)
	, m_Position(0.0f, 1.75f, 0.0f)
	, m_VerticalSpeed(0.0f)
	, m_VerticalSpeedJump(8.0f)
{
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	m_FPSCameraController = (CFPSCameraController*)l_Engine->GetCameraManager()->GetCameraController("player");
	//TO DO : Crear un character controller utilizando el método CreateCharacterController de la clase PhysicsManager del motor l_Engine y asignarlo en la variable miembro m_Controller. Utilizamos los parámetros de posición m_Position, altura de 2.0f, radio de 0.5f, stepOffset 0.5f (tamaño del escalón que se puede subir), 45 grados en radianes para el slopeLimit (grado de pendientes que se puede subir), y del grupo físico PLAYER
	m_Controller = CUOCEngine::GetEngine()->GetPhysicsManager()->CreateCharacterController(m_Position, 2.0f, 0.5f, 0.5f, DEG2RAD(45), TPhysicsGroup::PLAYER);
	//TO DO : Asignar en el atributo userData del Actor del m_Controller este objeto (this)
	m_Controller->setUserData(this);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Move(float Strafe, float Forward, bool Fast, float ElapsedTime)
{
	XMFLOAT3 l_VectorMovement;
	float l_Yaw = m_FPSCameraController->GetYaw();
	l_VectorMovement.y = 0.0f;

	l_VectorMovement.x = Forward * (cos(l_Yaw)) + Strafe * (cos(l_Yaw + DEG2RAD(180.0f) * 0.5f));
	l_VectorMovement.z = Forward * (sin(l_Yaw)) + Strafe * (sin(l_Yaw + DEG2RAD(180.0f) * 0.5f));
	float l_Movement = (Fast ? m_FastSpeed : m_Speed);

	m_VerticalSpeed += (-9.81f) * ElapsedTime;
	/*DirectX::XMVECTORF32 l_Vector;
	l_Vector.v= XMLoadFloat3(&l_VectorMovement);*/
	XMVECTOR l_Vector = XMLoadFloat3(&l_VectorMovement);
	l_Vector = DirectX::XMVector3Normalize(l_Vector);
	l_Vector *= l_Movement * ElapsedTime;

	l_VectorMovement = XMFLOAT3(l_Vector.vector4_f32[0], l_Vector.vector4_f32[1], l_Vector.vector4_f32[2]);
	l_VectorMovement.y = m_VerticalSpeed * ElapsedTime;


	PxControllerFilters l_Filters(NULL, NULL, NULL);
	PxControllerCollisionFlags l_Flags;
	//TO DO : Llamar al método move del controlador m_Controller pasando el vector de movimiento l_VectorMovement, 0.01f de distancia mínima, el ElapsedTime, los filtros que se encuentran en la variable l_Filters y NULL como en el parámetro de obstáculos. Asignar el valor que devuelve en la variable local l_Flags
	l_Flags = m_Controller->move(PxVec3(l_VectorMovement.x, l_VectorMovement.y, l_VectorMovement.z), 0.01f, ElapsedTime, l_Filters, NULL);
	//TO DO : Realizar una máscara binaria de l_Flags con PxControllerCollisionFlag::eCOLLISION_DOWN y con PxControllerCollisionFlag::eCOLLISION_UP, para comprobar si ha colisionado por arriba o ha colisionado por abajo, al comprobar si colisiona ha colisionado por arriba hay que mirar que la velocidad vertical m_VerticalSpeed sea superior a 0, para comprobar que está intentando subir 
	if ((l_Flags & PxControllerCollisionFlag::eCOLLISION_DOWN) == PxControllerCollisionFlag::eCOLLISION_DOWN || (((l_Flags & PxControllerCollisionFlag::eCOLLISION_UP) == PxControllerCollisionFlag::eCOLLISION_UP) && m_VerticalSpeed > 0))
		//TO DO : En caso de que colisione por arriba o por abajo establecer la variable miembro m_VerticalSpeed el valor de 0
		m_VerticalSpeed = 0;

	//TO DO : Asignar en la posición l_Position de tipo PxExtendedVec3 la posición del controlador utilizando el método getPosition de m_Controller
	PxExtendedVec3 l_Position = m_Controller->getPosition();
	//TO DO : Asignar en la posición m_Position de tipo XMFLOAT3 la posición que hemos recogido anteriormente en l_Position
	m_Position = XMFLOAT3(l_Position.x, l_Position.y, l_Position.z);

	m_FPSCameraController->SetPosition(m_Position);
}

void CPlayer::Update(float ElapsedTime)
{
	CInputManager* l_InputManager = CUOCEngine::GetEngine()->GetInputManager();
	CKeyboardInput* l_KeyboardInput = l_InputManager->GetKeyboard();
	CMouseInput* l_MouseInput = l_InputManager->GetMouse();

	m_FPSCameraController->AddYaw(-l_MouseInput->GetMovementX() * ElapsedTime);
	m_FPSCameraController->AddPitch(l_MouseInput->GetMovementY() * ElapsedTime);

	float l_Forward = 0.0f;
	float l_Strafe = 0.0f;
	bool l_MoveFast = l_KeyboardInput->IsKeyPressed(DIK_LSHIFT);

	if (l_KeyboardInput->IsKeyPressed(DIK_W))
		l_Forward = 1.0f;
	if (l_KeyboardInput->IsKeyPressed(DIK_S))
		l_Forward = -1.0f;
	if (l_KeyboardInput->IsKeyPressed(DIK_A))
		l_Strafe = -1.0f;
	if (l_KeyboardInput->IsKeyPressed(DIK_D))
		l_Strafe = 1.0f;

	if (l_KeyboardInput->IsKeyPressed(DIK_SPACE) && m_VerticalSpeed == 0.0f)
		Jump();

	Move(l_Strafe, l_Forward, l_MoveFast, ElapsedTime);
}

void CPlayer::Jump()
{
	m_VerticalSpeed = m_VerticalSpeedJump;
}
