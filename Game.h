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
	stack <State*> states;//stos, w którym bede przechowywałam obiekty klasy State
	map<string, int> supportedKeys;//pomocne 
	float gridSize;

	//init 6
	void initVariables();
	void initWindow();
	void initStates();
	void initStateData();
	void initKeys();
	void initGraphicsSettings();
	

public:
	//konstruktor
	Game();
	//destruktor
	virtual ~Game();
	//funkcje update
	void updateSFMLEvent();
	void update();
	void updateDT();

	//funkcje render
	void render();

	//funckje run i end
	void endApplication();
	void run();


};
#endif 

