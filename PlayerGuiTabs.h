#ifndef PLAYERGUITABS_H
#define PLAYERGUITABS_H

#include "CharacterTabs.h"
#include "Player.h"
#include "Gui.h"

enum PlayerTabs
{
	Character_Tab = 0,
	Inventory_Tab

};
class PlayerGuiTabs
{
private:
	vector<Tabs*>tabs;

	Clock keyTimer;
	float keyTimeMax;

	VideoMode& vm;
	Font& font;
	Player& player;
public:
	//konstruktor
	PlayerGuiTabs(VideoMode& vm,Font& font,Player& player);
	//destruktor
	virtual~PlayerGuiTabs();

	//funkcje glowne
	void update();
	void render(RenderTarget& target);
	//funkcje inicjujace
	void initTab();//musi byc w konstruktorze
	void initKeyTime();//musi byc w konstruktorze

	void toggleTab(const int tab_index);


	const bool getKeyTime();
	const bool tapsOpen();
};

#endif // !PLAYERGUITABS_H