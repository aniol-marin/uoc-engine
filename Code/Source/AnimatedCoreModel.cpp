#include "AnimatedCoreModel.h"
#include "cal3d/cal3d.h"
#include <string>
#include "defines.h"

CAnimatedCoreModel::CAnimatedCoreModel() :
	//TO DO : Inicializar la variable miembro m_CalCoreModel a NULL
	m_CalCoreModel{ nullptr },
	//TO DO : Inicializar la variable miembro m_Name a ""
	m_Name{""}
{
}

CAnimatedCoreModel::~CAnimatedCoreModel()
{
	//TO DO : Destruir la variable miembro m_CalCoreModel utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_CalCoreModel);
}

void CAnimatedCoreModel::onStartElement(const std::string &elem, MKeyValue &atts)
{
	const std::string nameKey = "name";
	const std::string actorKey = "actor";
	const std::string meshKey = "mesh";
	const std::string skeletonKey = "skeleton";
	const std::string textureKey = "texture";
	const std::string animationKey = "animation";
	const std::string fileNameKey = "filename";

	//TO DO : Si el elem es igual a "actor"
	if (elem == actorKey)
	{
		//TO DO : Asignar en m_Name el valor del mapa atts según la key "name"
		m_Name = atts[nameKey];
		//TO DO : Construir la variable miembro m_CalCoreModel de tipo CalCoreModel según el m_Name
		m_CalCoreModel = new CalCoreModel(m_Name);
	}
	//TO DO : Si el elem es igual a "mesh"
	else if (elem == meshKey)
	{
		//TO DO : Asignar en m_MeshFilename el valor del mapa atts según la key "filename"
		m_MeshFilename = fileNameKey;
		//TO DO : Llamar al método LoadMesh
		const bool _ = LoadMesh();
	}
	//TO DO : Si el elem es igual a "skeleton"
	else if (elem == skeletonKey)
	{
		//TO DO : Asignar en m_SkeletonFilename el valor del mapa atts según la key "filename"
		m_SkeletonFilename = atts[fileNameKey];
		//TO DO : Llamar al método LoadSkeleton
		const bool _ = LoadSkeleton();
	}
	//TO DO : Si el elem es igual a "texture"
	else if (elem == textureKey)
	{
		//TO DO : Añadir el nombre de la textura que se encuentra en el valor del mapa atts según la key "filename" en el vector de texturas m_TextureFilenameList utilizando el método push_back
		m_TextureFilenameList.push_back(fileNameKey);
	}
	//TO DO : Si el elem es igual a "animation"
	else if (elem == animationKey)
	{
		std::string l_Name;
		std::string l_Filename;
		//TO DO : Asignar en l_Name el valor del mapa atts según la key "name"
		l_Name = nameKey;
		//TO DO : Asignar en l_Filename el valor del mapa atts según la key "filename"
		l_Filename = fileNameKey;
		//TO DO : Llamar al método LoadAnimation
		const bool _ = LoadAnimation(l_Name, l_Filename);
	}
}

void CAnimatedCoreModel::Load(const std::string &Path)
{
	//TO DO : Asignar el valor de Path en m_Path
	m_Path = Path;
	std::string l_ActorFileName{ "actor.xml" };
	//TO DO : Llamar al método xmlParseFile pasándole el Path + "actor.xml"
	const bool _ = xmlParseFile(m_Path + l_ActorFileName);
}

bool CAnimatedCoreModel::LoadMesh()
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y m_MeshFilename
	l_CompletePath = m_Path + m_MeshFilename;
	//TO DO : Si la llamada al método loadCoreMesh de la instancia m_CalCoreModel es igual a -1 devolver false si no devolver true
	return static_cast<bool>(m_CalCoreModel->loadCoreMesh(l_CompletePath) + 1);
}

bool CAnimatedCoreModel::LoadSkeleton()
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y m_SkeletonFilename
	l_CompletePath = m_Path + m_SkeletonFilename;
	//TO DO : Si la llamada al método loadCoreSkeleton de la instancia m_CalCoreModel es false devolver false si no devolver true
	return static_cast<bool>(m_CalCoreModel->loadCoreSkeleton(l_CompletePath) + 1);
}

bool CAnimatedCoreModel::LoadAnimation(const std::string &Name, const std::string &Filename)
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y Filename
	l_CompletePath = m_Path + Filename;
	//TO DO : Si la llamada al método loadCoreAnimation de la instancia m_CalCoreModel es igual a -1 devolver false si no devolver true
	return static_cast<bool>(m_CalCoreModel->loadCoreAnimation(l_CompletePath) + 1);
}

CalCoreModel *CAnimatedCoreModel::GetCoreModel()
{
	//TO DO : Devolver la variable miembro m_CalCoreModel
	return m_CalCoreModel;
}

const std::string & CAnimatedCoreModel::GetTextureName(size_t id)
{
	//TO DO : Devolver el nombre de textura que se encuentra en el vector de texturas m_TextureFilenameList según el id
	return m_TextureFilenameList[id];
}
