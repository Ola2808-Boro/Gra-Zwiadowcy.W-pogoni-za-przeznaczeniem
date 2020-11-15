#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"//dobrze

 class Game
{
private:
	RenderWindow *window;
	Event sfEvent;
	vector <VideoMode> videomodes;
	ContextSettings windowSettings;
	bool fullscreen = false;
	Clock dtClock;// speed doesn't depend on frame
	float dt;
	stack <State*> states;//stos
	map<string, int> supportedKeys;//pomocne 

	//init
	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();
	

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


