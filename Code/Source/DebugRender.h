#ifndef _DEBUGRENDER_H
#define _DEBUGRENDER_H

#include "defines.h"
#include <vector>
#include <memory>
#include "PhysicsManager.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"

class CRenderableVertexs;
class CEffect;

class CDebugRender
{
public:
	~CDebugRender();
private:
	CRenderableVertexs* m_AxisRenderableVertexs;
	CRenderableVertexs* m_GridRenderableVertexs;
	CRenderableVertexs* m_CubeRenderableVertexs;
	CRenderableVertexs* m_SphereRenderableVertexs;
	std::vector<const PxRigidDynamic*> m_InteractiveSpheres;
	CEffect* m_Effect;
public:
	CDebugRender(ID3D11Device* Device);
	void DrawAxis(ID3D11DeviceContext* DeviceContext, float Size);
	void DrawGrid(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color);
	void DrawCube(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color);
	void DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color);
	void DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color, const XMFLOAT3& Position);
	std::unique_ptr<CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>> CreateVisuals(ID3D11Device* Device, const XMFLOAT3& Position, float Radius, const XMFLOAT4& Color);
	void CreateInteractiveSphere(CDebugRender* DebugRenderer, CPhysicsManager* PhysicsManager, ID3D11Device* Device, float Scale, XMFLOAT4 Color, XMFLOAT3 Origin);
	void DrawInteractableSpheres(ID3D11DeviceContext * DeviceContext, const XMFLOAT4 & Scale, const XMFLOAT4 & Color);
	void AssignInteractableSphereVisuals(const PxRigidDynamic* Transform);
};

#endif
