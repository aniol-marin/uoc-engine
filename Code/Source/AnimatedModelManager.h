#ifndef ANIMATEDMODELMANAGER_H
#define ANIMATEDMODELMANAGER_H

class CalCoreModel;

#include <string>
#include <map>

class CAnimatedCoreModel;

class CAnimatedModelManager
{
private:
	typedef std::map<std::string, CAnimatedCoreModel *>	TActorManagerMap;
	typedef TActorManagerMap::iterator				TActorManagerIterator;

	TActorManagerMap								m_ActorManagerMap;
public:
	CAnimatedModelManager();
	virtual ~CAnimatedModelManager();
	CAnimatedCoreModel *GetActor(const std::string &ActorName, const std::string &Path);
	void CleanUp();
};

#endif
