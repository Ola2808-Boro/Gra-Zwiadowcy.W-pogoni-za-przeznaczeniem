#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h" 

class Enemy :public Entity
{
private:
	
	/*EnemySpawner& enemySpawner;*/
public:
	Enemy(/*EnemySpawner& enemy_Spawner,*/float x, float y, Texture& texture_sheet);
	virtual~Enemy();
	void initAnimation();
	void initVariables();
	void update(const float& dt, Vector2f& mouse_pos_view);
	void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox);
	void updateAnimation(const float& dt);
};
#endif // !ENEMY_H
