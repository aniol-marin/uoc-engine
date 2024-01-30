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

constexpr std::string_view fbxFile = "data/models/world/World.fbx";

CApplicationDX::CApplicationDX()
	: m_Player(NULL)
{
}

CApplicationDX::~CApplicationDX()
{
	//TO DO : Llamar al m�todo Destroy de la clase singleton CUOCEngine
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	l_Engine->Destroy();
	//TO DO : Hacer el CHECKED_DELETE del singleton de la clase CUOCEngine
	CHECKED_DELETE(l_Engine);
	//TO DO : Hacer el CHECKED_DELETE de la instancia del Player
	CHECKED_DELETE(m_Player);
}

void CApplicationDX::Init(HWND hWnd, int Width, int Height)
{
	//TO DO : Inicializar el motor llamando al m�todo Init de la clase singleton CUOCEngine
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	l_Engine->Init(hWnd, Width, Height);
	//TO DO : Crear la instancia de la clase CPlayer
	m_Player = new CPlayer();
	//TO DO : Llamar al m�todo Load del FBXManager del motor y cargar el fichero fbx "data/models/world/World.fbx"
	l_Engine->GetFBXManager()->Load(fbxFile.data());
}

void CApplicationDX::Render()
{
	//TO DO : Llamar al m�todo Render de la clase singleton CUOCEngine
	CUOCEngine::GetEngine()->Render();
}

void CApplicationDX::Update()
{
	auto l_Engine = CUOCEngine::GetEngine();

	//TO DO : Llamar al m�todo Update de la clase singleton CUOCEngine
	l_Engine->Update();
	//TO DO : Llamar al m�todo Update de la instancia player pas�ndole el elapsed time del motor
	m_Player->Update(l_Engine->GetElapsedTime());
}

LRESULT WINAPI CApplicationDX::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
