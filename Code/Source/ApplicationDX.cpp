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
	
	CAnimatedCoreModel *l_AnimatedCoreModel;
	//TO DO : Inicializar la variable l_AnimatedCoreModel recogiendo el Actor de nombre "bot" y path "Data/Models/Bot/" de la clase CAnimatedModelManager que se encuentra en la clase CUOCEngine
	//TO DO : Añade un modelo animado de tipo l_AnimatedCoreModel en la clase CRenderableObjectManager que se encuentra en la clase CUOCEngine en la posición (0.0f, 0.0f, 0.0f), rotación (0.0f, 0.0f, 0.0f) y escala (2.0f, 2.0f, 2.0f)
	//TO DO : Añade un modelo animado de tipo l_AnimatedCoreModel en la clase CRenderableObjectManager que se encuentra en la clase CUOCEngine en la posición (33.0f, 2.3f, -18.0f), rotación (0.0f, 0.0f, 0.0f) y escala (2.0f, 2.0f, 2.0f)
	//TO DO : Añade un modelo animado de tipo l_AnimatedCoreModel en la clase CRenderableObjectManager que se encuentra en la clase CUOCEngine en la posición (68.0f, -0.8f, 6.0f), rotación (0.0f, 0.0f, 0.0f) y escala (2.0f, 2.0f, 2.0f)
	//TO DO : Añade un modelo animado de tipo l_AnimatedCoreModel en la clase CRenderableObjectManager que se encuentra en la clase CUOCEngine en la posición (17.0f, -5.7f, 31.0f), rotación (0.0f, 0.0f, 0.0f) y escala (2.0f, 2.0f, 2.0f)
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
