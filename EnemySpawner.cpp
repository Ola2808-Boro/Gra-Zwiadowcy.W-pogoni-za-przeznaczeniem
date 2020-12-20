#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& texture, const IntRect& texture_rect,
	float grid_size, int enem_type, int enemy_amount, int enemy_time_To_Spawn, float enemy_max_Disatnce):Tile(grid_x,grid_y,gridSizeF,texture,texture_rect,false,TileTypes::ENEMYSPAWNER)
{
	
	this->type = type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_To_Spawn;
	this->enemyMaxDisatnce = enemy_max_Disatnce;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update()
{
}

void EnemySpawner::render(RenderTarget& target, Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
}
