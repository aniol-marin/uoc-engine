#ifndef ANIMATEDINSTANCEMODEL_H
#define ANIMATEDINSTANCEMODEL_H

#define MAXBONES						29

#include "defines.h"
#include <vector>
#include "RenderableObject.h"

class CalModel;
class CAnimatedCoreModel;
class CalHardwareModel;
class CTexture;
class CRenderableVertexs;
class CEffect;

class CAnimatedInstanceModel : public CRenderableObject
{
private:
	CalModel							*m_CalModel;
	CAnimatedCoreModel					*m_AnimatedCoreModel;
	CalHardwareModel					*m_CalHardwareModel;
	std::vector<CTexture *>				m_TextureList;
	int									m_CurrentCycle;
	int									m_CurrentAnimationId;
	float								m_CurrentAnimationTime;
	CRenderableVertexs					*m_RenderableVertexs;
	CEffect								*m_Effect;
	int									m_NumVertices;
	int									m_NumFaces;

	void Destroy();
	bool LoadVertexBuffer(ID3D11Device *Device);
	void LoadTexture(ID3D11Device *Device);
public:
	CAnimatedInstanceModel();
	virtual ~CAnimatedInstanceModel();
	void InitD3D(ID3D11Device *Device);

	void Update(float ElapsedTime);
	void Render(ID3D11DeviceContext *DeviceContext);
	void Initialize(CAnimatedCoreModel *AnimatedCoreModel);
	void ExecuteAction(int Id, float Time);
	void BlendCycle(int Id, float Time);
	void ClearCycle(float Time);
	int GetCurrentCycle() const;
	int GetAnimationId() const;
};

#endif
