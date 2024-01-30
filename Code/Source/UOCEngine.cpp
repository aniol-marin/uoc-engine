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
#include "PhysicsManager.h"
#include "ScriptManager.h"

CUOCEngine *CUOCEngine::m_UOCEngine=NULL;

template<class T>
static void TW_CALL ReloadShader(void *ClientData)
{
	CUOCEngine *l_Engine = CUOCEngine::GetEngine();
	ID3D11Device *l_Device = l_Engine->GetRenderManager()->GetDevice();
	l_Engine->GetEffectManager()->GetEffect(T::GetVertexType())->Reload(l_Device);
}

CUOCEngine::CUOCEngine()
: m_RenderManager(NULL)
, m_DrawAntTweakBar(false)
, m_Bar(NULL)
, m_EffectManager(NULL)
, m_InputManager(NULL)
, m_CameraManager(NULL)
, m_PreviousTime(0)
, m_DebugRender(NULL)
, m_FBXManager(NULL)
, m_RenderableObjectManager(NULL)
, m_TextureManager(NULL)
, m_AnimatedModelManager(NULL)
//TO DO : Inicializar la variable miembro m_PhysicsManager a NULL
//TO DO : Inicializar la variable miembro m_ScriptManager a NULL
{
}

CUOCEngine::~CUOCEngine()
{
}

CUOCEngine * CUOCEngine::GetEngine()
{
	if(m_UOCEngine==NULL)
		m_UOCEngine=new CUOCEngine;
	
	return m_UOCEngine;
}

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	m_RenderManager=new CRenderManager;
	m_RenderManager->Init(hWnd, Width, Height);

	m_InputManager=new CInputManager(hWnd);
	m_EffectManager=new CEffectManager();

	m_DebugRender=new CDebugRender(m_RenderManager->GetDevice());

	m_CameraManager=new CCameraManager;
	m_CameraManager->Load("./DATA/XML/cameras.xml");

	m_FBXManager=new CFBXManager;
	m_RenderableObjectManager=new CRenderableObjectManager;
	m_TextureManager=new CTextureManager;
	m_AnimatedModelManager = new CAnimatedModelManager;

	//TO DO : Construir la variable miembro m_PhysicsManager de tipo CPhysicsManager
	//TO DO : Inicializar el motor de física m_PhysicsManager utilizando el método Init
	//TO DO : Construir la variable miembro m_ScriptManager de tipo CScriptManager
	//TO DO : Inicializar el motor de física m_ScriptManager utilizando el método Initialize

	TwInit(TW_DIRECT3D11, m_RenderManager->GetDevice());

	m_Bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar into a DirectX11 application.' ");
	int l_BarSize[2] = { 224, 320 };
	TwSetParam(m_Bar, NULL, "size", TW_PARAM_INT32, 2, l_BarSize);

	TwAddVarRW(m_Bar, "PaintSolid", TW_TYPE_BOOLCPP, m_RenderManager->GetPaintSolidAddress(), "label='PaintSolid'group=Render");
	TwAddVarRW(m_Bar, "AxisGrid", TW_TYPE_BOOLCPP, m_RenderManager->GetDrawAxisGridAddress(), "group=Render");

	TwAddVarRW(m_Bar, "BackgroundColor", TW_TYPE_COLOR4F, m_RenderManager->GetBackgroundColorAddress(), "colormode=rgb group=Render");
	TwAddButton(m_Bar, "Reload Normal Texture Shader", ReloadShader<UOC_POSITION_NORMAL_TEXTURE_VERTEX>, NULL, "group=Effects");

	m_PreviousTime=timeGetTime();
}

void CUOCEngine::Update()
{
	DWORD l_CurrentTime=timeGetTime();
	m_ElapsedTime=min(0.01f, (float)(l_CurrentTime-m_PreviousTime)*0.001f);
	m_PreviousTime=l_CurrentTime;

	m_InputManager->Update();

	CCameraController *l_CameraController=m_CameraManager->GetCameraController("player");
	
	CKeyboardInput *l_KeyboardInput=m_InputManager->GetKeyboard();

	if (l_KeyboardInput->KeyBecomesPressed(DIK_J))
		ToggleAnTweakBar();
	
	if(l_KeyboardInput->KeyBecomesPressed(DIK_TAB))
		m_CameraManager->ChangeVision();

	if(l_KeyboardInput->KeyBecomesPressed(DIK_C))
		m_CameraManager->ChangeControl();

	if (!IsAntTweakBarActive())
	{
		m_CameraManager->Update(m_ElapsedTime);
		m_RenderableObjectManager->Update(m_ElapsedTime);
	}
	
	//TO DO : Llamar al método Update de la instancia m_PhysicsManager pasándole el ElapsedTime en segundos (hay que transformarlo de milisegundos a segundos)
}

void CUOCEngine::Render()
{
	m_RenderManager->BeginRenderDX();
	ID3D11DeviceContext *l_DeviceContext=m_RenderManager->GetDeviceContext();

	if(m_RenderManager->GetPaintSolid())
		m_RenderManager->SetSolidRenderState(l_DeviceContext);
	else
		m_RenderManager->SetWireframeRenderState(l_DeviceContext);

	const CCamera &l_Camera=m_CameraManager->GetCamera();
	XMMATRIX l_View=l_Camera.GetView();
	XMMATRIX l_Projection=l_Camera.GetProjection();
	CEffectManager::m_SceneConstantBufferParameters.m_View=XMMatrixTranspose(l_View);
	CEffectManager::m_SceneConstantBufferParameters.m_Projection=XMMatrixTranspose(l_Projection);
	m_EffectManager->SetSceneConstantBuffer(l_DeviceContext);

	m_RenderableObjectManager->Render(m_RenderManager->GetDeviceContext());

	if(m_RenderManager->DrawAxisGrid())
	{
		CEffectManager::m_ObjectConstantBufferParameters.m_World=DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
		m_EffectManager->SetObjectConstantBuffer(l_DeviceContext);
		XMFLOAT4 l_DebugRenderColor(1.0f, 1.0f, 0.0f, 1.0f);
		ID3D11DeviceContext *l_DeviceContext=m_RenderManager->GetDeviceContext();
		
		m_DebugRender->DrawAxis(l_DeviceContext, 8.0f);
		m_DebugRender->DrawGrid(l_DeviceContext, 1.0f, l_DebugRenderColor);
		m_DebugRender->DrawCube(l_DeviceContext, 3.0f, l_DebugRenderColor);
		m_DebugRender->DrawSphere(l_DeviceContext, 0.5f, l_DebugRenderColor);
	}

	if(m_DrawAntTweakBar)
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
	CHECKED_DELETE(m_AnimatedModelManager);
	//TO DO : Destruir la variable miembro m_PhysicsManager utilizando la macro CHECKED_DELETE
	//TO DO : Llamar al método Destroy de la variable miembro m_ScriptManager
	//TO DO : Destruir la variable miembro m_ScriptManager utilizando la macro CHECKED_DELETE

	TwTerminate();

	m_RenderManager->Destroy();

	CHECKED_DELETE(m_RenderManager);
}
