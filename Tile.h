#ifndef TILE_H
#define TILE_H



enum TileTaps//wyliczanie
{
	DEFAULT = 0,
	DAMAGING

};

class Tile
{
private:

protected:
	RectangleShape shape;
	short  type;
	bool collision;

public:
	Tile();
	Tile(int grid_x, int grid_y,float gridSizeF,Texture& texture,const IntRect& texture_rect, bool collision = false, short type = TileTaps::DEFAULT);
	virtual ~Tile();

	const string getAsString()const;
	const FloatRect getGlobalBounds() const;
	const Vector2f& getPosition() const;

	const bool intersects(const FloatRect bounds) const ;
	const bool& getCollision() const;

	//Funkcje
	void update();
	void render(RenderTarget& target);
	

};
#endif // !TILE_H
