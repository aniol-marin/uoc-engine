#include "CameraController.h"

CCameraController::CCameraController()
//TO DO : Inicializar la variable m_Yaw a 0.0f
//TO DO : Inicializar la variable m_Pitch a 0.0f
{
}
CCameraController::~CCameraController()
{
}

XMFLOAT3 CCameraController::GetRight() const
{
	//TO DO : Calcular el vector Right de la c�mara, para ello utilizaremos el �ngulo Yaw-DEG2RAD(90.0f) de la c�mara
}

XMFLOAT3 CCameraController::GetUp() const
{
	//TO DO : Calcular el vector Up de la c�mara, para ello utilizaremos los �ngulos Yaw y Pitch de la c�mara
}

void CCameraController::AddYaw(float Radians)
{
	//TO DO : Incrementar el �ngulo Yaw de la c�mara seg�n el par�metro Radians
	//TO DO : Si el �ngulo Yaw es superior a 360 grados decrementarlo en 360 grados para que siempre entre -360 y 360 grados
	//TO DO : Si el �ngulo Yaw es inferior a -360 grados incrementarlo en 360 grados para que siempre entre -360 y 360 grados
}
void CCameraController::AddPitch(float Radians)
{
	//TO DO : Decremenetar el �ngulo Pitch de la c�mara seg�n el par�metro Radians
	//NOTA : Hacer un clamp consiste en limitar un valor en que no supere un cierto valor
	//TO DO : Hacer un clamp del �ngulo entre 90 y -90 grados
}
