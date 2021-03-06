#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStates.h"
#include "Gui.h"
#include "SettingState.h"
#include "LoadGameState.h"

class MainMenuState:public State //dziedzicze po State ma f wirtualne 
{
private:
	RectangleShape background;//tlo
	RectangleShape btnBackground;//tlo dla przyciskow
	Font font;
	Texture backgroundtexture;//zeby miec funkcje z tej klasy
	//gui::Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	map <string, gui::Button*> buttons;
	void initKeybinds();
	void InitFonts();
	void initGui();
	void initVariables();
	void resetGui();
public:
	MainMenuState(StateData* stateData);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
	void updatePlayerInput(const float& dt);
	virtual ~MainMenuState();
	void updateButton();
	void renderButtton(RenderTarget&target);
	void saveToFileNOT(string path);
	void saveToFile(string path);
};

#endif 

