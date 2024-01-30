#include "FPSCameraController.h"
#include "Camera.h"

CFPSCameraController::CFPSCameraController()
//TO DO : Inicializa la variable miembro m_YawSpeed a 100.0f
//TO DO : Inicializa la variable miembro m_PitchSpeed a 60.0f
//TO DO : Inicializa la variable miembro m_Speed a 5.0f
//TO DO : Inicializa la variable miembro m_FastSpeed a 10.0f
//TO DO : Inicializa la variable miembro m_Position a 0, 2, 0
{
}

CFPSCameraController::~CFPSCameraController()
{	
}

void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{
	//TO DO : Calculamos el vector direcci�n Forward del controlador de c�mara utilizando el �ngulo m_Yaw
	//TO DO : Calculamos el vector direcci�n Right del controlador de c�mara utilizando el �ngulo m_Yaw+DEG2RAD(90.0f)
	//TO DO : Calculamos el vector de movimiento sumando el vector Forward multiplicado por el par�metro Forward y le sumamos el vector Right multiplicado por el par�metro Strafe
	//TO DO : Normalizamos el vector utilizando la funci�n de DirectX XMVector3Normalize
	//TO DO : Calculamos el movimiento multiplicando el vector normalizado por la variable de velocidad m_Speed y por el ElapsedTime
	//TO DO : En caso de que el par�metro Speed sea verdadero multiplicamos el movimiento tambi�n por la variable FastSpeed
	//TO DO : Establecemos la posici�n en m_Position asign�ndole la posici�n actual m�s el movimiento calculado
}

void CFPSCameraController::AddYaw(float Radians)
{
	//TO DO : Llama al m�todo AddYaw de la clase base CCameraController pas�ndole el �ngulo -Radians multiplicado por la variable m_YawSpeed
}

void CFPSCameraController::AddPitch(float Radians)
{
	//TO DO : Llama al m�todo AddPitch de la clase base CCameraController pas�ndole el �ngulo Radians multiplicado por la variable m_PitchSpeed
}

void CFPSCameraController::SetCamera(CCamera *Camera) const
{
	//TO DO : Establecer el FOV de la c�mara utilizando el m�todo SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	//TO DO : Establecer el AspectRatio de la c�mara utilizando el m�todo SetAspectRatio a 16.0f/9.0f
	//TO DO : Establecer la posici�n de la c�mara utilizando el m�todo SetPosition
	//TO DO : Establecer el LookAt de la c�mara utilizando el m�todo SetLookAt, el lookat ser� la posici�n m�s la direcci�n de nuestro controlador
	//TO DO : Establecer el vector Up de la c�mara utilizando el m�todo SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro m�todo GetUp
	//TO DO : Llamar al m�todo SetMatrixs de la c�mara
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	//TO DO : Devuelve la direcci�n del controlador de c�mara utilizando l�s �ngulos m_Yaw y m_Pitch
}
