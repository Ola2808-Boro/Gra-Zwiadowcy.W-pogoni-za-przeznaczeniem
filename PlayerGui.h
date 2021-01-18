#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "Enemy.h"
#include "Gui.h"
#include "PlayerGuiTabs.h"
#include "LoadAttributeComponent.h"

class Player;
class Enemy;


class PlayerGui:public LoadAttributeComponent
{
private:

	VideoMode& vm;
	Player* player;
	Font font;

	//Level Element
	string  levelElementString;
	RectangleShape  levelElementBack;
	Text levelElementText;
	Text gameover;
	
	//exp musi byc w destruktorze
	gui::ProgressBar* expBar;

	//hp  musi byc w destruktorze
	gui::ProgressBar* hpBar;
	

	//Player Gui Tabs
	PlayerGuiTabs* playerGuiTabs;

	//5 funkcje
	void initFont();
	void initHPBar();
	void initExpBar();
	void initLevelElement();
	void initPlayerTabs(VideoMode& vm,Font& font,Player& player);
	

public:
	//konstruktor
	PlayerGui(Player* player,VideoMode& vm);
	//destruktor
	virtual~PlayerGui();
	//funkcje
	void update(const float& dt);
	void render(RenderTarget& target);

	////////Hp Bar/////////////////////
	void renderHPBar(RenderTarget& target);
	void updateHPBar();


	////////Exp Bar/////////////////////
	void renderExpBar(RenderTarget& target);
	void updateExpBar();

	////////Level Element/////////////////////
	void renderLevelElement(RenderTarget& target);
	void updateLevelElement();
	
	//PlayerGuiTabs
	void updatePlayerGuiTabs();
	void renderPlayerGuiTabs(RenderTarget& target);

	//funkcje dostepu
	const bool getTabsOpen()const;
	void toggleCharacterTab();


	void loadFromFile(string path);
	void loadFromFileGui(string path);
	//zmienne dotyczace 
	float playerPosition_x;
	float playerPosition_y;
	int playerHp;
	int playerExp;

	float enemyPosition_x;
	float enemyPosition_y;
	int enemyHp;
	int enemyExp;
	int enemyNumberSave;
	int enemyNumber;
	int levelSave;
	bool changeEnemy;
	int prawda_czy_falsz;
	bool first1 = true;
	bool first2 = true;
	bool first3 = true;
};
#endif // !PLAYERGUI_H

//Co powinno byc:
//4 funkcje update
//4 funckje w render
//5 funkcje init
