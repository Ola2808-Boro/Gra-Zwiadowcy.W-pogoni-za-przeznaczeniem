#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStates.h"
#include "EditorState.h"
#include "Gui.h"
#include "SettingState.h"

class MainMenuState:public State //dziedzicze po State ma f wirtualne 
{
private:
	RectangleShape background;//tlo
	Font font;
	Texture backgroundtexture;//zeby miec funkcje z tej klasy
	//gui::Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	map <string, gui::Button*> buttons;
	void initKeybinds();
	void InitFonts();
	void initButtom();
	void initBackground();
	void initVariables();

public:
	MainMenuState(StateData* stateData);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updatePlayerInput(const float& dt);
	virtual ~MainMenuState();
	void updateButton();
	void renderButtton(RenderTarget&target);
};

#endif 
