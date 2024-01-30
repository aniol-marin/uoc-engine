#include <windows.h>
#include "cal3d\loader.h"
#include "AnimatedModelManager.h"
#include <string>
#include "defines.h"
#include "AnimatedCoreModel.h"
#include <assert.h>

CAnimatedModelManager::CAnimatedModelManager()
{
	CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);
}

CAnimatedModelManager::~CAnimatedModelManager()
{
	CleanUp();
}

void CAnimatedModelManager::CleanUp()
{
	for(TActorManagerIterator it=m_ActorManagerMap.begin();it!=m_ActorManagerMap.end();++it)
	{
		CHECKED_DELETE(it->second);
	}
	m_ActorManagerMap.clear();
}

CAnimatedCoreModel *CAnimatedModelManager::GetActor(const std::string &ActorName, const std::string &Path)
{
	CAnimatedCoreModel *l_CoreActor=NULL;
	if(m_ActorManagerMap.find(ActorName)!=m_ActorManagerMap.end())
		l_CoreActor=m_ActorManagerMap[ActorName];
	else
	{
		assert(Path!="");
		l_CoreActor=new CAnimatedCoreModel;
		m_ActorManagerMap[ActorName]=l_CoreActor;
		l_CoreActor->Load(Path);
	}
	assert(l_CoreActor!=NULL);
	return l_CoreActor;
}
