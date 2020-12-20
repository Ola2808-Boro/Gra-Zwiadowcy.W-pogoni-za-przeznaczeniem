#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	if (!this->weapon_texture.loadFromFile("Resources/Images/sprite/sword.png"))//poiwnien zaladowac sie 
	{
		cout << "Blad z za³adowniem tekstury miecza" << endl;
	}
	this->weapon_sprite.setTexture(this->weapon_texture);
	this->weapon_sprite.setOrigin(this->weapon_sprite.getGlobalBounds().width / 2.f, this->weapon_sprite.getGlobalBounds().height);
	

}

Sword::~Sword()
{
}

void Sword::update(const Vector2f& mouse_pos_view,const Vector2f center)
{

	this->weapon_sprite.setPosition(center);

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->weapon_sprite.setRotation(deg + 90.f);
}

void Sword::render(sf::RenderTarget& target, Shader* shader)
{
	if (shader)
	{
		target.draw(this->weapon_sprite, shader);
	}
	else
	{
		target.draw(this->weapon_sprite);
	}
}
