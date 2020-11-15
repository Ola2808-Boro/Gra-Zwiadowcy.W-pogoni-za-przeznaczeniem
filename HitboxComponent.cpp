#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height) :sprite(sprite),offset_x(offset_x), offset_y(offset_y)
{
	this->hitbox.setPosition(sprite.getPosition().x+offset_x, sprite.getPosition().y+offset_y);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(Color::Green);

}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
}

void HitboxComponent::render(RenderTarget& target)
{
	target.draw(this->hitbox);
}

bool HitboxComponent::checkIntersect(const FloatRect frect)//kolizje
{
	return this->hitbox.getGlobalBounds().intersects(frect);//metoda prostokatow
}
