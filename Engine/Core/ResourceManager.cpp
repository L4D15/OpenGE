#include "Engine/Core/ResourceManager.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#ifdef __APPLE__
  #include <mach-o/dyld.h>
#endif

// Nickname the namespace
namespace fs = boost::filesystem;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

std::string ResourceManager::GetWorkingPath()
{
	return fs::current_path().string();
}

std::string ResourceManager::GetPath(std::string pathToFile)
{
	std::string absolutePath;

    fs::path currentPath;

    currentPath = fs::current_path();

    absolutePath.append(currentPath.string());
    absolutePath.append("/");

#ifdef __APPLE__
    char path[FILENAME_MAX];
    uint32_t size = sizeof(path);
    _NSGetExecutablePath(path, &size);

    absolutePath = path;

    // Take just the part we need
    absolutePath = absolutePath.substr(0, absolutePath.find("/MacOS/") + 1);
    absolutePath.append("/Resources/");

#elif __linux

#elif _WIN32

#elif _WIN64

#else
    STUBBED("ResourceManage::getPath - Missing code for this platform.");
#endif

    absolutePath.append(pathToFile);

    std::cout << absolutePath << std::endl;

    return absolutePath;
}

template <typename T>
T& ResourceManager::GetAsset(const std::string filePath)
{
    int posLastSlash;
    int posLastDot;

    posLastSlash = filePath.find_last_of('/');
    posLastDot = filePath.find_last_of('.');

    std::string name;

    name = filePath.substr(posLastSlash + 1, posLastDot);

    std::map<std::string, Asset*>::iterator mappedAsset;

    mappedAsset = assetMapper.find(name);

    if (mappedAsset != assetMapper.end())
    {
        return (* static_cast<T*>(mappedAsset->second));
    }
    else
    {
        // Load the asset
        T* asset;

        asset = new T(name, filePath);

        std::pair<std::string, Asset*> newAsset(name, asset);

        assetMapper.insert(newAsset);

        return (* asset);
    }
}
