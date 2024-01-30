#ifndef ANIMATEDCOREMODEL_H
#define ANIMATEDCOREMODEL_H

#include "XMLParser.h"

#include <vector>

class CalCoreModel;

class CAnimatedCoreModel : public CXMLParser
{
private:
	CalCoreModel							*m_CalCoreModel;
	std::string								m_Name;
	std::string								m_MeshFilename;
	std::string								m_SkeletonFilename;
	std::vector<std::string>				m_TextureFilenameList;
	std::string								m_Path;

	bool LoadMesh();
	bool LoadSkeleton();
	bool LoadAnimation(const std::string &Name, const std::string &Filename);
	void onStartElement(const std::string &elem, MKeyValue &atts);
public:
	CAnimatedCoreModel();
	virtual ~CAnimatedCoreModel();
	CalCoreModel *GetCoreModel();
	const std::string & GetTextureName(size_t id);
	size_t GetNumTextures() const {return m_TextureFilenameList.size();}
	void Load(const std::string &Path);
};

#endif
