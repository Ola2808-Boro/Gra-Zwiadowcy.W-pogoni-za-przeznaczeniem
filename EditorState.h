#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:	

	   Font font;
	   //Button *gamestate_button;//obiekt klasy zajmujacej sie prostokatem
	   map <string, Button*> buttons;

	   void initKeybinds();
	   void InitFonts();
	   void initButtom();
	   void initBackground();
	   void initVariables();

public:
	EditorState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
	void updateInput(const float& dt);
	virtual ~EditorState();
	void updateButton();
	void renderButtton(RenderTarget&target);

  
};
#endif // !EDITORSTATE_H

