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

CUOCEngine* CUOCEngine::m_UOCEngine = NULL;

CUOCEngine::CUOCEngine() :
	//TO DO : Inicializar la variable miembro m_RenderManager a NULL
	m_RenderManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_DrawAntTweakBar a false
	m_DrawAntTweakBar{ false },
	//TO DO : Inicializar la variable miembro m_EffectManager a NULL
	m_EffectManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_InputManager a NULL
	m_InputManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_CameraManager a NULL
	m_CameraManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_PreviousTime a 0
	m_PreviousTime{ 0 },
	//TO DO : Inicializar la variable miembro m_DebugRender a NULL
	m_DebugRender{ nullptr },
	//TO DO : Inicializar la variable miembro m_FBXManager a NULL
	m_FBXManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_RenderableObjectManager a NULL
	m_RenderableObjectManager{ nullptr },
	//TO DO : Inicializar la variable miembro m_TextureManager a NULL
	m_TextureManager{ nullptr },
	m_ElapsedTime{}
{
}

CUOCEngine::~CUOCEngine()
{
}

CUOCEngine* CUOCEngine::GetEngine()
{
	//TO DO : Implementar el patr�n Singleton, si la instancia m_UOCEngine es NULL crearla
	//TO DO : Devolver la instancia m_UOCEngine
	if (!m_UOCEngine) {
		m_UOCEngine = new CUOCEngine();
	}
	return m_UOCEngine;
}

constexpr std::string_view cameraFile = "./DATA/XML/cameras.xml";

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	//TO DO : Construye la variable miembro m_RenderManager
	m_RenderManager = new CRenderManager();
	//TO DO : Llama al m�todo Init de la variable miembro m_RenderManager
	m_RenderManager->Init(hWnd, Width, Height);

	//TO DO : Construye la variable miembro m_InputManager
	m_InputManager = new CInputManager(hWnd);
	//TO DO : Construye la variable miembro m_EffectManager
	m_EffectManager = new CEffectManager();

	//TO DO : Construye la variable miembro m_DebugRender pasando el par�metro el Device de la variable miembro m_RenderManager
	m_DebugRender = new CDebugRender(m_RenderManager->GetDevice());

	//TO DO : Construye la variable miembro m_CameraManager
	m_CameraManager = new CCameraManager();
	//TO DO : Llama al m�todo Load de la variable miemtro m_CameraManager para cargar el fichero xml "./DATA/XML/cameras.xml"
	m_CameraManager->Load(cameraFile.data());

	//TO DO : Construye la variable miembro m_FBXManager
	m_FBXManager = new CFBXManager();
	//TO DO : Construye la variable miembro m_RenderableObjectManager
	m_RenderableObjectManager = new CRenderableObjectManager();
	//TO DO : Construye la variable miembro m_TextureManager
	m_TextureManager = new CTextureManager();
	//TO DO : Inicializa la variable miembro m_PreviousTime asign�ndole el valor que devuelve la funci�n timeGetTime()
	m_PreviousTime = timeGetTime();
}

void CUOCEngine::Update()
{
	//TO DO : Calcula el elapsed time del frame, para ello recoges el tiempo actual con la funci�n timeGetTime() y le decrementamos el m_PreviousTime. Este valor se calcula en milisegundos y lo transformamos en segundos multiplicando por 0.001f
	const DWORD l_CurrentTime = timeGetTime();
	m_ElapsedTime = (l_CurrentTime - m_PreviousTime) * 0.001f;
	//TO DO : Asignamos a la variable m_PreviousTime el tiempo actual de este frame que hemos capturado en el TO DO anterior
	m_PreviousTime = l_CurrentTime;

	//TO DO : Llamamos al m�todo Update de la variable miembro m_InputManager para actualizar el Input
	m_InputManager->Update();

	CKeyboardInput* l_KeyboardInput = m_InputManager->GetKeyboard();
	//TO DO : Si la tecla DIK_TAB se pulsa en este frame (utilizamos el m�todo KeyBecomesPressed de la instancia del KeyboardInput l_KeyboardInput), cambiamos el controlador de c�mara que se utiliza para pintar con el m�todo ChangeVision del m_CameraManager
	if (l_KeyboardInput->KeyBecomesPressed(DIK_TAB)) {
		m_CameraManager->ChangeVision();
	}
	//TO DO : Si la tecla DIK_C se pulsa en este frame, cambiamos el controlador de c�mara que se utiliza para control con el m�todo ChangeControl del m_CameraManager
	if (l_KeyboardInput->KeyBecomesPressed(DIK_C)) {
		m_CameraManager->ChangeControl();
	}
	//TO DO : Actualizamos el m_CameraManager llamando al m�todo Update
	m_CameraManager->Update(m_ElapsedTime);
	//TO DO : Actualizamos el m_RenderableObjectManager llamando al m�todo Update
	m_RenderableObjectManager->Update(m_ElapsedTime);
}

void CUOCEngine::Render()
{
	//TO DO : Llamar al m�todo BeginRenderDX de la instancia m_RenderManager
	ID3D11DeviceContext* l_DeviceContext = m_RenderManager->GetDeviceContext();
	m_RenderManager->BeginRenderDX();

	//TO DO : Si debemos pintar en modo s�lido (utilizamos el m�tod GetPaintSolid de la clase m_RenderManager), establecemos el renderstate de s�lido utilizando el m�todo SetSolidRenderState de la clase m_RenderManager
	if (m_RenderManager->GetPaintSolid()) {
		m_RenderManager->SetSolidRenderState(l_DeviceContext);
	}
	//TO DO : En caso contrario establecemos el render state en modo alambre utilizando el m�todo SetWireframeRenderState de la clase m_RenderManager
	else {
		m_RenderManager->SetWireframeRenderState(l_DeviceContext);
	}

	CSceneConstantBufferParameters& l_BufferParameters = m_EffectManager->m_SceneConstantBufferParameters;
	//TO DO : Recoger la matriz de view de la c�mara de la variable miembro m_CameraManager
	const DirectX::CXMMATRIX& l_View = m_CameraManager->GetCamera().GetView();
	//TO DO : Recoger la matriz de proyecci�n de la c�mara de la variable miembro m_CameraManager
	const DirectX::CXMMATRIX& l_Projection = m_CameraManager->GetCamera().GetProjection();
	//TO DO : Establecer la variable miembro m_View de la variable miembro est�tica m_SceneConstantBufferParameters de la clase CEffectManager, el valor ser� la matriz transpuesta de la matriz de View que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la funci�n de DirectX XMMatrixTranspose
	l_BufferParameters.m_View = XMMatrixTranspose(l_View);
	//TO DO : Establecer la variable miembro m_Projection de la variable miembro est�tica m_SceneConstantBufferParameters de la clase CEffectManager, el valor ser� la matriz transpuesta de la matriz de Projection que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la funci�n de DirectX XMMatrixTranspose
	l_BufferParameters.m_Projection = XMMatrixTranspose(l_Projection);
	//TO DO : Establecer las constantes de escena en la variable miembro m_EffectManager utilizando el m�todo SetSceneConstantBuffer
	m_EffectManager->SetSceneConstantBuffer(l_DeviceContext);
	//TO DO : Llamar al m�todo Render de la variable miembro m_RenderableObjectManager
	m_RenderableObjectManager->Render(l_DeviceContext);


	if (m_RenderManager->DrawAxisGrid())
	{
		ID3D11DeviceContext* l_DeviceContext = m_RenderManager->GetDeviceContext();
		//TO DO : Crear una variable de tipo XMMATRIX que contendr� la matriz de mundo y asignarle el valor identidad mediante la funci�n DirectX:::XMMatrixIdentity
		const DirectX::XMMATRIX l_WorldMatrix = DirectX::XMMatrixIdentity();
		//TO DO : Establecer en la variable miembro m_World de la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager, estableceremos la matriz transpuesta de la variable de mundo que hemos creado en el TO DO anterior
		m_EffectManager->m_ObjectConstantBufferParameters.m_World = DirectX::XMMatrixTranspose(l_WorldMatrix);
		//TO DO : Llamar al m�todo SetObjectConstantBuffer de la variable miembro m_EffectManager para establecer las constantes de objeto
		m_EffectManager->SetObjectConstantBuffer(l_DeviceContext);
		//TO DO : Llamar al m�todo DrawAxis de la variable miembro m_DebugRender con un Size de 8.0f
		m_DebugRender->DrawAxis(l_DeviceContext, 8.0f);
		//TO DO : Llamar al m�todo DrawGrid de la variable miembro m_DebugRender con un Size de 1.0f y color blanco
		m_DebugRender->DrawGrid(l_DeviceContext, 1.0f, g_White);
		//TO DO : Llamar al m�todo DrawCube de la variable miembro m_DebugRender con un Size de 3.0f y color blanco
		m_DebugRender->DrawCube(l_DeviceContext, 3.0f, g_White);
		//TO DO : Llamar al m�todo DrawSphere de la variable miembro m_DebugRender con un Size de 0.5f y color blanco
		m_DebugRender->DrawSphere(l_DeviceContext, 0.5f, g_White);
	}

	//TO DO : Llamar al m�todo EndRenderDX de la instancia m_RenderManager
	m_RenderManager->EndRenderDX();
}

void CUOCEngine::Destroy()
{
	//TO DO : Destruir la variable miembro m_DebugRender utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_DebugRender);
	//TO DO : Destruir la variable miembro m_InputManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_InputManager);
	//TO DO : Destruir la variable miembro m_CameraManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_CameraManager);
	//TO DO : Destruir la variable miembro m_EffectManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_EffectManager);
	//TO DO : Destruir la variable miembro m_FBXManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_FBXManager);
	//TO DO : Destruir la variable miembro m_RenderableObjectManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_RenderableObjectManager);
	//TO DO : Destruir la variable miembro m_TextureManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_TextureManager);
	//TO DO : Llamar al m�todo Destroy de la variable miembro m_RenderManager
	m_RenderManager->Destroy();
	//TO DO : Destruir la variable miembro m_RenderManager utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_RenderManager);
}