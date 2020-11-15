#ifndef GAMESTATES_H
#define GAMESTATES_H

#include"State.h"//dobrze
#include "Player.h"
class GameStates:public State//inherit 
{
private:
	Player *player;
	void initKeybinds();
	void initTextures();
	void initPlayers();


public:
	GameStates(RenderWindow *window, map <string, int>* supportedKeys, stack <State*>* states);
	virtual ~GameStates();
	void update(const float& dt);
	void render(RenderTarget* target=nullptr);
	void updateInput(const float& dt);
	Texture temp;//pomoc do zaladowania struktury
};
#endif 
