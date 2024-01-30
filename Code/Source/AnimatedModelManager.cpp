#include <windows.h>
#include "cal3d\loader.h"
#include "AnimatedModelManager.h"
#include <string>
#include "defines.h"
#include "AnimatedCoreModel.h"
#include <assert.h>

CAnimatedModelManager::CAnimatedModelManager()
{
	//TO DO : Forzar a Cal3D para que se carguen los modelos animados de Cal3D rotados en el eje X utilizando el método estático setLoadingMode de la clase CalLoader
	CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);
}

CAnimatedModelManager::~CAnimatedModelManager()
{
	//TO DO : Llamar al método CleanUp
	CleanUp();
}

void CAnimatedModelManager::CleanUp()
{
	//TO DO : Recorrer el mapa m_ActorManagerMap
	for (auto& elem : m_ActorManagerMap)
	{
		//TO DO : Destruir el valor del mapa que estamos recorriendo en el for utilizando la macro CHECKED_DELETE
		CHECKED_DELETE(elem.second);
	}
	//TO DO : Limpiamos el mapa m_ActorManagerMap utilizando el método clear
	m_ActorManagerMap.clear();
}

CAnimatedCoreModel *CAnimatedModelManager::GetActor(const std::string &ActorName, const std::string &Path)
{
	CAnimatedCoreModel *l_CoreActor;
	//TO DO : Si el ActorName existe en el mapa m_ActorManagerMap (es diferente del end)
	if (m_ActorManagerMap.find(ActorName) != m_ActorManagerMap.end())
		l_CoreActor = m_ActorManagerMap[ActorName];
		//TO DO : Asignamos en l_CoreActor el valor del mapa m_ActorManagerMap según la clave ActorName
	else
	{
		//TO DO : Construir la instancia l_CoreActor de tipo CAnimatedCoreModel
		l_CoreActor = new CAnimatedCoreModel();
		//TO DO : Insertar en el mapa m_ActorManagerMap según la clave ActorName el valor l_CoreActor
		m_ActorManagerMap.insert(CAnimatedModelManager::TActorManagerMap::value_type(ActorName, l_CoreActor));
		//TO DO : Llamar al método Load de l_CoreActor
		l_CoreActor->Load(Path);
	}
	//TO DO : Devolver la instancia l_CoreActor
	return l_CoreActor;
}
