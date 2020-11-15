#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStates.h"
#include "Button.h"
#include "EditorState.h"

class MainMenuState:public State //dziedzicze po State ma f wirtualne 
{
private:
	RectangleShape background;//tlo
	Font font;
	Texture backgroundtexture;//zeby miec funkcje z tej klasy
	//Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	map <string, Button*> buttons;
	void initKeybinds();
	void InitFonts();
	void initButtom();
	void initBackground();
	void initVariables();

public:
	MainMenuState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updateInput(const float& dt);
	virtual ~MainMenuState();
	void updateButton();
	void renderButtton(RenderTarget&target);
};

#endif 
