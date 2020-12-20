#ifndef ENEMYEDITORMODES_H
#define ENEMYEDITORMODES_H

#include "EnemySpawner.h"
#include "EditorModes.h"
class EnemyEditorModes :public EditorModes
{
private:

public:
	EnemyEditorModes(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data):EditorModes();
	virtual~EnemyEditorModes();


	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};
#endif // !ENEMYEDITORMODES
