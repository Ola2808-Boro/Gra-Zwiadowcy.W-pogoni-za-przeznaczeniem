#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "PausedMenu.h"
#include "Gui.h"
#include "TileMap.h"
#include "EditorModes.h"
#include "DefaultMode.h"



enum EditorMode { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };

class EditorState :public State
{
private:	

	
	   Font font;
	   View view;
	   float cameraSpeed;
	   //Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	   map <string, gui::Button*> buttons;
	   PausedMenu* pauseMenu;
	   TileMap *tileMap;
	   EditorStateData editorStateData;

	   vector <EditorModes*> modes;//sprawdzic czy usniety w destruktorze 

	 
	   //10 sprawdzic zgodnosc w konstruktorze
	   void initView();
	   void initKeybinds();
	   void InitFonts();
	   void initButtom();
	   void initBackground();
	   void initVariables();
	   void initPauseMenu();
	   void initTileMap();
	   void initGui();
	   void initModes();
	   void initEditorStateData();
public:
	EditorState(StateData* stateData);
	void update(const float& dt);
	void updateModes(const float& dt);
	void render(RenderTarget* target = NULL);
	void updatePlayerInput(const float& dt);
	void updateEditorInput(const float& dt);
	virtual ~EditorState();
	void updateButton();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void renderButtton(RenderTarget& target);
	void renderGui(RenderTarget& target);
	void renderModes(RenderTarget& target);
  
};
#endif // !EDITORSTATE_H

