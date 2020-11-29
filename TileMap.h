#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	Vector2u maxSize;//unsigned int
	vector< vector<vector<Tile*> > >  map;
	Texture tileTextureSheet;


public:

	//Konstruktor
	TileMap(float gridSize,unsigned width,unsigned height);
	//Destruktor
	virtual~TileMap();

	Texture* getTileTextureSheet() ;//const, zeby bylo bezpieczne

	//Funkcje
	void update();
	void render(RenderTarget& target);
	void addTile(const unsigned x, const unsigned y, const unsigned z, const IntRect& textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
};
#endif // !TILEMAP_H
