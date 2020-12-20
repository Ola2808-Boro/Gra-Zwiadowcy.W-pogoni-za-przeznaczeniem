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
	TileMap(const string file_name);
	//Destruktor
	virtual~TileMap();

	const bool tileEmpty(const int x, const int y, const int z) const;
	const Texture* getTileTextureSheet() const ;//const, zeby bylo bezpieczne
	const int getLayerSize(const int x, const int y, const int layer) const;
	const Vector2f& getMaxSizeF() const;

	//Funkcje
	void render(RenderTarget& target, const Vector2i& gridPosition, Shader* shader = NULL, const Vector2f playerPosition = Vector2f(), const bool show_collision=false);
	void renderDeferred(RenderTarget& target,Shader* shader = NULL, const Vector2f playerPosition = Vector2f());
	void addTile(const int x, const int y, const int z, const IntRect& texture_rect,const bool& collision,const short& type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	void update(Entity * entity, const float& dt);
	const bool checkType(const int x, const int y, const int z, const int type) const;


};
#endif // !TILEMAP_H
