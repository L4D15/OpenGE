#ifndef OPENGE_ASSET_H
#define OPENGE_ASSET_H

#include <string>
#include "Engine/Libraries/Libraries.hpp"

enum class AssetType { Sprite, Audio, Text, Texture, Script, None};

class ResourceManager;

class Asset
{
protected:
	Asset(const std::string name, const std::string filePath) : name(name), filePath(filePath) { usage = 1; }
	virtual ~Asset() { }

	inline Uint16				GetUsage () const { return usage; }
	inline void					NotifyUse() { ++usage; }
	inline void					NotifyRelease() { if (usage > 0) --usage; }

public:
	virtual std::string			ToString() const = 0;

public:
	std::string					name;
	std::string					filePath;

protected:
	Uint16						usage;

	friend class ResourceManager;
};

#endif // OPENGE_ASSET_H