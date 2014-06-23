#include "Engine/Core/ResourceManager.hpp"
#include "Engine/Assets/Sprite.hpp"
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
  // Load the Missing_Image sprite
}

ResourceManager::~ResourceManager()
{
    for (auto asset : assetMapper)
    {
        delete asset.second;
    }
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
    absolutePath.append("Resources/");

#else
#if __linux

#else
#if _WIN32

#else
#if _WIN64

#else
    STUBBED("ResourceManage::getPath - Missing code for this platform.");
#endif
#endif
#endif
#endif

    absolutePath.append(pathToFile);

    return absolutePath;
}

luabind::scope ResourceManager::RegisterForScripting()
{
    return
            luabind::class_<ResourceManager>("ResourceManager")
                .def("GetSprite", &ResourceManager::GetAsset<Sprite>)
            ;
}
