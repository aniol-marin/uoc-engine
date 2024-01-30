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

constexpr float g_SpeedDefault{ 10.0f };
constexpr float g_FastSpeedDefault{ 20.0f };
constexpr XMFLOAT3 g_PositionDefault{ resize(1.75f, g_Up) };
constexpr float g_VerticalSpeedDefault{ 0.0f };
constexpr float g_VerticalSpeedJumpDefault{ 8.0f };
constexpr std::string_view g_PlayerController = "player";

CPlayer::CPlayer(void) :
	//TO DO : Inicializar la variable miembro m_Speed a 10.0f
	m_Speed{ g_SpeedDefault },
	//TO DO : Inicializar la variable miembro m_Position a (0.0f, 1.75f, 0.0f)
	m_Position{ g_PositionDefault },
	//TO DO : Inicializar la variable miembro m_FastSpeed a 20.0f
	m_FastSpeed{ g_FastSpeedDefault },
	//TO DO : Inicializar la variable miembro m_VerticalSpeed a 0.0f
	m_VerticalSpeed{ g_VerticalSpeedDefault },
	//TO DO : Inicializar la variable miembro m_VerticalSpeedJump a 8.0f
	m_VerticalSpeedJump{ g_VerticalSpeedJumpDefault }
{
	//TO DO : Asignar el controlador de c�mara en la variable m_FPSCameraController, para ello debemos pedirle al CameraManager de la clase CUOCEngine el controlador de c�mara que tiene por nombre "player"
	m_FPSCameraController = static_cast<CFPSCameraController*>(CUOCEngine::GetEngine()->GetCameraManager()->GetCameraController(g_PlayerController.data()));
}

CPlayer::~CPlayer()
{
}

constexpr float gravity{ -9.81f };
constexpr float height{ 2.0f };

void CPlayer::Move(float Strafe, float Forward, bool Fast, float ElapsedTime)
{
	//TO DO : Crear una variable que contenga el �ngulo Yaw del controlador de c�mara m_FPSCameraController
	const float l_Yaw = m_FPSCameraController->GetYaw();
	//TO DO : Inicializar la variable l_VectorMovement con la direcci�n de movimiento sobre el plano XZ del personaje seg�n los valores de Strafe y Forward. Strafe mover� al personaje lateralmente y Forward hacia delante
	XMFLOAT3 l_VectorMovement{};
	const XMVECTOR l_ForwardVector = eulerToDirection(g_RollDefault, g_PitchDefault, l_Yaw) * Forward;
	const XMFLOAT3 l_Lateral = m_FPSCameraController->GetRight();
	const XMVECTOR l_LateralVector = DirectX::XMLoadFloat3(&l_Lateral) * -Strafe;
	const XMVECTOR l_Direction = l_ForwardVector + l_LateralVector;
	DirectX::XMStoreFloat3(&l_VectorMovement, l_Direction); // TODO delete, it's redundant

	//TO DO : Incrementar la variable miembro m_VerticalSpeed seg�n la gravedad -9.81 multiplicado por el ElapsedTime
	m_VerticalSpeed += ElapsedTime * gravity;

	//TO DO : Normalizar el vector l_VectorMovement utilizando la funci�n de DirectX XMVector3Normalize, para ello deberemos convertir l_VectorMovement de tipo XMFLOAT3 a XMVECTOR
	const XMVECTOR l_NormalizedMovement = DirectX::XMVector3Normalize(l_Direction);
	//TO DO : Multiplicar el vector normalizado por la velocidad m_FastSpeed o m_Speed (dependiendo si est� activo el par�metro Fast) por el ElapsedTime y asignarlo a l_VectorMovement 
	DirectX::XMStoreFloat3(&l_VectorMovement, (Fast * m_FastSpeed + !Fast * m_Speed) * l_NormalizedMovement * ElapsedTime);
	//TO DO : Asignar en la componente Y de l_VectorMovement el movimiento en Y multiplicando m_VerticalSpeed por el ElapsedTime
	l_VectorMovement.y = m_VerticalSpeed * ElapsedTime;
	//TO DO : Incrementar m_Position seg�n el vector l_VectorMovement
	m_Position = sum(m_Position, l_VectorMovement);
	//TO DO : Para evitar que el personaje no caiga infinitamente debemos bloquearlo, para ello si la componente Y de m_Position es menor que 2 asignamos la componente Y de m_Position a 2 y le asignamos la velocidad vertical m_VerticalSpeed el valor de 0
	if (m_Position.y < height) {
		m_Position.y = height;
		m_VerticalSpeed = 0.0f;
	}
	//TO DO : Establecer la nueva posici�n en el controlador de c�mara m_FPSCameraController con el m�todo SetPosition
	m_FPSCameraController->SetPosition(m_Position);
}

void CPlayer::Update(float ElapsedTime)
{
	CKeyboardInput* l_KeyboardInput;
	CMouseInput* l_MouseInput;
	//TO DO : Asignar en l_KeyboardInput el device del Keyboard del InputManager que se encuentra en la clase CUOCEngine
	l_KeyboardInput = CUOCEngine::GetEngine()->GetInputManager()->GetKeyboard();
	//TO DO : Asignar en l_MouseInput el device del Mouse del InputManager que se encuentra en la clase CUOCEngine
	l_MouseInput = CUOCEngine::GetEngine()->GetInputManager()->GetMouse();
	//TO DO : Incrementar el �ngulo Yaw del controlador de c�mara m_FPSCameraController utilizando el m�todo AddYaw seg�n el movimiento en -X del rat�n que recogemos utilizando el m�todo GetMovementX de la instancia l_MouseInput multiplicado por el ElapsedTime
	m_FPSCameraController->AddYaw(deg2Rad(-l_MouseInput->GetMovementX() * ElapsedTime));
	//TO DO : Incrementar el �ngulo Pitch del controlador de c�mara m_FPSCameraController utilizando el m�todo AddPitch seg�n el movimiento en Y del rat�n que recogemos utilizando el m�todo GetMovementY de la instancia l_MouseInput multiplicado por el ElapsedTime
	m_FPSCameraController->AddPitch(deg2Rad(l_MouseInput->GetMovementY() * ElapsedTime));

	float l_Forward{ 0.0f };
	float l_Strafe{ 0.0f };
	bool l_MoveFast{};

	//TO DO : Asignar en la variable l_MoveFast verdadero si est� pulsada la tecla DIK_LSHIFT utilizando el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	l_MoveFast = l_KeyboardInput->IsKeyPressed(DIK_LSHIFT);
	//TO DO : Si se pulda la tecla DIK_W en el teclado asignamos el valor de 1 a l_Forward. Para saber si se pulsa la tecla utilizamos el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	l_Forward += l_KeyboardInput->IsKeyPressed(DIK_W);
	//TO DO : Si se pulda la tecla DIK_S en el teclado asignamos el valor de -1 a l_Forward. Para saber si se pulsa la tecla utilizamos el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	l_Forward -= l_KeyboardInput->IsKeyPressed(DIK_S);
	//TO DO : Si se pulda la tecla DIK_A en el teclado asignamos el valor de -1 a l_Strafe. Para saber si se pulsa la tecla utilizamos el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	l_Strafe -= l_KeyboardInput->IsKeyPressed(DIK_A);
	//TO DO : Si se pulda la tecla DIK_D en el teclado asignamos el valor de 1 a l_Strafe. Para saber si se pulsa la tecla utilizamos el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	l_Strafe += l_KeyboardInput->IsKeyPressed(DIK_D);
	//TO DO : Si se pulda la tecla DIK_SPACE en el teclado y m_VerticalSpeed tiene un valor de 0.0f llamamos al m�todo Jump. Para saber si se pulsa la tecla utilizamos el m�todo IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	if (l_KeyboardInput->IsKeyPressed(DIK_SPACE) && m_VerticalSpeed == 0.0f) {//TODO float comparison
		Jump();
	}
	//TO DO : Llamar al m�todo Move para mover el personaje
	Move(l_Strafe, l_Forward, l_MoveFast, ElapsedTime);
}

void CPlayer::Jump()
{
	//TO DO : Asignar el valor de m_VerticalSpeedJump a la variable miembro m_VerticalSpeed
	m_VerticalSpeed = m_VerticalSpeedJump;
}
