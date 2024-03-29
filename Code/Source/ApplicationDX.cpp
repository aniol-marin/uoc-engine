#include "ApplicationDX.h"
#include <assert.h>
#include "defines.h"
#include "DebugRender.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "VertexTypes.h"
#include "Player.h"
#include "FBXManager.h"
#include "EffectManager.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include "AnimatedModelManager.h"
#include "RenderableObjectManager.h"

CApplicationDX::CApplicationDX()
: m_Player(NULL)
{
}

CApplicationDX::~CApplicationDX()
{
	CUOCEngine *l_Engine=CUOCEngine::GetEngine();

	l_Engine->Destroy();
	CHECKED_DELETE(l_Engine);
	CHECKED_DELETE(m_Player);
}

void CApplicationDX::Init(HWND hWnd, int Width, int Height)
{
	CUOCEngine *l_Engine=CUOCEngine::GetEngine();
	l_Engine->Init(hWnd, Width, Height);
	m_Player=new CPlayer;
	l_Engine->GetFBXManager()->Load("data/models/world/World.fbx");
	
	CAnimatedCoreModel *l_AnimatedCoreModel = l_Engine->GetAnimatedModelManager()->GetActor("bot", "Data/Models/Bot/");
	CRenderableObjectManager *l_RenderableObjectManager = l_Engine->GetRenderableObjectManager();

	l_RenderableObjectManager->AddAnimatedModel(l_AnimatedCoreModel, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f));
	l_RenderableObjectManager->AddAnimatedModel(l_AnimatedCoreModel, XMFLOAT3(33.0f, 2.3f, -18.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f));
	l_RenderableObjectManager->AddAnimatedModel(l_AnimatedCoreModel, XMFLOAT3(68.0f, -0.8f, 6.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f));
	l_RenderableObjectManager->AddAnimatedModel(l_AnimatedCoreModel, XMFLOAT3(17.0f, -5.7f, 31.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f));
}

void CApplicationDX::Render()
{
	CUOCEngine::GetEngine()->Render();
}

void CApplicationDX::Update()
{
	CUOCEngine *l_Engine=CUOCEngine::GetEngine();
	l_Engine->Update();
	m_Player->Update(l_Engine->GetElapsedTime());
}

LRESULT WINAPI CApplicationDX::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (TwEventWin(hWnd, msg, wParam, lParam))
		return 0;
	switch( msg )
    {
		case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					return 0;
					break;
			}
		}
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}
