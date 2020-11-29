#include"stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF,Texture& texture, const IntRect& textureRect)
{
	x = 10;
	y = 10;
	gridSizeF = gridSizeF;
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(Color::Green);
	//->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(x, y);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(textureRect);
	
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target)
{
	target.draw(shape);
}
