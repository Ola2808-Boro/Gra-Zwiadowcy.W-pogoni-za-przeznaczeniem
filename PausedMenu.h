#ifndef PAUSED_MENU_H
#define PAUSED_MENU_H

#include "Gui.h"
//#include<vector>
//#include<stack>
//#include<map>
//#include<fstream>
//#include<iostream>
//#include<cstdlib>
//#include<ctime>
//#include<SFML/Graphics.hpp>
//#include<SFML/Window.hpp>
//#include<SFML/System.hpp>
//#include<SFML/Audio.hpp>
//#include<SFMl/Network.hpp>
//using namespace std;
//using namespace sf;


class PausedMenu
{
private:
	Font& font;
	Text menuText;
	RectangleShape background;
	RectangleShape container;
	map <string, gui::Button*> buttons;

public:
	PausedMenu(RenderWindow &window,Font &font);
	virtual ~PausedMenu();
	map <string, gui::Button*>&getButtons();
	void update(Vector2f mousePos);
	void render(RenderTarget &target);
	void addButtons(string key, float x, float y, string text);
	const bool& isButtonPressed(const string key);
};
#endif // !PAUSED_MENU_H
