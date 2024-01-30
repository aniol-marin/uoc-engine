#ifndef _RENDERABLE_OBJECT_MANAGER_H_
#define _RENDERABLE_OBJECT_MANAGER_H_

#include <vector>
#include "defines.h"

class CRenderableObject;
class CAnimatedCoreModel;

class CRenderableObjectManager
{
protected:
	std::vector<CRenderableObject *>				m_RenderableObjects;
public:
	CRenderableObjectManager();
	virtual ~CRenderableObjectManager();
	void Update(float ElapsedTime);
	void Render(ID3D11DeviceContext *DeviceContext);
	void AddRenderableObject(CRenderableObject *RenderableObject);
	void AddAnimatedModel(CAnimatedCoreModel *AnimatedCoreModel, const XMFLOAT3 &Position, const XMFLOAT3 &Rotation, const XMFLOAT3 &Scale);
};

#endif
