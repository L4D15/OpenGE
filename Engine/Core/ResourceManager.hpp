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
	T&						GetAsset(std::string filePath)
	{
	    int posLastSlash;
	    int posLastDot;

	    posLastSlash = filePath.find_last_of('/');
	    posLastDot = filePath.find_last_of('.');

	    std::string name;

	    name = filePath.substr(posLastSlash + 1, posLastDot);

	    std::pair<  std::multimap<std::string, Asset*>::iterator,
	                std::multimap<std::string, Asset*>::iterator> range;

	    range = assetMapper.equal_range(name);

	    for (std::multimap<std::string, Asset*>::iterator it = range.first; it != range.second; ++it)
	    {
	        if (dynamic_cast<T*>(it->second) != 0)
	        {
	            return (* static_cast<T*>(it->second));
	        }
	    }

	    // If we get here means the asset is not loaded, so load it
	    T* asset;

	    asset = new T(name, filePath);

	    std::pair<std::string, Asset*> newAsset(name, asset);

	    assetMapper.insert(newAsset);

	    return (* asset);
	}

private:
	std::multimap<
		std::string,
		Asset*>				assetMapper;
};

#endif // OPENGE_RESOURCEMANAGER_H