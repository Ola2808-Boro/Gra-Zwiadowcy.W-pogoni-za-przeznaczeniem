#ifndef EDIOTRMODES_H
#define EDITORMODES_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class EditorStateData
{
public:
	EditorStateData()
	{
	};

	
	View* view;
	Font* font;

	float* keytime;
	float* keytimeMax;

	map<string, int>* keybinds;

	Vector2i* mousePostScreen;
	Vector2i* mousePostWindow;
	Vector2f* mousePostView;
	Vector2i* mousePosGrid;
};
class EditorModes
{
private:

protected:
	StateData* stateData;
	EditorStateData* editorStateData;
	TileMap* tileMap;

public:
	EditorModes(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorModes();

	//Functions
	const bool getKeytime();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif //!EDITORMODES_H