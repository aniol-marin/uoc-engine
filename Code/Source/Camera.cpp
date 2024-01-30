#include "Camera.h"

constexpr float g_FOVDefault = 60.0f;
constexpr float g_NearDefault = 0.1f;
constexpr float g_FarDefault = 100.0f;
constexpr float g_RatioDefault{ f_1 / f_1 };

CCamera::CCamera() :
	//TO DO : Inicializr la variable miembro m_FOV con 60 grados en radianes utilizando la macro DEG2RAD
	m_FOV{ deg2Rad(g_FOVDefault) },
	//TO DO : Inicializr la variable miembro m_Aspect Ratio a 1.0f
	m_AspectRatio{ g_RatioDefault },
	//TO DO : Inicializr la variable miembro m_ZNear a 0.1f
	m_ZNear{ g_NearDefault },
	//TO DO : Inicializr la variable miembro m_ZFar a 100.0f
	m_ZFar{ g_FarDefault },
	//TO DO : Inicializr la variable miembro m_LookAt a la posici�n 0, 0, 0
	m_LookAt{ g_Center },
	//TO DO : Inicializr la variable miembro m_Up con el vector vertical 0, 1, 0
	m_Up{ g_Up },
	m_Position{},
	m_Projection{},
	m_View{}
{
}

CCamera::~CCamera()
{
}

void CCamera::SetMatrixs()
{
	//NOTA : Para construir una variable de tipo XMVECTOR utilizar la funci�n de DirectX::XMVectorSet
	//TO DO : Construir la matriz de view en la variable m_View utilizando la funci�n de DirectX::XMMatrixLookAtRH
	m_View = DirectX::XMMatrixLookAtRH(
		DirectX::XMLoadFloat3(&m_Position),
		DirectX::XMLoadFloat3(&m_LookAt),
		DirectX::XMLoadFloat3(&m_Up));

	//TO DO : Construir la matriz de proyecci�n en la variable m_Projection utilizando la funci�n de DirectX::XMMatrixPerspectiveFovRH
	m_Projection = DirectX::XMMatrixPerspectiveFovRH(
		m_FOV,
		m_AspectRatio,
		m_ZNear,
		m_ZFar);
}
