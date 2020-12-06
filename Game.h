#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"//dobrze

 class Game
{
private:
	
	GraphicsSettings gfxSettings;
	RenderWindow *window;
	Event sfEvent;
	StateData stateData;
	Clock dtClock;// speed doesn't depend on frame
	float dt;
	stack <State*> states;//stos
	map<string, int> supportedKeys;//pomocne 
	float gridSize;
	//init
	void initVariables();
	void initWindow();
	void initStates();
	void initStateData();
	void initKeys();
	void initGraphicsSettings();
	

public:
	Game();
	virtual ~Game();
	void updateSFMLEvent();
	void update();
	void run();
	void render();
	void endApplication();
	void updateDT();//


};
#endif 



