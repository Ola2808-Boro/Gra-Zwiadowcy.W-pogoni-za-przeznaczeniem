#ifndef TILE_H
#define TILE_H



enum TileTypes { DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER };//wyliczanie

class Tile
{
private:

protected:
	RectangleShape shape;
	short  type;
	bool collision;

public:
	Tile();
	Tile(int grid_x, int grid_y,float gridSizeF,Texture& texture,const IntRect& texture_rect, const bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const string getAsString()const;
	const FloatRect getGlobalBounds() const;
	const Vector2f& getPosition() const;
	const short& getType()const;

	const bool intersects(const FloatRect bounds) const ;
	const bool& getCollision() const;

	//Funkcje
	virtual void update() = 0;
	virtual void render(RenderTarget& target, Shader* shader = NULL, const Vector2f player_position = Vector2f()) = 0;
	

};
#endif // !TILE_H

