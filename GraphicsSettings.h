#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H



class GraphicsSettings
{

public:
	VideoMode resolutions;
	bool fullscreen;
	bool verticalSync;
	bool verticalSync1;
	unsigned frameRateLimit;
	string title;
	ContextSettings contextSettings;
	vector<VideoMode> videModes;

	//Konstruktor
	GraphicsSettings();
	
	//Destruktor


	//Funkcje
	void saveToFile(string path);
		
	void loadToFile(string path);
	

};
#endif // !GRAPHICSSETTINGS_H