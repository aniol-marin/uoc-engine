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

CUOCEngine *CUOCEngine::m_UOCEngine=NULL;

CUOCEngine::CUOCEngine()
//TO DO : Inicializar la variable miembro m_RenderManager a NULL
//TO DO : Inicializar la variable miembro m_DrawAntTweakBar a false
//TO DO : Inicializar la variable miembro m_EffectManager a NULL
//TO DO : Inicializar la variable miembro m_InputManager a NULL
//TO DO : Inicializar la variable miembro m_CameraManager a NULL
//TO DO : Inicializar la variable miembro m_PreviousTime a 0
//TO DO : Inicializar la variable miembro m_DebugRender a NULL
//TO DO : Inicializar la variable miembro m_FBXManager a NULL
//TO DO : Inicializar la variable miembro m_RenderableObjectManager a NULL
//TO DO : Inicializar la variable miembro m_TextureManager a NULL
{
}

CUOCEngine::~CUOCEngine()
{
}

CUOCEngine * CUOCEngine::GetEngine()
{
	//TO DO : Implementar el patr�n Singleton, si la instancia m_UOCEngine es NULL crearla
	//TO DO : Devolver la instancia m_UOCEngine
}

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	//TO DO : Construye la variable miembro m_RenderManager
	//TO DO : Llama al m�todo Init de la variable miembro m_RenderManager

	//TO DO : Construye la variable miembro m_InputManager
	//TO DO : Construye la variable miembro m_EffectManager

	//TO DO : Construye la variable miembro m_DebugRender pasando el par�metro el Device de la variable miembro m_RenderManager

	//TO DO : Construye la variable miembro m_CameraManager
	//TO DO : Llama al m�todo Load de la variable miemtro m_CameraManager para cargar el fichero xml "./DATA/XML/cameras.xml"

	//TO DO : Construye la variable miembro m_FBXManager
	//TO DO : Construye la variable miembro m_RenderableObjectManager
	//TO DO : Construye la variable miembro m_TextureManager
	//TO DO : Inicializa la variable miembro m_PreviousTime asign�ndole el valor que devuelve la funci�n timeGetTime()
}

void CUOCEngine::Update()
{
	//TO DO : Calcula el elapsed time del frame, para ello recoges el tiempo actual con la funci�n timeGetTime() y le decrementamos el m_PreviousTime. Este valor se calcula en milisegundos y lo transformamos en segundos multiplicando por 0.001f
	//TO DO : Asignamos a la variable m_PreviousTime el tiempo actual de este frame que hemos capturado en el TO DO anterior

	//TO DO : Llamamos al m�todo Update de la variable miembro m_InputManager para actualizar el Input

	CCameraController *l_CameraController=m_CameraManager->GetCameraController("player");
	
	CKeyboardInput *l_KeyboardInput=m_InputManager->GetKeyboard();

	//TO DO : Si la tecla DIK_TAB se pulsa en este frame (utilizamos el m�todo KeyBecomesPressed de la instancia del KeyboardInput l_KeyboardInput), cambiamos el controlador de c�mara que se utiliza para pintar con el m�todo ChangeVision del m_CameraManager
	//TO DO : Si la tecla DIK_C se pulsa en este frame, cambiamos el controlador de c�mara que se utiliza para control con el m�todo ChangeControl del m_CameraManager
	//TO DO : Actualizamos el m_CameraManager llamando al m�todo Update
	//TO DO : Actualizamos el m_RenderableObjectManager llamando al m�todo Update
}

void CUOCEngine::Render()
{
	//TO DO : Llamar al m�todo BeginRenderDX de la instancia m_RenderManager
	ID3D11DeviceContext *l_DeviceContext=m_RenderManager->GetDeviceContext();

	//TO DO : Si debemos pintar en modo s�lido (utilizamos el m�tod GetPaintSolid de la clase m_RenderManager), establecemos el renderstate de s�lido utilizando el m�todo SetSolidRenderState de la clase m_RenderManager
	//TO DO : En caso contrario establecemos el render state en modo alambre utilizando el m�todo SetWireframeRenderState de la clase m_RenderManager
	//TO DO : Recoger la matriz de view de la c�mara de la variable miembro m_CameraManager
	//TO DO : Recoger la matriz de proyecci�n de la c�mara de la variable miembro m_CameraManager
	//TO DO : Establecer la variable miembro m_View de la variable miembro est�tica m_SceneConstantBufferParameters de la clase CEffectManager, el valor ser� la matriz transpuesta de la matriz de View que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la funci�n de DirectX XMMatrixTranspose
	//TO DO : Establecer la variable miembro m_Projection de la variable miembro est�tica m_SceneConstantBufferParameters de la clase CEffectManager, el valor ser� la matriz transpuesta de la matriz de Projection que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la funci�n de DirectX XMMatrixTranspose
	//TO DO : Establecer las constantes de escena en la variable miembro m_EffectManager utilizando el m�todo SetSceneConstantBuffer
	//TO DO : Llamar al m�todo Render de la variable miembro m_RenderableObjectManager

	
	if(m_RenderManager->DrawAxisGrid())
	{
		//TO DO : Crear una variable de tipo XMMATRIX que contendr� la matriz de mundo y asignarle el valor identidad mediante la funci�n DirectX:::XMMatrixIdentity
		//TO DO : Establecer en la variable miembro m_World de la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager, estableceremos la matriz transpuesta de la variable de mundo que hemos creado en el TO DO anterior
		//TO DO : Llamar al m�todo SetObjectConstantBuffer de la variable miembro m_EffectManager para establecer las constantes de objeto
		//TO DO : Llamar al m�todo DrawAxis de la variable miembro m_DebugRender con un Size de 8.0f
		//TO DO : Llamar al m�todo DrawGrid de la variable miembro m_DebugRender con un Size de 1.0f y color blanco
		//TO DO : Llamar al m�todo DrawCube de la variable miembro m_DebugRender con un Size de 3.0f y color blanco
		//TO DO : Llamar al m�todo DrawSphere de la variable miembro m_DebugRender con un Size de 0.5f y color blanco
	}

	//TO DO : Llamar al m�todo EndRenderDX de la instancia m_RenderManager
}

void CUOCEngine::Destroy()
{
	//TO DO : Destruir la variable miembro m_DebugRender utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_InputManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CameraManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_EffectManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_FBXManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_RenderableObjectManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_TextureManager utilizando la macro CHECKED_DELETE
	//TO DO : Llamar al m�todo Destroy de la variable miembro m_RenderManager
	//TO DO : Destruir la variable miembro m_RenderManager utilizando la macro CHECKED_DELETE
}
