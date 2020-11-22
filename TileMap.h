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
	vector< vector<vector<Tile> > >  map;


public:

	//Konstruktor
	TileMap();
	//Destruktor
	virtual~TileMap();


	//Funkcje
	void update();
	void render(RenderTarget& target);
};
#endif // !TILEMAP_H
