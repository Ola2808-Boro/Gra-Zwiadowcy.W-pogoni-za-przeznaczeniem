#include"stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, Texture& texture, const IntRect& texture_rect,bool collision,short type)
{

	gridSizeF = gridSizeF;
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(Color::Green);
	//->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x)*gridSizeF, (static_cast<float>(grid_y)* gridSizeF));
	this->shape.setTexture(&texture);//sprawdzic
	this->shape.setTextureRect(texture_rect);


	this->collision = collision;
	this->type = type;
	
}

Tile::~Tile()
{
}

const string Tile::getAsString() const
{
	std::stringstream ss;
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << this->collision << " " << this->type << " " << endl;
	return ss.str();
}
const FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}
const bool& Tile::getCollision() const
{
	return this->collision;
}


const Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const short& Tile::getType() const
{
	return this->type;
}

const bool Tile::intersects(const FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target,Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);
		target.draw(this->shape,shader);
	}
	else
	{
		target.draw(this->shape);
	}
}

