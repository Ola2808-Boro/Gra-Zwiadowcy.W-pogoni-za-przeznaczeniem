#ifndef HELPSTATE_H
#define HELPSTATE_H

#include "Gui.h"
#include "Player.h"

class Gui;
class HelpState
{
private:
	Font& font;
	Text helpText;
	Text helpTextInfo;
	Player* player;

	RectangleShape background;
	RectangleShape container;
	map <string, gui::Button*> buttons;


public:

	//konstruktor
	HelpState(VideoMode& vm, Font& font);
	//destruktor
	virtual ~HelpState();

	map <string, gui::Button*>& getButtons();
	void update(Vector2i& mousePostWindow);
	void render(RenderTarget& target);
	void addButtons(string key, const float y, const float width, const float height, const unsigned char_size, string text);
	const bool& isButtonPressed(const string key);


};
#endif

