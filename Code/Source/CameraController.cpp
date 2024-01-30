#include "CameraController.h"
#include <functional>

CCameraController::CCameraController() :
	//TO DO : Inicializar la variable m_Yaw a 0.0f
	m_Yaw{ g_YawDefault },
	//TO DO : Inicializar la variable m_Pitch a 0.0f
	m_Pitch{ g_PitchDefault },
	m_Position{}
{
}
CCameraController::~CCameraController()
{
}

XMFLOAT3 CCameraController::GetRight() const
{
	//TO DO : Calcular el vector Right de la c�mara, para ello utilizaremos el �ngulo Yaw-DEG2RAD(90.0f) de la c�mara
	XMFLOAT3 l_Right{};
	DirectX::XMStoreFloat3(&l_Right, eulerToDirection(
		g_RollDefault,
		m_Pitch,
		m_Yaw - deg2Rad(g_QuarterCircleDeg)));
	return l_Right;
}

XMFLOAT3 CCameraController::GetUp() const
{
	//TO DO : Calcular el vector Up de la c�mara, para ello utilizaremos los �ngulos Yaw y Pitch de la c�mara
	XMFLOAT3 l_Up{};
	DirectX::XMStoreFloat3(&l_Up, eulerToDirection(
		g_RollDefault,
		m_Pitch + deg2Rad(g_QuarterCircleDeg),
		m_Yaw));
	return l_Up;
}

void CCameraController::AddYaw(float Radians)
{
	//TO DO : Incrementar el �ngulo Yaw de la c�mara seg�n el par�metro Radians
	m_Yaw += Radians;

	std::function<float(float, float)> fModule;
	 
	fModule = [&fModule](float value, float period) {
		if (value > period) fModule(value - period, period);
		else if (value < -period) fModule(value + period, period);
		return value;
	};

	//TO DO : Si el �ngulo Yaw es superior a 360 grados decrementarlo en 360 grados para que siempre entre -360 y 360 grados
	if (m_Yaw > deg2Rad(g_FullCircleDeg)) {
		m_Yaw = fModule(m_Yaw, deg2Rad(g_FullCircleDeg));
	}
	//TO DO : Si el �ngulo Yaw es inferior a -360 grados incrementarlo en 360 grados para que siempre entre -360 y 360 grados
	else if (m_Yaw < -deg2Rad(g_FullCircleDeg)) {
		m_Yaw = -fModule(-m_Yaw, deg2Rad(g_FullCircleDeg));
	}
}
void CCameraController::AddPitch(float Radians)
{

	//TO DO : Decremenetar el �ngulo Pitch de la c�mara seg�n el par�metro Radians
	//NOTA : Hacer un clamp consiste en limitar un valor en que no supere un cierto valor
	std::function<float(float, float, float)> clamp = [](float value, float min, float max) {
		value = (value > min) * value + !(value > min) * min;
		value = (value < max) * value + !(value < max) * max;
		return value;
	};
	//TO DO : Hacer un clamp del �ngulo entre 90 y -90 grados
	m_Pitch = clamp(m_Pitch - Radians, -deg2Rad(g_QuarterCircleDeg), deg2Rad(g_QuarterCircleDeg));

}
