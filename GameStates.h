#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "PausedMenu.h"
#include "TileMap.h"


class GameStates:public State//inherit 
{
private:
	Player *player;
	Font font;
	PausedMenu *pauseMenu;
	TileMap tilemap;
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void InitFonts();
	void initPauseMenu();


public:
	GameStates(RenderWindow *window,GraphicsSettings gfxSettings, map <string, int>* supportedKeys, stack <State*>* states);
	virtual ~GameStates();
	void update(const float& dt);
	void render(RenderTarget* target=nullptr);
	void updatePlayerInput(const float& dt);//W,S,A,D
	void updateInput(const float dt);//przyciski
	void updatePauseMenuButtons();
	Texture temp;//pomoc do zaladowania struktury
};
#endif 
