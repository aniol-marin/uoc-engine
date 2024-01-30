#include "UOCEngine.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "DebugRender.h"
#include "CameraManager.h"
#include "DebugRender.h"
#include "FBXManager.h"
#include "RenderableObjectManager.h"
#include "TextureManager.h"
#include "VertexTypes.h"
#include "AnimatedModelManager.h"
#include <functional>

CUOCEngine* CUOCEngine::m_UOCEngine = NULL;

template<class T>
static void TW_CALL ReloadShader(void* ClientData)
{
	ID3D11Device* l_Device;
	//TO DO : Asignar en l_Device el Device que se encuentra en la clase RenderManager que se encuentra en la clase singleton CUOCEngine
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	l_Device = l_Engine->GetRenderManager()->GetDevice();
	//TO DO : Llamar al método Reload del Effect que se encuentra en la clase EffectManager de la clase singleton CUOCEngine según el tipo de vértice T::GetVertexType()
	l_Engine->GetEffectManager()->GetEffect(T::GetVertexType())->Reload(l_Device);

}

CUOCEngine::CUOCEngine()
	: m_RenderManager(NULL)
	//TO DO : Inicializar la variable miembro m_DrawAntTweakBar a false
	, m_DrawAntTweakBar{ false }
	//TO DO : Inicializar la variable miembro m_Bar a NULL
	, m_Bar{ NULL }
	, m_EffectManager(NULL)
	, m_InputManager(NULL)
	, m_CameraManager(NULL)
	, m_PreviousTime(0)
	, m_DebugRender(NULL)
	, m_FBXManager(NULL)
	, m_RenderableObjectManager(NULL)
	, m_TextureManager(NULL)
	//TO DO : Inicializar la variable miembro m_AnimatedModelManager a NULL
	, m_AnimatedModelManager{ NULL }
	, m_ElapsedTime{}
{
}

CUOCEngine::~CUOCEngine()
{
}

CUOCEngine* CUOCEngine::GetEngine()
{
	if (m_UOCEngine == NULL)
		m_UOCEngine = new CUOCEngine;

	return m_UOCEngine;
}

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	m_RenderManager = new CRenderManager;
	m_RenderManager->Init(hWnd, Width, Height);

	m_InputManager = new CInputManager(hWnd);
	m_EffectManager = new CEffectManager();

	m_DebugRender = new CDebugRender(m_RenderManager->GetDevice());

	m_CameraManager = new CCameraManager;
	m_CameraManager->Load("./DATA/XML/cameras.xml");

	m_FBXManager = new CFBXManager;
	m_RenderableObjectManager = new CRenderableObjectManager;
	m_TextureManager = new CTextureManager;

	//TO DO : Construir la variable miembro m_AnimatedModelManager de tipo CAnimatedModelManager
	m_AnimatedModelManager = new CAnimatedModelManager();
	//TO DO : Llamar a la función TwInit para inicializar la librería AntTweakBar en TW_DIRECT3D11 pasándole el device que se encuentra en el RenderManager
	TwInit(TW_DIRECT3D11, m_RenderManager->GetDevice());

	//TO DO : Construir la variable miembro m_Bar utilizando la función de la librería de AntTweakBar TwNewBar con nombre "TweakBar"
	m_Bar = TwNewBar("TweakBar");
	//TO DO : Llamar a la función TwDefine de la librería de AntTweakBar pasando el parámetro " GLOBAL help='This example shows how to integrate AntTweakBar into a DirectX11 application.' "
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar into a DirectX11 application.' ");
	int l_BarSize[2] = { 224, 320 };
	//TO DO : Establecer los parámetros de la barra de AntTweakBar utilizando la función TwSetParam pasando los parámetros m_Bar, NULL, "size", TW_PARAM_INT32, 2, l_BarSize
	TwSetParam(m_Bar, NULL, "size", TW_PARAM_INT32, 2, l_BarSize);
	//TO DO : Añadir una variable de lectura escritura en la barra de AntTweakBar utilizando la función TwAddVarRW con los parámetros m_Bar, "PaintSolid", TW_TYPE_BOOLCPP, m_RenderManager->GetPaintSolidAddress(), "label='PaintSolid'group=Render"
	TwAddVarRW(m_Bar, "PaintSolid", TW_TYPE_BOOLCPP, m_RenderManager->GetPaintSolidAddress(), "label='PaintSolid'group=Render");
	//TO DO : Añadir una variable de lectura escritura en la barra de AntTweakBar utilizando la función TwAddVarRW con los parámetros m_Bar, "AxisGrid", TW_TYPE_BOOLCPP, m_RenderManager->GetDrawAxisGridAddress(), "group=Render"
	TwAddVarRW(m_Bar, "AxisGrid", TW_TYPE_BOOLCPP, m_RenderManager->GetDrawAxisGridAddress(), "group=Render");
	//TO DO : Añadir una variable de lectura escritura en la barra de AntTweakBar utilizando la función TwAddVarRW con los parámetros m_Bar, "BackgroundColor", TW_TYPE_COLOR4F, m_RenderManager->GetBackgroundColorAddress(), "colormode=rgb group=Render"
	TwAddVarRW(m_Bar, "BackgroundColor", TW_TYPE_COLOR4F, m_RenderManager->GetBackgroundColorAddress(), "colormode=rgb group=Render");
	//TO DO : Añadir un botón en la barra de AntTweakBar utilizando la función TwAddButton con los parámetros m_Bar, "Reload Normal Texture Shader", ReloadShader<UOC_POSITION_NORMAL_TEXTURE_VERTEX>, NULL, "group=Effects"
	TwAddButton(m_Bar, "Reload Normal Texture Shader", ReloadShader<UOC_POSITION_NORMAL_TEXTURE_VERTEX>, NULL, "group=Effects");

	TwButtonCallback callback = [](void* clientData) {
		CRenderableObjectManager* l_ObjectManager = CUOCEngine::GetEngine()->GetRenderableObjectManager();
		CAnimatedModelManager* l_ModelManager = CUOCEngine::GetEngine()->GetAnimatedModelManager();
		XMFLOAT3 l_Origin{ CUOCEngine::GetEngine()->GetCameraManager()->GetCamera().GetPosition() };
		XMFLOAT3 rotation{ CUOCEngine::GetEngine()->GetCameraManager()->GetCamera().GetLookAt() };
		XMFLOAT3 scale{ 1,1,1 };
		l_ObjectManager->AddAnimatedModel(l_ModelManager->GetActor("bot", "Data/Models/Bot"), l_Origin, rotation, scale);
	};
	TwAddButton(m_Bar, "Add Model into Player Position", callback, NULL, "group=Edit");

	m_PreviousTime = timeGetTime();
}

void CUOCEngine::Update()
{
	DWORD l_CurrentTime = timeGetTime();
	m_ElapsedTime = min(0.01f, (float)(l_CurrentTime - m_PreviousTime) * 0.001f);
	m_PreviousTime = l_CurrentTime;

	m_InputManager->Update();

	CCameraController* l_CameraController = m_CameraManager->GetCameraController("player");

	CKeyboardInput* l_KeyboardInput = m_InputManager->GetKeyboard();

	if (l_KeyboardInput->KeyBecomesPressed(DIK_TAB))
		m_CameraManager->ChangeVision();

	if (l_KeyboardInput->KeyBecomesPressed(DIK_C))
		m_CameraManager->ChangeControl();

	//TO DO : Si se pulsa la tecla DIK_J llamar al método ToggleAnTweakBar, basarse en las lineas anteriores	
	if (l_KeyboardInput->KeyBecomesPressed(DIK_J))
		ToggleAnTweakBar();

	//TO DO : Si AntTweakBar no está activa, utilizamos la función IsAntTweakBarActive() para saber si está o no activa
	if (!IsAntTweakBarActive())
	{
		m_CameraManager->Update(m_ElapsedTime);
		m_RenderableObjectManager->Update(m_ElapsedTime);
	}
}

void CUOCEngine::Render()
{
	m_RenderManager->BeginRenderDX();
	ID3D11DeviceContext* l_DeviceContext = m_RenderManager->GetDeviceContext();

	if (m_RenderManager->GetPaintSolid())
		m_RenderManager->SetSolidRenderState(l_DeviceContext);
	else
		m_RenderManager->SetWireframeRenderState(l_DeviceContext);

	const CCamera& l_Camera = m_CameraManager->GetCamera();
	XMMATRIX l_View = l_Camera.GetView();
	XMMATRIX l_Projection = l_Camera.GetProjection();
	CEffectManager::m_SceneConstantBufferParameters.m_View = XMMatrixTranspose(l_View);
	CEffectManager::m_SceneConstantBufferParameters.m_Projection = XMMatrixTranspose(l_Projection);
	m_EffectManager->SetSceneConstantBuffer(l_DeviceContext);

	m_RenderableObjectManager->Render(m_RenderManager->GetDeviceContext());

	if (m_RenderManager->DrawAxisGrid())
	{
		CEffectManager::m_ObjectConstantBufferParameters.m_World = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
		m_EffectManager->SetObjectConstantBuffer(l_DeviceContext);
		XMFLOAT4 l_DebugRenderColor(1.0f, 1.0f, 0.0f, 1.0f);
		ID3D11DeviceContext* l_DeviceContext = m_RenderManager->GetDeviceContext();

		m_DebugRender->DrawAxis(l_DeviceContext, 8.0f);
		m_DebugRender->DrawGrid(l_DeviceContext, 1.0f, l_DebugRenderColor);
		m_DebugRender->DrawCube(l_DeviceContext, 3.0f, l_DebugRenderColor);
		m_DebugRender->DrawSphere(l_DeviceContext, 0.5f, l_DebugRenderColor);
	}

	//TO DO : Si debemos pintar la AntTweakBar llamamos a la función TwDraw, para ello utilizaremos la variable miembro m_DrawAntTweakBar
	if (m_DrawAntTweakBar)
		TwDraw();

	m_RenderManager->EndRenderDX();
}

void CUOCEngine::Destroy()
{
	CHECKED_DELETE(m_DebugRender);
	CHECKED_DELETE(m_InputManager);
	CHECKED_DELETE(m_CameraManager);
	CHECKED_DELETE(m_EffectManager);
	CHECKED_DELETE(m_FBXManager);
	CHECKED_DELETE(m_RenderableObjectManager);
	CHECKED_DELETE(m_TextureManager);
	//TO DO : Destruir la variable miembro m_AnimatedModelManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_AnimatedModelManager);
	//TO DO : Destruir la librería AntTweakBar utilizando la función TwTerminate
	TwTerminate();

	m_RenderManager->Destroy();

	CHECKED_DELETE(m_RenderManager);
}
