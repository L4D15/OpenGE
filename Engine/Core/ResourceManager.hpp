#ifndef OPENGE_RESOURCEMANAGER_H
#define OPENGE_RESOURCEMANAGER_H

#include <string>
#include "Engine/Assets/Asset.hpp"
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::string				GetPath(std::string pathToFile);
	std::string				GetWorkingPath();

	template <typename T>
	T&						GetAsset(const std::string filePath);

private:
	std::map<std::string,
				Asset*>		assetMapper;
};

#endif // OPENGE_RESOURCEMANAGER_H