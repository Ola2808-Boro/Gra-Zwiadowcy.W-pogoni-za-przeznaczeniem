#ifndef WEAPON_H
#define WEAPON_H

#include"Item.h"

class Weapon:public Item
{
protected:
	Sprite weapon_sprite;
	Texture weapon_texture;

	int damageMin;
	int damageMax;
public:
	Weapon();
	virtual ~Weapon();

	virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};
#endif // !WEAPON_H
