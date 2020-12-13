#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	float gridSizeF;
	int gridSizeI;
	int layers;
	Vector2f maxSizeWorldF;//f
	Vector2i maxSizeWorldGrid;// int
	vector< vector<vector <vector<Tile*>> > >  map;
	stack <Tile*> deferedrenderStack;
	Texture tileTextureSheet;
	string textureFile;
	RectangleShape collisonBox;
	void clear();

	int fromX;
	int fromY;
	int toY;
	int toX;
	int layer;
public:

	//Konstruktor
	TileMap(float gridSize, int width,int height, string texture_file);
	//Destruktor
	virtual~TileMap();

	const Texture* getTileTextureSheet() const ;//const, zeby bylo bezpieczne
	const int getLayerSize(const int x, const int y, const int layer) const;

	//Funkcje
	void update();
	void render(RenderTarget& target,const Vector2i& gridPosition);
	void renderDeferred(RenderTarget& target);
	void addTile(const int x, const int y, const int z, const IntRect& texture_rect,const bool& collision,const short& type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	void updateCollision(Entity * entity, const float& dt);

};
#endif // !TILEMAP_H
