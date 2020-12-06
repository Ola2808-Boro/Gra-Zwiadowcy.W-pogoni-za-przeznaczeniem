#ifndef PAUSED_MENU_H
#define PAUSED_MENU_H

#include "Gui.h"

class Gui;


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
	void update(Vector2i& mousePostWindow);
	void render(RenderTarget &target);
	void addButtons(string key, float x, float y, float width, float height, string text);
	const bool& isButtonPressed(const string key);
};
#endif // !PAUSED_MENU_H

