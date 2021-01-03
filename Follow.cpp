#include "stdafx.h"
#include "Follow.h"
//------------------KONSTRUKTOR------------------------------//
Follow::Follow(Entity& self, Entity& entity):Option(self, entity)
{
	
}
//------------------DESTRUKTOR------------------------------//
Follow::~Follow()
{
}
//----------------------FUNKCJE-----------------------------------//
void Follow::update(const float& dt)//poruszanie,zeby wrog w miare naturalny sposob poruszal sie bohaterem
{
	Vector2f moveVec;
	moveVec.x = entity.getPosition().x - self.getPosition().x;
	moveVec.y = entity.getPosition().y - self.getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((self.getPosition().x != entity.getPosition().x) && abs(vecLength) < 500.f)//jezeli ich pozycje sa rozne
	{
		if (self.getPosition().x - entity.getPosition().x>40)
		{
			self.move(moveVec.x, moveVec.y, dt);
		}
	
	}
}
