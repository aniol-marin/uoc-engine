#include "Camera.h"

CCamera::CCamera()
//TO DO : Inicializr la variable miembro m_FOV con 60 grados en radianes utilizando la macro DEG2RAD
//TO DO : Inicializr la variable miembro m_Aspect Ratio a 1.0f
//TO DO : Inicializr la variable miembro m_ZNear a 0.1f
//TO DO : Inicializr la variable miembro m_ZFar a 100.0f
//TO DO : Inicializr la variable miembro m_LookAt a la posici�n 0, 0, 0
//TO DO : Inicializr la variable miembro m_Up con el vector vertical 0, 1, 0
{
}

CCamera::~CCamera()
{
}

void CCamera::SetMatrixs()
{
	//NOTA : Para construir una variable de tipo XMVECTOR utilizar la funci�n de DirectX::XMVectorSet
	//TO DO : Construir la matriz de view en la variable m_View utilizando la funci�n de DirectX::XMMatrixLookAtRH
	//TO DO : Construir la matriz de proyecci�n en la variable m_Projection utilizando la funci�n de DirectX::XMMatrixPerspectiveFovRH
}
