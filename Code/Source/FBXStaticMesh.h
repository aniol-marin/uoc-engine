#ifndef _FBXSTATICMESH_H
#define _FBXSTATICMESH_H

#include <string>
#include <fbxsdk.h>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "defines.h"
#include <fbxsdk.h>
#include <PxPhysicsAPI.h>
//#include <geometry/PxTriangleMesh.h>

class CTexture;
class CRenderableVertexs;
class CEffect;

class CFBXStaticMesh
{
private:
	CEffect									*m_Effect;
	std::vector<CRenderableVertexs *>		m_RenderableVertexs;
	std::vector<CTexture *>					m_Textures;
	XMFLOAT3								m_Position, m_BBMin, m_BBMax;
	float									m_Radius;
	std::vector<physx::PxTriangleMesh *>			m_PxTriangleMeshes;
public:
	CFBXStaticMesh();
	virtual ~CFBXStaticMesh();
	float GetRadius() const { return m_Radius; }
	bool Generate(FbxNode *Node, FbxMesh *Mesh);
	const XMFLOAT3 & GetPosition() const { return m_Position; }
	const XMFLOAT3 & GetBBMin() const { return m_BBMin; }
	const XMFLOAT3 & GetBBMax() const { return m_BBMax; }
	void Render(ID3D11DeviceContext *DeviceContext);
	bool IsInBoundingBox(const XMFLOAT3 &Pos);
	std::vector<physx::PxTriangleMesh *> & GetPxTriangleMeshes() { return m_PxTriangleMeshes; }
};

#endif
