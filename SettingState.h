#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.h"
#include "Gui.h"


class SettingState:public State//klasa bazowa
{
private:
	//Will
	RectangleShape willTreatyShowing;
	Text willShowingText;
	Texture willTreatyShowingTexture;//zeby miec funkcje z tej klasy
	//tlo
	RectangleShape background;//tlo
	Texture backgroundtexture;//zeby miec funkcje z tej klasy
	//Alyss
	RectangleShape alyssShowing;//tlo
	Texture alyssShowingTexture;
	Text alyssShowingText;
	//Horace
	RectangleShape horaceShowing;
	Texture horaceShowingTexture;
	Text horaceShowingText;


	
		
	Font font;
	Text optionsText;
	Text infoText;

	map <string, gui::Button*> buttons;
	vector <VideoMode> modes;


	//5 funkcji
	void initKeybinds();
	void InitFonts();
	void initGui();
	void resetGui();
	void initVariables();
	void loadTextures();

	

public:
	//konstruktor
	SettingState(StateData* stateData);
	//destruktor
	virtual~SettingState();

	//funkcje
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
	void updatePlayerInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(RenderTarget& target);

	void saveToFile(string path);
	
};

#endif // !SETTINGSTATE_H
