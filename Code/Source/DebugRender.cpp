#include "DebugRender.h"
#include "UOCEngine.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"
#include "RenderManager.h"

CDebugRender::CDebugRender(ID3D11Device* Device)
{
	//AXIS
	CEffectManager* l_EffectManager = CUOCEngine::GetEngine()->GetEffectManager();
	m_Effect = l_EffectManager->GetEffect(UOC_POSITION_COLOR_VERTEX::GetVertexType());
	UOC_POSITION_COLOR_VERTEX l_AxisVtxs[6] =
	{
		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	m_AxisRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);

	//CUBE
	const float l_SizeCube = 1.0f;
	UOC_POSITION_COLOR_VERTEX l_CubeVtxs[] =
	{
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//tapa
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//lineas laterales
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,-l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,-l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube / 2.0f,l_SizeCube / 2.0f,l_SizeCube / 2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	m_CubeRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_CubeVtxs, 24, 12);

	//GRID
	float l_Size = 10.0f;
	const int l_Grid = 10;
	UOC_POSITION_COLOR_VERTEX l_GridVtxs[(l_Grid + 1) * 2 * 2];
	for (int b = 0; b <= l_Grid; ++b)
	{
		l_GridVtxs[b * 2].Position = XMFLOAT3(-l_Size / 2.0f + ((float)(b * l_Size)) / (float)l_Grid, 0.0f, -l_Size / 2.0f);
		l_GridVtxs[b * 2].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		l_GridVtxs[(b * 2) + 1].Position = XMFLOAT3(-l_Size / 2.0f + ((float)(b * l_Size)) / (float)l_Grid, 0.0f, l_Size / 2.0f);
		l_GridVtxs[(b * 2) + 1].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//LINEAS EN X
	for (int b = 0; b <= l_Grid; ++b)
	{
		l_GridVtxs[(l_Grid + 1) * 2 + (b * 2)].Position = XMFLOAT3(-l_Size / 2.0f, 0.0f, -l_Size / 2.0f + ((float)(b * l_Size)) / (float)l_Grid);
		l_GridVtxs[(l_Grid + 1) * 2 + (b * 2)].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		l_GridVtxs[(l_Grid + 1) * 2 + (b * 2) + 1].Position = XMFLOAT3(l_Size / 2.0f, 0.0f, -l_Size / 2.0f + ((float)(b * l_Size)) / (float)l_Grid);
		l_GridVtxs[(l_Grid + 1) * 2 + (b * 2) + 1].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_GridRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_GridVtxs, (l_Grid + 1) * 2 * 2, (l_Grid + 1) * 2);

	//SPHERE
	const int l_Aristas = 10;
	UOC_POSITION_COLOR_VERTEX l_SphereVtxs[4 * l_Aristas * l_Aristas];
	for (int t = 0; t < l_Aristas; ++t)
	{
		float l_RadiusRing = sin(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas));
		for (int b = 0; b < l_Aristas; ++b)
		{
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 0].Position = XMFLOAT3(l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))), cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)), l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 0].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 1].Position = XMFLOAT3(l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)(b + 1)) / ((float)l_Aristas))), cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)), l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)(b + 1)) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 1].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			float l_RadiusNextRing = sin(DEG2RAD(180.0f * ((float)(t + 1))) / ((float)l_Aristas));

			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 2].Position = XMFLOAT3(l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))), cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)), l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 2].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 3].Position = XMFLOAT3(l_RadiusNextRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))), cos(DEG2RAD(180.0f * ((float)(t + 1))) / ((float)l_Aristas)), l_RadiusNextRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 3].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	m_SphereRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_SphereVtxs, 4 * l_Aristas * l_Aristas, 2 * l_Aristas * l_Aristas);
}

CDebugRender::~CDebugRender()
{
	CHECKED_DELETE(m_AxisRenderableVertexs);
	CHECKED_DELETE(m_GridRenderableVertexs);
	CHECKED_DELETE(m_CubeRenderableVertexs);
	CHECKED_DELETE(m_SphereRenderableVertexs);
}


void CDebugRender::DrawAxis(ID3D11DeviceContext* DeviceContext, float Size)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_BaseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	CEffectManager::m_ObjectConstantBufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_AxisRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawGrid(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_BaseColor = Color;
	CEffectManager::m_ObjectConstantBufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_GridRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawCube(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_BaseColor = Color;
	CEffectManager::m_ObjectConstantBufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_CubeRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_BaseColor = Color;
	CEffectManager::m_ObjectConstantBufferParameters.m_DebugRenderScale = XMFLOAT4(Radius, Radius, Radius, Radius);
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	m_SphereRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color, const XMFLOAT3& Position)
{
	CEffectManager::m_ObjectConstantBufferParameters.m_BaseColor = Color;
	CEffectManager::m_ObjectConstantBufferParameters.m_DebugRenderScale = XMFLOAT4(Radius, Radius, Radius, Radius);
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	ID3D11Device* l_Device{ CUOCEngine::GetEngine()->GetRenderManager()->GetDevice() };

	std::unique_ptr<CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>> l_Sphere{ CreateVisuals(l_Device, Position, Radius, Color) };
	l_Sphere->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawInteractableSpheres(ID3D11DeviceContext* DeviceContext, const XMFLOAT4& Scale, const XMFLOAT4& Color)
{
	for (const PxRigidDynamic* l_RigidBody : m_InteractiveSpheres) {
		const PxVec3 l_Position = l_RigidBody->getGlobalPose().p;
		DrawSphere(DeviceContext, Scale.x, Color, XMFLOAT3{ l_Position.x, l_Position.y, l_Position.z });
	}

}

std::unique_ptr<CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>> CDebugRender::CreateVisuals(ID3D11Device* Device, const XMFLOAT3& Position, float Radius, const XMFLOAT4& Color) {

	const int l_Aristas = 10;
	UOC_POSITION_COLOR_VERTEX l_SphereVtxs[4 * l_Aristas * l_Aristas];
	for (int t = 0; t < l_Aristas; ++t)
	{
		float l_RadiusRing = sin(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas));
		for (int b = 0; b < l_Aristas; ++b)
		{
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 0].Position = XMFLOAT3(
				Position.x + l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))),
				Position.y + cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)),
				Position.z + l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 0].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 1].Position = XMFLOAT3(
				Position.x + l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)(b + 1)) / ((float)l_Aristas))),
				Position.y + cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)),
				Position.z + l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)(b + 1)) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 1].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			float l_RadiusNextRing = sin(DEG2RAD(180.0f * ((float)(t + 1))) / ((float)l_Aristas));

			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 2].Position = XMFLOAT3(
				Position.x + l_RadiusRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))),
				Position.y + cos(DEG2RAD(180.0f * ((float)t)) / ((float)l_Aristas)),
				Position.z + l_RadiusRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 2].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 3].Position = XMFLOAT3(
				Position.x + l_RadiusNextRing * cos(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))),
				Position.y + cos(DEG2RAD(180.0f * ((float)(t + 1))) / ((float)l_Aristas)),
				Position.z + l_RadiusNextRing * sin(DEG2RAD((float)(360.0f * (float)b) / ((float)l_Aristas))));
			l_SphereVtxs[(t * l_Aristas * 4) + (b * 4) + 3].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	return std::make_unique<CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>>(Device, l_SphereVtxs, 4 * l_Aristas * l_Aristas, 2 * l_Aristas * l_Aristas);
}

void CDebugRender::AssignInteractableSphereVisuals(const PxRigidDynamic* RigidBody) {
	m_InteractiveSpheres.push_back(RigidBody);
}

void CDebugRender::CreateInteractiveSphere(CDebugRender* DebugRenderer, CPhysicsManager* PhysicsManager, ID3D11Device* Device, float Scale, XMFLOAT4 Color, XMFLOAT3 Origin) {

	const PxVec3 l_Origin = PxVec3{ Origin.x, Origin.y, Origin.z };
	PxRigidDynamic* l_RigidBody{ PhysicsManager->CreateRigidDynamic(Scale, l_Origin) };

	DebugRenderer->AssignInteractableSphereVisuals(l_RigidBody);
}