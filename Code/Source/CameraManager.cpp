#include "CameraManager.h"
#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "CameraController.h"
#include "Frustum.h"
#include "InputManager.h"

constexpr std::string_view g_PlayerString = "player";
constexpr std::string_view g_NameString = "name";
constexpr std::string_view g_PosxString = "posx";
constexpr std::string_view g_PosyString = "posy";
constexpr std::string_view g_PoszString = "posz";

CCameraManager::CCameraManager() :
	//TO DO : Construir la instancia del Frustum de la c�mara
	m_Frustum{ new CFrustum },
	//TO DO : Establecer la varaible m_CameraControllerControl a "player"
	m_CameraControllerControl{ g_PlayerString },
	//TO DO : Establecer la varaible m_CameraControllerVision a "player"
	m_CameraControllerVision{ g_PlayerString },
	m_Camera{},
	m_CameraControllers{}
{
	//TO DO : Construir una instancia de CFPSCameraController e insertarla en la variable miembro m_CameraControllers con nombre "player"
	m_CameraControllers.insert({ g_PlayerString.data(), new CFPSCameraController() });
}

CCameraManager::~CCameraManager()
{
	//TO DO : Recorrer todo el mapa de CameraController y eliminar los controladores de c�mara utilizando la macro CHECKED_DELETE
	for (auto& l_Controller : m_CameraControllers) {
		CHECKED_DELETE(l_Controller.second);
	}
	//TO DO : Eliminar la instancia de frustum de c�mara utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_Frustum);
}

void CCameraManager::AddCameraController(TCameraControllerType CameraControllerType, const std::string& Name, const XMFLOAT3& Position, float Zoom)
{
	CCameraController* l_CameraController{};
	CSphericalCameraController* l_Handle;

	switch (CameraControllerType)
	{
	case SPHERICAL_CAMERA_CONTROLLER:
		//TO DO : Construir una instancia de tipo CSphericalCameraController en la variable l_CameraController
		l_Handle = new CSphericalCameraController();
		l_CameraController = l_Handle;
		//TO DO : Establecer el Zoom en el controlador de c�mara utilizando el m�todo SetZoom de la clase CSphericalCameraController pas�ndole el par�metro Zoom
		l_Handle->SetZoom(Zoom);
		break;
	case FPS_CAMERA_CONTROLLER:
		//TO DO : Construir una instancia de tipo CFPSCameraController en la variable l_CameraController
		l_CameraController = new CFPSCameraController();
		break;
	}
	//TO DO : Establecer la posici�n en el controlador de c�mara utilizando el m�todo SetPosition 
	l_CameraController->SetPosition(Position);
	//TO DO : Insertar el controlador de c�mara en la variable miembro m_CameraControllers seg�n la clave Name
	m_CameraControllers.insert({ Name, l_CameraController });
}

void CCameraManager::ChangeVision()
{
	//TO DO : Utilizar el m�todo find de la instancia m_CameraControllers para encontrar el controlador de c�mara m_CameraControllerControl
	auto l_Handle = m_CameraControllers.find(m_CameraControllerControl);

	//TO DO : Si encontramos el controlador de c�mara avanzamos al siguiente controlador de c�mara
	if (l_Handle != m_CameraControllers.end()) {
		l_Handle = std::next(l_Handle);
	}

	//TO DO : Si el controlador de c�mara no es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del iterador
	if (l_Handle != m_CameraControllers.end()) {
		m_CameraControllerVision = l_Handle->first;
	}
	//TO DO : Si el controlador de c�mara es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del begin m_CameraControllers
	else {
		m_CameraControllerVision = m_CameraControllers.begin()->first;
	}
}

void CCameraManager::onStartElement(const std::string& elem, MKeyValue& atts)
{
	if (elem == "SphericalCameraController")
	{
		float l_Zoom;
		XMFLOAT3 l_Position;
		std::string l_Name = atts["name"];
		std::string l_PosX = atts["posx"];
		std::string l_PosY = atts["posy"];
		std::string l_PosZ = atts["posz"];
		std::string l_ZoomStr = atts["zoom"];

		sscanf_s(l_PosX.c_str(), "%f", &l_Position.x);
		sscanf_s(l_PosY.c_str(), "%f", &l_Position.y);
		sscanf_s(l_PosZ.c_str(), "%f", &l_Position.z);
		sscanf_s(l_ZoomStr.c_str(), "%f", &l_Zoom);

		//TO DO : A�adir un controlador de c�mara esf�rica utilizando el m�todo AddCameraController
		AddCameraController(SPHERICAL_CAMERA_CONTROLLER, l_Name, l_Position, l_Zoom);
	}
	else if (elem == "FPSCameraController")
	{
		//TO DO : Recoger el nombre del controlador de c�mara de los atributos del xml name
		//NOTA : Basarse en c�mo recoge la posici�n de los atributos xml en la c�mara de tipo SphericalCameraController
		const std::string l_Name = atts[g_NameString.data()];
		//TO DO : Recoger la posici�n x del controlador de c�mara de los atributos del xml posx
		const std::string l_PosX = atts[g_PosxString.data()];
		//TO DO : Recoger la posici�n y del controlador de c�mara de los atributos del xml posy
		const std::string l_PosY = atts[g_PosyString.data()];
		//TO DO : Recoger la posici�n z del controlador de c�mara de los atributos del xml posz
		const std::string l_PosZ = atts[g_PoszString.data()];

		XMFLOAT3 l_Position{};
		sscanf_s(l_PosX.c_str(), "%f", &l_Position.x);
		sscanf_s(l_PosY.c_str(), "%f", &l_Position.y);
		sscanf_s(l_PosZ.c_str(), "%f", &l_Position.z);

		//TO DO : A�adir un controlador de c�mara FPS utilizando el m�todo AddCameraController
		AddCameraController(FPS_CAMERA_CONTROLLER, l_Name, l_Position);
	}
}
bool CCameraManager::SphereVisible(const XMFLOAT3& Center, float Radius) const {
	//TO DO : Utiliza el m�todo SphereVisible de la instancia m_Frustum para saber si una esfera es visible por el frustum de c�mara
	return m_Frustum->SphereVisible(Center, Radius);
}

bool CCameraManager::BoxVisible(const XMFLOAT3& max, const XMFLOAT3& min) const
{
	//TO DO : Utiliza el m�todo BoxVisible de la instancia m_Frustum para saber si una caja es visible por el frustum de c�mara
	return m_Frustum->BoxVisible(max, min);
}

CCameraController* CCameraManager::GetCameraController(const std::string& Name) const
{
	CCameraController* l_Result{};

	//TO DO : Buscamos el controlador de c�mara utilizando el m�todo find de m_CameraControllers
	const auto& l_Handle = m_CameraControllers.find(Name);
	//TO DO : Si lo encontramos devolvemos el second del iterador que nos devuelve el m�todo find de m_CameraControllers
	if (l_Handle != m_CameraControllers.end()) {
		l_Result = l_Handle->second;
	}

	//TO DO : Devuelve NULL en caso de no encontrar el controlador de c�mara
	return l_Result;
}

void CCameraManager::Update(float ElapsedTime)
{
	//TO DO : Actualiza el controlador de c�mara con nombre m_CameraControllerControl utilizando el m�todo Update
	GetCameraController(m_CameraControllerControl)->Update(ElapsedTime);
	//TO DO : Establece el controlador de c�mara con nombre m_CameraControllerVision utilizando el m�todo SetCamera
	GetCameraController(m_CameraControllerVision)->SetCamera(&m_Camera);
	//TO DO : Llamar al m�todo UpdateFrustumCamera para que se actualice el Frustum de la c�mara
	UpdateFrustumCamera();
}

void CCameraManager::UpdateFrustumCamera()
{
	//TO DO : Actualiza el frustum de la c�mara llamando al m�todo Update de la variable miembro m_Frustum pas�ndoel las matrices de View y de Proyecci�n de la instancia m_Camera
	m_Frustum->Update(DirectX::XMMatrixMultiply(m_Camera.GetView(), m_Camera.GetProjection()));
}

void CCameraManager::Load(const std::string& Filename)
{
	//TO DO : Parsea el fichero xml Filename utilizando el m�todo xmlParseFile
	const bool _ = xmlParseFile(Filename);
}
