#ifndef ENEMYEDITORMODES_H
#define ENEMYEDITORMODES_H


#include "EditorModes.h"

class EnemyEditorModes :public EditorModes
{
private:
	Text cursorText;
	RectangleShape sidebar;
	RectangleShape selectorRect;
	IntRect textureRect;
	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;

	//prywatne funkcje
	void initGui();
	void initVariables();

public:
	//konstruktor
	EnemyEditorModes(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	//destruktor
	virtual~EnemyEditorModes();

	//funkcje
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};
#endif // !ENEMYEDITORMODES
