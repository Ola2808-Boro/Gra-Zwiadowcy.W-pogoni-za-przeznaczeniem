#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "PausedMenu.h"
#include "GameOverState.h"
#include "HelpState.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"
#include "Enemy.h"
#include "EnemyGui.h"

#include "TextTagSystem.h"



class GameStates:public State,public TileMap//dziedzicznie
{
private:
	View view;
	Vector2i viewGridPosition;
	RenderTexture renderTexture;
	Sprite renderSprite;

	
	Text debugText;
	
	vector<Enemy*> activeEnemies;//konstruktor i destruktor

	Player *player;
	Enemy* enemy;
	Player* Will;
	Player* Alyss;
	Player* Horace;
	
	PlayerGui* playerGui;
	EnemyGui* enemyGui;
	



	Font font;
	PausedMenu *pauseMenu;
	GameOverState* gameOverState;
	HelpState* helpState;
	TileMap *tileMap;

	Clock keyTimer;
	float keyTimeMax;

	int characterAlyss;
	int characterHorace;
	int characterWill;

	int enemyType;
	int enemyAmount;
	int enemyCounter;
	Clock enemySpawnTimer;
	Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	Clock despawnTimer;
	Int32 despawnTimerMax;
	bool firstSpawn;


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
	void initEnemyGui();
	void initSystems();
	void initKeyTime();
	void initDebugText();
	void initEnemy();
	void initPauseMenuGameOver();
	void initHelpState();
	void initEnemySystem();

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
	void updateCombat(Player* player, Enemy* enemy, const float& dt);
	void updateDebugText(const float dt);
	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateDistance(Player* player, Enemy* enemy,const float& dt);
	//wszystkie render
	void render(RenderTarget* target = NULL);

	//zapisywanie gry
	void saveToFile(string path);
	void saveToFileEnemyPosition(string path);
	void saveToFileGui(string path);
	//
	void chooseCharacter();
	//funkcje dostepu
	const bool getKeyTime();

	// enemy
	bool controlExp;
	int enemyNumber;
	float position_enemy_x;
	float position_enemy_y;
	

	Texture temp;//pomoc do zaladowania struktury
};
#endif 
