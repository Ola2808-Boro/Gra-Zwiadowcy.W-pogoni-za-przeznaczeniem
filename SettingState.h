#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H
#include "State.h"
#include "Gui.h"
//zmiany ustawinie
class SettingState:public State//klasa bazowa
{
private:
	RectangleShape background;//tlo
	Font font;
	//GraphicsSettings gfxSettings;
	Texture backgroundtexture;//zeby miec funkcje z tej klasy
	//Button* gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	Text optionsText;

	map <string, gui::Button*> buttons;
	map <string, gui::DropDownList*> dropDownList;
	vector <VideoMode> modes;

	void initKeybinds();
	void InitFonts();
	void initGui();
	void initBackground();
	void initVariables();
	void initText();
	

public:
	SettingState(StateData* stateData);
	virtual~SettingState();

	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updatePlayerInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(RenderTarget& target);
};

#endif // !SETTINGSTATE_H
