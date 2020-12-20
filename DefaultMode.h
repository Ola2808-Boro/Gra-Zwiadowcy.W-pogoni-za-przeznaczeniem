#ifndef DEFAULTMODE_H
#define DEFAULTMODE_H

#include "EditorModes.h"



class DefaultMode :public EditorModes
{
private:
	Text cursorText;
	RectangleShape sidebar;
	RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;
	IntRect textureRect;
	bool collision;
	short type;
	int layer;
	bool tileAddLock;

	void initVariables();
	void initGui();

public:
	DefaultMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultMode();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(RenderTarget& target);
	void render(RenderTarget& target);
};

#endif //!DEFAULTEDITORMODE_H