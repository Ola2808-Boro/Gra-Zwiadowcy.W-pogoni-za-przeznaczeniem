#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "PausedMenu.h"
#include "Gui.h"
#include "TileMap.h"

class State;
class Gui;
class PausedMenu;
class TileMap;


class EditorState :
    public State
{
private:	

	   Font font;
	   //Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	   map <string, gui::Button*> buttons;
	   PausedMenu* pauseMenu;
	   TileMap maps;

	   void initKeybinds();
	   void InitFonts();
	   void initButtom();
	   void initBackground();
	   void initVariables();
	   void initPauseMenu();
public:
	EditorState(RenderWindow* window,GraphicsSettings  gfxSettings, map <string, int>* supportedKeys, stack <State*>* states);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updatePlayerInput(const float& dt);
	virtual ~EditorState();
	void updateButton();
	void updatePauseMenuButtons();
	void renderButtton(RenderTarget&target);

  
};
#endif // !EDITORSTATE_H

