#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "PausedMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"
#include "Player2.h"
#include "Fighter.h"

#include "AllEnemies.h"
#include "TextTagSystem.h"



class GameStates:public State,public TileMap//dziedzicznie
{
private:
	View view;
	Vector2i viewGridPosition;
	RenderTexture renderTexture;
	Sprite renderSprite;

	
	Text debugText;

	Player *player;
	Player2* player2;
	Fighter* fighter;
	
	PlayerGui* playerGui;
	Enemy *enemy;
	Rat* rat;
	
	EnemySystem* enemysystem;
	EnemySpawner* enemySpawner;

	vector<Enemy*> activeEnemies;


	Font font;
	PausedMenu *pauseMenu;
	TileMap *tileMap;

	Clock keyTimer;
	float keyTimeMax;


	TextTagSystem* tts;

	//14 funkcji sprawdzic z konstruktorem
	void iniDefferedRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void InitFonts();
	void initPauseMenu();
	void initTileMap();
	void initPlayerGui();
	void initEnemySystem();
	void initSystems();
	void initKeyTime();
	void initDebugText();
	void initEnemy();
	void initSpawn();

public:
	//konstruktor
	GameStates(StateData* stateData);
	//destruktor
	virtual ~GameStates();

	//wszystkie update
	void updateView(const float& dt);
	void update(const float& dt);
	void updateTileMap(Entity* entity, const float& dt);
	void updatePlayerInput(const float& dt);//W,S,A,D
	void updatePlayerGui(const float& dt);
	void updateInput(const float dt);//przyciski
	void updatePauseMenuButtons();
	void updatePlayer(const float& dt);
	void updateEmemies(const float& dt);
	void updateCombat(Player* player, Player2* player2, const float& dt);
	void updateDebugText(const float dt);
	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateDistance(Player* player,Player2* player2,const float& dt);
	//wszystkie render
	void render(RenderTarget* target = NULL);

	//funkcje dostepu
	const bool getKeyTime();


	Texture temp;//pomoc do zaladowania struktury
};
#endif 

