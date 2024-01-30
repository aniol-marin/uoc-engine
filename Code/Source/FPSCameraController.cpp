#include "FPSCameraController.h"
#include "Camera.h"

constexpr float g_ScreenRatio = 16.0f / 9.0f;
constexpr float g_YawSpeedDefault = 100.0f;
constexpr float g_PitchSpeedDefault = 60.0f;
constexpr float g_SpeedDefault = 5.0f;
constexpr float g_FastSpeedDefault = 10.0f;
constexpr float g_FOVDefault{ 50.0f };

CFPSCameraController::CFPSCameraController() :
	CCameraController(),
	//TO DO : Inicializa la variable miembro m_YawSpeed a 100.0f
	m_YawSpeed{ g_YawSpeedDefault },
	//TO DO : Inicializa la variable miembro m_PitchSpeed a 60.0f
	m_PitchSpeed{ g_PitchSpeedDefault },
	//TO DO : Inicializa la variable miembro m_Speed a 5.0f
	m_Speed{ g_SpeedDefault },
	//TO DO : Inicializa la variable miembro m_FastSpeed a 10.0f
	m_FastSpeed{ g_FastSpeedDefault }
{

	//TO DO : Inicializa la variable miembro m_Position a 0, 2, 0
	SetPosition(XMFLOAT3{ f32_0, f32_2, f32_0 });
}

CFPSCameraController::~CFPSCameraController()
{
}

void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{
	//TO DO : Calculamos el vector direcci�n Forward del controlador de c�mara utilizando el �ngulo m_Yaw
	const XMVECTOR l_Forward = eulerToDirection(g_RollDefault, g_PitchDefault, m_Yaw);
	//TO DO : Calculamos el vector direcci�n Right del controlador de c�mara utilizando el �ngulo m_Yaw+deg2Rad(90.0f)
	const XMVECTOR l_Right = eulerToDirection(g_RollDefault, g_PitchDefault, m_Yaw + deg2Rad(g_QuarterCircleDeg));
	//TO DO : Calculamos el vector de movimiento sumando el vector Forward multiplicado por el par�metro Forward y le sumamos el vector Right multiplicado por el par�metro Strafe
	const XMVECTOR l_Movement = l_Forward * Forward + l_Right * Strafe;
	//TO DO : Normalizamos el vector utilizando la funci�n de DirectX XMVector3Normalize
	const XMVECTOR l_NormalizedMovement = DirectX::XMVector3Normalize(l_Movement);
	//TO DO : Calculamos el movimiento multiplicando el vector normalizado por la variable de velocidad m_Speed y por el ElapsedTime
	XMVECTOR l_EffectiveMovement = l_NormalizedMovement * m_Speed * ElapsedTime;
	//TO DO : En caso de que el par�metro Speed sea verdadero multiplicamos el movimiento tambi�n por la variable FastSpeed
	l_EffectiveMovement = l_EffectiveMovement * !Speed + l_EffectiveMovement * Speed * m_FastSpeed;
	//TO DO : Establecemos la posici�n en m_Position asign�ndole la posici�n actual m�s el movimiento calculado
	m_Position = sum(m_Position, l_EffectiveMovement);
}

void CFPSCameraController::AddYaw(float Radians)
{
	//TO DO : Llama al m�todo AddYaw de la clase base CCameraController pas�ndole el �ngulo -Radians multiplicado por la variable m_YawSpeed
	CCameraController::AddYaw(-Radians * m_YawSpeed);
}

void CFPSCameraController::AddPitch(float Radians)
{
	//TO DO : Llama al m�todo AddPitch de la clase base CCameraController pas�ndole el �ngulo Radians multiplicado por la variable m_PitchSpeed
	CCameraController::AddPitch(Radians * m_PitchSpeed);
}

void CFPSCameraController::SetCamera(CCamera* Camera) const
{
	//TO DO : Establecer el FOV de la c�mara utilizando el m�todo SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	Camera->SetFOV(deg2Rad(g_FOVDefault));
	//TO DO : Establecer el AspectRatio de la c�mara utilizando el m�todo SetAspectRatio a 16.0f/9.0f
	Camera->SetAspectRatio(g_ScreenRatio);
	//TO DO : Establecer la posici�n de la c�mara utilizando el m�todo SetPosition
	Camera->SetPosition(m_Position);
	//TO DO : Establecer el LookAt de la c�mara utilizando el m�todo SetLookAt, el lookat ser� la posici�n m�s la direcci�n de nuestro controlador
	Camera->SetLookAt(combine (GetDirection(), m_Position));
	//TO DO : Establecer el vector Up de la c�mara utilizando el m�todo SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro m�todo GetUp
	Camera->SetUp(GetUp());
	//TO DO : Llamar al m�todo SetMatrixs de la c�mara
	Camera->SetMatrixs();
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	//TO DO : Devuelve la direcci�n del controlador de c�mara utilizando l�s �ngulos m_Yaw y m_PitchXMFLOAT3 l_Right{};
	XMFLOAT3 l_Direction;
	DirectX::XMStoreFloat3(&l_Direction, eulerToDirection(g_RollDefault, m_Pitch, m_Yaw));
	return l_Direction;
}