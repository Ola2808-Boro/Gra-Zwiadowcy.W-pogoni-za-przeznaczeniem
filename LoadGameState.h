#ifndef LOADGAMESTATE_H
#define LOADGAMESTATE_H

#include "State.h"

#include "PausedMenu.h"
#include "GameOverState.h"
#include "HelpState.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"
#include "Enemy.h"
#include "Fighter.h"
#include "AlyssMainwaring.h"
#include "HoraceAltman.h"
#include "WillTreaty.h"

#include "AllEnemies.h"
#include "TextTagSystem.h"



class LoadGameState :public State, public TileMap//dziedzicznie
{
private:
	View view;
	Vector2i viewGridPosition;
	RenderTexture renderTexture;
	Sprite renderSprite;
	

	Text debugText;



	Player* player;
	Enemy* enemy;
	Fighter* fighter;
	Player* Will;
	Player* Alyss;
	Player* Horace;

	PlayerGui* playerGui;
	


	Font font;
	PausedMenu* pauseMenu;
	GameOverState* gameOverState;
	HelpState* helpState;
	TileMap* tileMap;

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
	void initPauseMenuGameOver();
	void initHelpState();

public:
	//konstruktor
	LoadGameState(StateData* stateData);
	//destruktor
	virtual ~LoadGameState();
	int characterAlyss;
	int characterHorace;
	int characterWill;
	bool load;
	//zmienne dotyczace 
	float playerPosition_x;
	float playerPosition_y;
	int playerHp;
	int playerExp;

	float enemyPosition_x;
	float enemyPosition_y;
	int enemyHp;
	int enemyExp;

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
	void updateCombat(Player* player, Enemy* player2, const float& dt);
	void updateDebugText(const float dt);
	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateDistance(Player* player, Enemy* enemy, const float& dt);
	//wszystkie render
	void render(RenderTarget* target = NULL);
	void chooseCharacter();
	//zapisywanie gry
	void saveToFile(string path);
	void loadFromFile(string path);


	//funkcje dostepu
	const bool getKeyTime();


	Texture temp;//pomoc do zaladowania struktury
};
#endif // !LOADGAMESTATE_H
