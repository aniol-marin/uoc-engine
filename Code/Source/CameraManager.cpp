#include "CameraManager.h"
#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "CameraController.h"
#include "Frustum.h"
#include "InputManager.h"

CCameraManager::CCameraManager()
{
	//TO DO : Construir la instancia del Frustum de la c�mara
	//TO DO : Construir una instancia de CFPSCameraController e insertarla en la variable miembro m_CameraControllers con nombre "player"
	//TO DO : Establecer la varaible m_CameraControllerControl a "player"
	//TO DO : Establecer la varaible m_CameraControllerVision a "player"
}

CCameraManager::~CCameraManager()
{
	//TO DO : Recorrer todo el mapa de CameraController y eliminar los controladores de c�mara utilizando la macro CHECKED_DELETE
	//TO DO : Eliminar la instancia de frustum de c�mara utilizando la macro CHECKED_DELETE
}

void CCameraManager::AddCameraController(TCameraControllerType CameraControllerType, const std::string &Name, const XMFLOAT3 &Position, float Zoom)
{
	CCameraController *l_CameraController=NULL;
		
	switch(CameraControllerType)
	{
		case SPHERICAL_CAMERA_CONTROLLER:
			//TO DO : Construir una instancia de tipo CSphericalCameraController en la variable l_CameraController
			//TO DO : Establecer el Zoom en el controlador de c�mara utilizando el m�todo SetZoom de la clase CSphericalCameraController pas�ndole el par�metro Zoom
			break;
		case FPS_CAMERA_CONTROLLER:
			//TO DO : Construir una instancia de tipo CFPSCameraController en la variable l_CameraController
			break;
	}
	//TO DO : Establecer la posici�n en el controlador de c�mara utilizando el m�todo SetPosition 
	//TO DO : Insertar el controlador de c�mara en la variable miembro m_CameraControllers seg�n la clave Name
}

void CCameraManager::ChangeVision()
{
	//TO DO : Utilizar el m�todo find de la instancia m_CameraControllers para encontrar el controlador de c�mara m_CameraControllerControl
	//TO DO : Si encontramos el controlador de c�mara avanzamos al siguiente controlador de c�mara
	//TO DO : Si el controlador de c�mara no es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del iterador
	//TO DO : Si el controlador de c�mara es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del begin m_CameraControllers
}

void CCameraManager::onStartElement(const std::string &elem, MKeyValue &atts)
{
	if(elem=="SphericalCameraController")
    {
		float l_Zoom;
		XMFLOAT3 l_Position;
		std::string l_Name=atts["name"];
		std::string l_PosX=atts["posx"];
		std::string l_PosY=atts["posy"];
		std::string l_PosZ=atts["posz"];
		std::string l_ZoomStr=atts["zoom"];
	  	  
		sscanf_s(l_PosX.c_str(),"%f",&l_Position.x);
		sscanf_s(l_PosY.c_str(),"%f",&l_Position.y);
		sscanf_s(l_PosZ.c_str(),"%f",&l_Position.z);
		sscanf_s(l_ZoomStr.c_str(),"%f",&l_Zoom);
	  
		//TO DO : A�adir un controlador de c�mara esf�rica utilizando el m�todo AddCameraController
    }
	else if(elem=="FPSCameraController")
    {
		//TO DO : Recoger el nombre del controlador de c�mara de los atributos del xml name
		//NOTA : Basarse en c�mo recoge la posici�n de los atributos xml en la c�mara de tipo SphericalCameraController
		//TO DO : Recoger la posici�n x del controlador de c�mara de los atributos del xml posx
		//TO DO : Recoger la posici�n y del controlador de c�mara de los atributos del xml posy
		//TO DO : Recoger la posici�n z del controlador de c�mara de los atributos del xml posz
		//TO DO : A�adir un controlador de c�mara FPS utilizando el m�todo AddCameraController
    }
}

bool CCameraManager::SphereVisible(const XMFLOAT3 &Center, float Radius) const
{
	//TO DO : Utiliza el m�todo SphereVisible de la instancia m_Frustum para saber si una esfera es visible por el frustum de c�mara
}

bool CCameraManager::BoxVisible( const XMFLOAT3 &max, const XMFLOAT3 &min ) const
{
	//TO DO : Utiliza el m�todo BoxVisible de la instancia m_Frustum para saber si una caja es visible por el frustum de c�mara
}

CCameraController * CCameraManager::GetCameraController(const std::string &Name) const
{
	//TO DO : Buscamos el controlador de c�mara utilizando el m�todo find de m_CameraControllers
	//TO DO : Si lo encontramos devolvemos el second del iterador que nos devuelve el m�todo find de m_CameraControllers
	//TO DO : Devuelve NULL en caso de no encontrar el controlador de c�mara
}

void CCameraManager::Update(float ElapsedTime)
{
	//TO DO : Actualiza el controlador de c�mara con nombre m_CameraControllerControl utilizando el m�todo Update
	//TO DO : Establece el controlador de c�mara con nombre m_CameraControllerVision utilizando el m�todo SetCamera
	//TO DO : Llamar al m�todo UpdateFrustumCamera para que se actualice el Frustum de la c�mara
}

void CCameraManager::UpdateFrustumCamera()
{
	//TO DO : Actualiza el frustum de la c�mara llamando al m�todo Update de la variable miembro m_Frustum pas�ndoel las matrices de View y de Proyecci�n de la instancia m_Camera
}

void CCameraManager::Load(const std::string &Filename)
{
	//TO DO : Parsea el fichero xml Filename utilizando el m�todo xmlParseFile
}
