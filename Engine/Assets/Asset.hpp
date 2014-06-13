#ifndef OPENGE_ASSET_H
#define OPENGE_ASSET_H

#include <string>
#include "Engine/Libraries/Libraries.hpp"

class Asset
{
protected:
	Asset(const std::string name) : name(name) { };
	virtual ~Asset();

	inline Uint16 const Usage() { return usage; }
	inline void			NotifyUse() { ++usage; }
	inline void			NotifyRelease() { if (usage > 0) --usage; }

public:
	std::name			name;

protected:
	Uint16				usage;
};

#endif // OPENGE_ASSET_H