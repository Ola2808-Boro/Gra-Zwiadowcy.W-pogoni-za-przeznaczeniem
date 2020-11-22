#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "Ola";
	this->resolutions = VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->verticalSync1 = true;
	contextSettings.antialiasingLevel = 0;
	this->frameRateLimit = 120;
	videModes = VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(string path)
	{
		ofstream ofs(path);
		if (ofs.is_open())
		{
			ofs << title;
			ofs << resolutions.width << " " << resolutions.height;
			ofs << fullscreen;
			ofs << frameRateLimit;
			ofs << verticalSync;
			ofs << verticalSync1;
			ofs << contextSettings.antialiasingLevel;

		}
		ofs.clear();
		ofs.seekp(0);//beginning
		ofs.close();
	}
void GraphicsSettings::loadToFile(string path)
	{
		ifstream ifs(path);
		if (ifs.is_open())
		{
			getline(ifs, title);
			ifs >> resolutions.width >> resolutions.height;
			ifs >> fullscreen;
			ifs >> frameRateLimit;
			ifs >> verticalSync;
			ifs >> verticalSync1;
			ifs >> contextSettings.antialiasingLevel;

		}
		ifs.clear();
		ifs.seekg(0);//beginning
		ifs.close();
	}
