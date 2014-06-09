#ifndef OPENGE_RESOURCEMANAGER_H
#define OPENGE_RESOURCEMANAGER_H

#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::string				GetPath(std::string pathToFile);
	std::string				GetWorkingPath();

private:
	
};

#endif // OPENGE_RESOURCEMANAGER_H