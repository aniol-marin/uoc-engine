#include "AnimatedCoreModel.h"
#include "cal3d/cal3d.h"
#include <string>
#include "defines.h"

CAnimatedCoreModel::CAnimatedCoreModel()
: m_CalCoreModel(NULL)
, m_Name("")
{	
}

CAnimatedCoreModel::~CAnimatedCoreModel()
{
	CHECKED_DELETE( m_CalCoreModel );
}

void CAnimatedCoreModel::onStartElement(const std::string &elem, MKeyValue &atts)
{
	if(elem=="actor")
	{
		m_Name=atts["name"];
		m_CalCoreModel = new CalCoreModel(m_Name.c_str());
		assert(m_CalCoreModel!=NULL);
	}
	else if(elem=="mesh")
	{
		m_MeshFilename=atts["filename"];
		bool l_Ok=LoadMesh();
		assert(l_Ok);
	}
	else if(elem=="skeleton")
	{
		m_SkeletonFilename=atts["filename"];
		bool l_Ok=LoadSkeleton();
		assert(l_Ok);
	}
	else if(elem=="texture")
	{
		m_TextureFilenameList.push_back(atts["filename"]);
	}
	else if(elem=="animation")
	{
		std::string l_Name=atts["name"];
		std::string l_Filename=atts["filename"];
		bool l_Ok=LoadAnimation(l_Name,l_Filename);
		assert(l_Ok);
	}
}

void CAnimatedCoreModel::Load(const std::string &Path)
{
	m_Path=Path;
	xmlParseFile(Path+"actor.xml");
}

bool CAnimatedCoreModel::LoadMesh()
{
	std::string l_CompletePath=m_Path;
	l_CompletePath+=m_MeshFilename;

	assert(m_CalCoreModel!=NULL);
	if(m_CalCoreModel->loadCoreMesh(l_CompletePath) == -1)
		return false;
	return true;
}

bool CAnimatedCoreModel::LoadSkeleton()
{
	std::string l_CompletePath=m_Path;
	l_CompletePath+=m_SkeletonFilename;

	assert(m_CalCoreModel!=NULL);
	if(!m_CalCoreModel->loadCoreSkeleton(l_CompletePath))
		return false;
	return true;
}

bool CAnimatedCoreModel::LoadAnimation(const std::string &Name, const std::string &Filename)
{
	std::string l_CompletePath=m_Path;
	l_CompletePath+=Filename;

	assert(m_CalCoreModel!=NULL);
	if(m_CalCoreModel->loadCoreAnimation(l_CompletePath, Name) == -1)
		return false;
	return true;
}

CalCoreModel *CAnimatedCoreModel::GetCoreModel()
{
	return m_CalCoreModel;
}

const std::string & CAnimatedCoreModel::GetTextureName(size_t id)
{
	assert( id >= 0 && id <m_TextureFilenameList.size() );
	return m_TextureFilenameList[ id ];
}
