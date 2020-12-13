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
	   View view;
	   Text cursorText;
	   //Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	   map <string, gui::Button*> buttons;
	   PausedMenu* pauseMenu;
	   TileMap *tileMap;
	   IntRect texture_Rect;
	   RectangleShape selectorRect;
	   gui::TextureSelector *textureSeletor;

	   RectangleShape sidebar;
	

	   short type;
	   bool collision;
	   float cameraSpeed;
	   float layer;
	   //10
	   void initView();
	   void initKeybinds();
	   void InitFonts();
	   void initButtom();
	   void initBackground();
	   void initVariables();
	   void initPauseMenu();
	   void initTileMap();
	   void initGui();
	   void initText();
public:
	EditorState(StateData* stateData);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updatePlayerInput(const float& dt);
	void updateEditorInput(const float& dt);
	virtual ~EditorState();
	void updateButton();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void renderButtton(RenderTarget& target);
	void renderGui(RenderTarget& target);
  
};
#endif // !EDITORSTATE_H
