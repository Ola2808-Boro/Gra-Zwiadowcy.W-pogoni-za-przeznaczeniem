#ifndef  ENEMYSPAWNER_H
#define  ENEMYSPAWNER_H

#include "Enemy.h"
#include "Tile.h"

class EnemySpawner:public Tile
{
private:

	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDisatnce;
	RectangleShape shape;

public:
	//konstruktor
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& texture, const IntRect& texture_rect,
		float grid_size, int enem_type, int enemy_amount, int enemy_time_To_Spawn, float enemy_max_Disatnce);
	//destruktor
	virtual~EnemySpawner();

	//funkcje
	void update();
	void render(RenderTarget& target, Shader* shader=NULL, const sf::Vector2f player_position=Vector2f());

	void spawn();
	void clear();
};
#endif // ! ENEMYSPAWNER_H
