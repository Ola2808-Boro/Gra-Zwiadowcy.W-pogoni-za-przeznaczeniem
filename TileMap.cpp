
#include"stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)//wartosci domyslne
{
	this->gridSizeU = static_cast<unsigned>(gridSizeF);//rzutowanie na unsigned
	this->gridSizeF = gridSize;
	this->maxSize.x = height;
	this->maxSize.y =width;
	this->layers = 1;
	this->map.resize(maxSize.x, vector<vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		//this->map.resize(maxSize.x);
		//this->map.push_back(vector<vector<Tile*>>());
		
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(maxSize.y, vector<Tile*>());
			/*this->map[x].push_back(vector<Tile*>());*/

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(layers,NULL);
				/*this->map[x][y].push_back(nullptr);*/
			}
		}
	}
	if(!this->tileTextureSheet.loadFromFile("Resources/Images/tile/ tilesheet1.png"));
	{
		cout << "Error" << endl;
	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
	

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
		

			for (size_t z = 0; z < this->layers; z++)
			{
				
				delete this->map[x][y][z];
			}
		}
	}
}

Texture* TileMap::getTileTextureSheet() 
{
	return &this->tileTextureSheet;
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
			for (auto *z : y)
			{
				if (z!=NULL)
				{
					z->render(target);
				}
				
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z,const IntRect& textureRect)
{
	if ((x<this->maxSize.x) &&( x>=0 )&& (y< maxSize.y )&& (y>=0 )&& (z < layers) && (z>=0))//sprawdzi czy spelnia warunki
	{
		if (map[x][y][z]==NULL)
		{
			this->map[x][y][z] = new Tile(this->gridSizeF*x,  this->gridSizeF*y, this->gridSizeF, this->tileTextureSheet,textureRect);
			
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 && y < maxSize.y && y >= 0 && z < layers && z >= 0)//sprawdzi czy spelnia warunki
	{
		if (map[x][y][z] != NULL)//odwrotnie jak do dodawania
		{
			
			delete this->map[x][y][z];
			this->map[x][y][z]=NULL;

		}
	}
}
