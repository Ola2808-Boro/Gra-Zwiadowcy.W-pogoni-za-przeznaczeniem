#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "PausedMenu.h"
#include "TileMap.h"

//class PausedMenu;
//class Player;
//class TileMap;
//class View;
//class Font;
//class RenderTexture;

class GameStates:public State//inherit 
{
private:
	View view;
	RenderTexture renderTexture;
	Sprite renderSprite;
	Player *player;
	Font font;
	PausedMenu *pauseMenu;
	TileMap *tileMap;

	void iniDefferedRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void InitFonts();
	void initPauseMenu();
	void initTileMap();


public:
	GameStates(StateData* stateData);
	virtual ~GameStates();
	void updateView(const float& dt);
	void update(const float& dt);
	void updateTileMap(const float& dt);
	void render(RenderTarget* target=nullptr);
	void updatePlayerInput(const float& dt);//W,S,A,D
	void updateInput(const float dt);//przyciski
	void updatePauseMenuButtons();
	Texture temp;//pomoc do zaladowania struktury
};
#endif 
