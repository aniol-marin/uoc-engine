#include "RenderableObject.h"

CRenderableObject::CRenderableObject()
//TO DO : Inicializar la variable miembro m_Position a 0, 0, 0
//TO DO : Inicializar la variable miembro m_Scale a 1, 1, 1
//TO DO : Inicializar la variable miembro m_Rotation a 0, 0, 0
{
}

CRenderableObject::~CRenderableObject()
{
}

void CRenderableObject::Update(float ElapsedTime)
{
}

void CRenderableObject::Render(ID3D11DeviceContext *DeviceContext)
{
}

XMMATRIX CRenderableObject::GetTransform()
{
	XMMATRIX l_TranslationMatrix, l_RotationMatrix, l_RotationXMatrix, l_RotationYMatrix, l_RotationZMatrix, l_ScaleMatrix;
	//TO DO : Calcular la matriz de traslaci�n l_TranslationMatrix utilizando la funci�n de DirectX::XMMatrixTranslation y la posici�n que est� guardada en la variable m_Position
	//TO DO : Calcular la matriz de rotaci�n en X l_RotationXMatrix utilizando la funci�n de DirectX::XMMatrixRotationX y la rotaci�n que est� guardada en la variable m_Rotation.x
	//TO DO : Calcular la matriz de rotaci�n en Y l_RotationYMatrix utilizando la funci�n de DirectX::XMMatrixRotationY y la rotaci�n que est� guardada en la variable m_Rotation.y
	//TO DO : Calcular la matriz de rotaci�n en Z l_RotationZMatrix utilizando la funci�n de DirectX::XMMatrixRotationZ y la rotaci�n que est� guardada en la variable m_Rotation.z
	//TO DO : Calcular la matriz de escala l_ScaleMatrix utilizando la funci�n de DirectX::XMMatrixScaling y la escala que est� guardada en la variable m_Scale
	//TO DO : Calcular la matriz de rotaci�n l_RotationMatrix multiplicando las variables de rotaci�n l_RotationXMatrix por l_RotationYMatrix por l_RotationZMatrix
	//TO DO : Devolver el c�lculo de multiplicar la matriz de escala l_ScaleMatrix por l_RotationMatrix por l_TranslationMatrix
}
