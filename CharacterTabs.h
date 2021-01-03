#ifndef CHARACTERTABS_H
#define CHARACTERTABS_H

#include "Tabs.h"

class CharacterTabs:public Tabs
{
private:
	//CharacterTab
	RectangleShape CharacterTabsBackground;
	Text characterTabsInfoText;

public:
	//konstruktor
	CharacterTabs(VideoMode& vm, Font& font, Player& player);
	//destruktor
	virtual~CharacterTabs();

	//funkcje
	void initText();//musi byc w konstruktorze
	//void initCharacterTabs();//dotyczace wroga
	//void initTabMenu();//dotyczace wroga
	void update();
	void render(RenderTarget& target);
};
#endif // !CHARACTER_TABS_H

