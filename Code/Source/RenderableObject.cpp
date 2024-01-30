#include "RenderableObject.h"

CRenderableObject::CRenderableObject()
: m_Position(0.0f, 0.0f, 0.0f)
, m_Scale(1.0f, 1.0f, 1.0f)
, m_Rotation(0.0f, 0.0f, 0.0f)
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
	XMMATRIX l_TranslationMatrix, l_RotationXMatrix, l_RotationYMatrix, l_RotationZMatrix, l_ScaleMatrix;
	l_TranslationMatrix=DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	l_RotationXMatrix= DirectX::XMMatrixRotationX(m_Rotation.x);
	l_RotationYMatrix= DirectX::XMMatrixRotationY(m_Rotation.y);
	l_RotationZMatrix= DirectX::XMMatrixRotationZ(m_Rotation.z);
	l_ScaleMatrix= DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	
	return l_ScaleMatrix*(l_RotationXMatrix*l_RotationZMatrix*l_RotationYMatrix)*l_TranslationMatrix;
}
