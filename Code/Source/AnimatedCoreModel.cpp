#include "AnimatedCoreModel.h"
#include "cal3d/cal3d.h"
#include <string>
#include "defines.h"

CAnimatedCoreModel::CAnimatedCoreModel()
//TO DO : Inicializar la variable miembro m_CalCoreModel a NULL
//TO DO : Inicializar la variable miembro m_Name a ""
{	
}

CAnimatedCoreModel::~CAnimatedCoreModel()
{
	//TO DO : Destruir la variable miembro m_CalCoreModel utilizando la macro CHECKED_DELETE
}

void CAnimatedCoreModel::onStartElement(const std::string &elem, MKeyValue &atts)
{
	//TO DO : Si el elem es igual a "actor"
	if ()
	{
		//TO DO : Asignar en m_Name el valor del mapa atts seg�n la key "name"
		//TO DO : Construir la variable miembro m_CalCoreModel de tipo CalCoreModel seg�n el m_Name
	}
	//TO DO : Si el elem es igual a "mesh"
	else if ()
	{
		//TO DO : Asignar en m_MeshFilename el valor del mapa atts seg�n la key "filename"
		//TO DO : Llamar al m�todo LoadMesh
	}
	//TO DO : Si el elem es igual a "skeleton"
	else if ()
	{
		//TO DO : Asignar en m_SkeletonFilename el valor del mapa atts seg�n la key "filename"
		//TO DO : Llamar al m�todo LoadSkeleton
	}
	//TO DO : Si el elem es igual a "texture"
	else if ()
	{
		//TO DO : A�adir el nombre de la textura que se encuentra en el valor del mapa atts seg�n la key "filename" en el vector de texturas m_TextureFilenameList utilizando el m�todo push_back
	}
	//TO DO : Si el elem es igual a "animation"
	else if ()
	{
		std::string l_Name;
		std::string l_Filename;
		//TO DO : Asignar en l_Name el valor del mapa atts seg�n la key "name"
		//TO DO : Asignar en l_Filename el valor del mapa atts seg�n la key "filename"
		//TO DO : Llamar al m�todo LoadAnimation
	}
}

void CAnimatedCoreModel::Load(const std::string &Path)
{
	//TO DO : Asignar el valor de Path en m_Path
	//TO DO : Llamar al m�todo xmlParseFile pas�ndole el Path + "actor.xml"
}

bool CAnimatedCoreModel::LoadMesh()
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y m_MeshFilename
	//TO DO : Si la llamada al m�todo loadCoreMesh de la instancia m_CalCoreModel es igual a -1 devolver false si no devolver true
}

bool CAnimatedCoreModel::LoadSkeleton()
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y m_SkeletonFilename
	//TO DO : Si la llamada al m�todo loadCoreSkeleton de la instancia m_CalCoreModel es false devolver false si no devolver true
}

bool CAnimatedCoreModel::LoadAnimation(const std::string &Name, const std::string &Filename)
{
	std::string l_CompletePath;
	//TO DO : Asignar a l_CompletePath la suma de los strings m_Path y Filename
	//TO DO : Si la llamada al m�todo loadCoreAnimation de la instancia m_CalCoreModel es igual a -1 devolver false si no devolver true
}

CalCoreModel *CAnimatedCoreModel::GetCoreModel()
{
	//TO DO : Devolver la variable miembro m_CalCoreModel
}

const std::string & CAnimatedCoreModel::GetTextureName(size_t id)
{
	//TO DO : Devolver el nombre de textura que se encuentra en el vector de texturas m_TextureFilenameList seg�n el id
}
