#include"stdafx.h"
#include "TileMap.h"

TileMap::TileMap()//wartosci domyslne
{
	this->gridSizeU = static_cast<unsigned>(gridSizeF);//rzutowanie na unsigned
	this->gridSizeF = 50;
	this->maxSize.x = 10;
	this->maxSize.y =10;
	this->layers = 1;
	this->map.resize(maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.resize(maxSize.x);
		this->map.push_back(vector<vector<Tile>>());
		
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(maxSize.y);
			this->map[x].push_back(vector<Tile>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(layers);
				this->map[x][y].push_back(Tile(x * gridSizeF, y * gridSizeF, gridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(RenderTarget& target)
{
	for (auto &x:this->map )
	{
		for (auto &y:x) 
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}
