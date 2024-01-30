#include <math.h>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "UOCEngine.h"
#include "InputManager.h"
#include "MouseInput.h"

CSphericalCameraController::CSphericalCameraController() 
//TO DO : Inicializa la variable miembro m_Zoom a 50.0f
//TO DO : Inicializa la variable miembro m_ZoomSpeed a 2.0f
{
}

CSphericalCameraController::~CSphericalCameraController()
{	
}

XMFLOAT3 CSphericalCameraController::GetDirection() const
{
	//TO DO : Calcula la direcci�n de la c�mara utilizando los �ngulos Yaw y Pitch
}

void CSphericalCameraController::SetCamera(CCamera *Camera) const
{
	//TO DO : Establecer el FOV de la c�mara utilizando el m�todo SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	//TO DO : Establecer el AspectRatio de la c�mara utilizando el m�todo SetAspectRatio a 16.0f/9.0f
	//TO DO : Establecer el LookAt de la c�mara utilizando el m�todo SetLookAt a la posici�n del controlador de c�mara
	//TO DO : Establecer la Posici�n de la c�mara utilizando el m�todo SetPosition, la posici�n de la c�mara ser� la posici�n del controlador de c�mara menos la direcci�n de nuestro controlador
	//TO DO : Establecer el vector Up de la c�mara utilizando el m�todo SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro m�todo GetUp
	//TO DO : Llamar al m�todo SetMatrixs de la c�mara
}

void CSphericalCameraController::Update(float ElapsedTime)
{
	//TO DO : A�ade grados al �ngulo yaw del controlador de c�mara utilizando el m�todo AddYaw, para ello utilizaremos el m�todo GetMovementX del Input de rat�n multiplicado por el elapsedTime y por 30.0f como velocidad
	//TO DO : A�ade grados al �ngulo pitch del controlador de c�mara utilizando el m�todo AddPitch, para ello utilizaremos el m�todo GetMovementY del Input de rat�n multiplicado por el elapsedTime y por 30.0f como velocidad
	//TO DO : A�ade zoom al controlador de c�mara utilizando el m�todo AddZoom, para ello utilizaremos el m�todo GetMovementZ del Input de rat�n multiplicado por el elapsedTime y por 2.0f como velocidad
}
