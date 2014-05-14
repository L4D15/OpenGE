#ifndef OPENGE_SETTINGS_H
#define OPENGE_SETTINGS_H

class Settings
{
public:
	Settings()
	{
		maxFPS = 60;
	}

	~Settings()
	{

	}

public:
	int				maxFPS;
	
};

#endif