#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H


#include "Gui.h"

class Gui;

class GameOverState
{
	Font& font;
	Text gameOverText;

	RectangleShape background;
	RectangleShape container;
	map <string, gui::Button*> buttons;


public:

	//konstruktor
	GameOverState(VideoMode& vm, Font& font);
	//destruktor
	virtual ~GameOverState();

	map <string, gui::Button*>& getButtons();
	void update(Vector2i& mousePostWindow);
	void render(RenderTarget& target);
	void addButtons(string key, const float y, const float width, const float height, const unsigned char_size, string text);
	const bool& isButtonPressed(const string key);
};
#endif // !GAMEOVERSTATE_H
