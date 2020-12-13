#include"stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height) :sprite(sprite),offset_x(offset_x), offset_y(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
	this->hitbox.setPosition(sprite.getPosition().x+offset_x, sprite.getPosition().y+offset_y);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(Color::Green);

}

HitboxComponent::~HitboxComponent()
{
}

const Vector2f& HitboxComponent::getPosition() const//uzyje tej funkcji do ustawienia pozycji
{
	return this->hitbox.getPosition();
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
}

void HitboxComponent::render(RenderTarget& target)
{
	target.draw(this->hitbox);
}

void HitboxComponent::setPosition(const Vector2f position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - offset_x, position.y - offset_y);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x,y);
	this->sprite.setPosition(x - offset_x, y - offset_y);
}

bool HitboxComponent::intersect(const FloatRect frect)//kolizje
{
	return this->hitbox.getGlobalBounds().intersects(frect);//metoda prostokatow
}

const FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const FloatRect& HitboxComponent::getNextPosition(const Vector2f& velocity) 
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;
	return this->nextPosition;
}

