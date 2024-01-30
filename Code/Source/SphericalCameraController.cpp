#include <math.h>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "UOCEngine.h"
#include "InputManager.h"
#include "MouseInput.h"

constexpr float g_AxisUpdateSpeed = 30.0f;
constexpr float g_ZoomDefault = 50.0f;
constexpr float g_ZoomSpeedDefault = 2.0f;
constexpr float g_ScreenRatioDefault = 16.0f / 9.0f;

CSphericalCameraController::CSphericalCameraController() :
	//TO DO : Inicializa la variable miembro m_Zoom a 50.0f
	m_Zoom{ g_ZoomDefault },
	//TO DO : Inicializa la variable miembro m_ZoomSpeed a 2.0f
	m_ZoomSpeed{ g_ZoomSpeedDefault }
{
}

CSphericalCameraController::~CSphericalCameraController()
{
}

XMFLOAT3 CSphericalCameraController::GetDirection() const
{
	//TO DO : Calcula la direcci�n de la c�mara utilizando los �ngulos Yaw y Pitch
	XMFLOAT3 l_Direction;
	DirectX::XMStoreFloat3(&l_Direction, eulerToDirection(
		g_RollDefault,
		m_Pitch,
		m_Yaw));
	return l_Direction;
}

void CSphericalCameraController::SetCamera(CCamera* Camera) const
{
	//TO DO : Establecer el FOV de la c�mara utilizando el m�todo SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	Camera->SetFOV(deg2Rad(g_ZoomDefault));
	//TO DO : Establecer el AspectRatio de la c�mara utilizando el m�todo SetAspectRatio a 16.0f/9.0f
	Camera->SetAspectRatio(g_ScreenRatioDefault);
	//TO DO : Establecer la Posici�n de la c�mara utilizando el m�todo SetPosition, la posici�n de la c�mara ser� la posici�n del controlador de c�mara menos la direcci�n de nuestro controlador
	XMVECTOR l_Position = DirectX::XMLoadFloat3(&m_Position);
	const XMFLOAT3 l_Handle = GetDirection();
	const XMVECTOR l_Direction = DirectX::XMLoadFloat3(&l_Handle);
	l_Position -= l_Direction;
	XMFLOAT3 l_NewPosition;
	DirectX::XMStoreFloat3(&l_NewPosition, l_Position);
	Camera->SetPosition(l_NewPosition);
	//TO DO : Establecer el LookAt de la c�mara utilizando el m�todo SetLookAt a la posici�n del controlador de c�mara
	Camera->SetLookAt(m_Position);
	//TO DO : Establecer el vector Up de la c�mara utilizando el m�todo SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro m�todo GetUp
	Camera->SetUp(GetUp());
	//TO DO : Llamar al m�todo SetMatrixs de la c�mara
	Camera->SetMatrixs();
}

void CSphericalCameraController::Update(float ElapsedTime)
{
	const CMouseInput* l_Mouse = CUOCEngine::GetEngine()->GetInputManager()->GetMouse();

	//TO DO : A�ade grados al �ngulo yaw del controlador de c�mara utilizando el m�todo AddYaw, para ello utilizaremos el m�todo GetMovementX del Input de rat�n multiplicado por el elapsedTime y por 30.0f como velocidad
	AddYaw(deg2Rad(l_Mouse->GetMovementX() * ElapsedTime * g_AxisUpdateSpeed));
	//TO DO : A�ade grados al �ngulo pitch del controlador de c�mara utilizando el m�todo AddPitch, para ello utilizaremos el m�todo GetMovementY del Input de rat�n multiplicado por el elapsedTime y por 30.0f como velocidad
	AddPitch(deg2Rad(l_Mouse->GetMovementY() * ElapsedTime * g_AxisUpdateSpeed));
	//TO DO : A�ade zoom al controlador de c�mara utilizando el m�todo AddZoom, para ello utilizaremos el m�todo GetMovementZ del Input de rat�n multiplicado por el elapsedTime y por 2.0f como velocidad
	AddZoom(l_Mouse->GetMovementZ() * ElapsedTime * m_ZoomSpeed);
}