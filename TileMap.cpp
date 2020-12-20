#include"stdafx.h"
#include "TileMap.h"

void TileMap::clear()//to samo co w destruktorze, po to, zeby tam usunac i po prostu wywyolac ta funkcje
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}

					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
	this->map.clear();
}
	/*cout << this->map.size() << endl;*/

}

TileMap::TileMap(float gridSize, int width, int height,string texture_file)//wartosci domyslne
{

	this->gridSizeI = static_cast<int>(this->gridSizeF);//rzutowanie na unsigned
	this->gridSizeF = gridSize;
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->toX = 0;
	this->layer=0;

	
	this->map.resize(this->maxSizeWorldGrid.x, vector<vector<vector<Tile*>>>());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		cout << "1" << endl;
		
		
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			cout << "2" << endl;
			this->map[x].resize(maxSizeWorldGrid.y, vector<vector<Tile*>>());
			

			for (int z = 0; z < this->layers; z++)
			{
				cout << "3" << endl;
				this->map[x][y].resize(layers,vector<Tile*>());//pusty 
				/*this->map[x][y].push_back(nullptr);*/
			}
		}
	}
	if(!this->tileTextureSheet.loadFromFile(texture_file));
	{
		cout << "Error w konstruktorze" << endl;
	}
	this->collisonBox.setSize(Vector2f(gridSize, gridSize));
	this->collisonBox.setFillColor(Color(255, 0, 0, 50));
	this->collisonBox.setOutlineColor(Color::Red);
	this->collisonBox.setOutlineThickness(1.f);

}

TileMap::TileMap(const string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);

	this->collisonBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisonBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisonBox.setOutlineColor(sf::Color::Red);
	this->collisonBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}
const bool TileMap::checkType(const int x, const int y, const int z, const int type) const
{
	return this->map[x][y][this->layer].back()->getType() == type;
}
const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}

const Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorldF;
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x>=0 &&  x<this->maxSizeWorldGrid.x && y >= 0 && y < this->maxSizeWorldGrid.y && z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}
	throw("Error w TileEmpty");
}

const Texture* TileMap::getTileTextureSheet() const
{
	return &this->tileTextureSheet;
}


void TileMap::render(RenderTarget& target, const Vector2i& gridPosition, Shader* shader, const Vector2f playerPosition, const bool show_collision)
{

	this->layer = 0;

		this->fromX =gridPosition.x - 5;
		if (this->fromX < 0)
		{
			fromX = 0;
		}
		else if (this->fromX > this->maxSizeWorldGrid.x)
		{
			this->fromX = this->maxSizeWorldGrid.x;
		}



		this->toX = gridPosition.x + 8;
		if (this->toX < 0)
		{
			toX = 0;
		}
		else if (this->toX > this->maxSizeWorldGrid.x)
		{
			this->toX = this->maxSizeWorldGrid.x;
		}



		this->fromY = gridPosition.y - 5;
		if (this->fromY < 0)
		{
			fromY = 0;
		}
		else if (this->fromY > this->maxSizeWorldGrid.y)
		{
			this->fromY = this->maxSizeWorldGrid.y;
		}



		this->toY = gridPosition.y + 8;
		if (this->toY < 0)
		{
			toY = 0;
		}
		else if (this->toY > this->maxSizeWorldGrid.y)
		{
			this->toY = this->maxSizeWorldGrid.y;
		}


		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType()==TileTypes::DOODAD)
					{
						this->deferedrenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						if (shader)
						{
							this->map[x][y][this->layer][k]->render(target,shader,playerPosition);
						}
						else
						{
							this->map[x][y][this->layer][k]->render(target);
						}
					}
					if (show_collision)
					{
						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisonBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(collisonBox);

						}
					}
				}
				
			}

		}
	
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto &z : y)
				{
					for (auto* k : z)
					{
						k->render(target);
						if (k->getCollision())
						{
							this->collisonBox.setPosition(k->getPosition());
							target.draw(this->collisonBox);
						}
						}
				

				}
			}
		}


	

	
}

void TileMap::renderDeferred(RenderTarget& target, Shader* shader, const Vector2f playerPosition)
{
	while (!this->deferedrenderStack.empty())
	{
		
		if (shader)
		{
			deferedrenderStack.top()->render(target, shader, playerPosition);
		}
		else
		{
			deferedrenderStack.top()->render(target);
		}

			deferedrenderStack.pop();
		
	}
}

void TileMap::addTile(const int x, const int y, const int z,const IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		/* OK To add tile. */
		this->map[x][y][z].push_back(new Tile( x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision,type));

		cout << "Dodaje!" << "\n";	
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if ((x < this->maxSizeWorldGrid.x) && (x >= 0 )&& (y < this->maxSizeWorldGrid.y) && (y >= 0 )&& (z < this->layers && z >= 0))//sprawdzi czy spelnia warunki
	{
		if (!this->map[x][y][z].empty())//odwrotnie jak do dodawania
		{

			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
			cout << "Remove file" << endl;
		}
	}
	/*if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{*/
		//	if (!this->map[x][y][z].empty())
		//	{
		//		/* OK To remove tile. */
		//		if (type >= 0)
		//		{
		//			if (this->map[x][y][z].back()->getType() == type)
		//			{
		//				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
		//				this->map[x][y][z].pop_back();
		//				//std::cout << "DEGBUG: REMOVED TILE!" << "\n";
		//			}
		//		}
		//		else
		//		{
		//			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
		//			this->map[x][y][z].pop_back();
		//			//std::cout << "DEGBUG: REMOVED TILE!" << "\n";
		//		}
		//	}
		//}
}


void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text-file.
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texture file
	All tiles:
	type
	gridPos x y layer
	Texture rect x y
	collision
	tile_specific...
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file <<" "<< x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< " ";
						}
					}
				}
				}
			}
		}

	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVESAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const string file_name)
{
	ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())//jezeli istnieje
	{
		Vector2i size;
		int gridSize=0;
		int layers=0;
		string texture_file="";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		this->gridSizeI = gridSize;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->gridSizeI = gridSize;
		this->gridSizeF = static_cast<float>(gridSize);
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;


		this->clear();

		this->map.resize(maxSizeWorldGrid.x, vector<vector<vector<Tile*>>>());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(maxSizeWorldGrid.y, vector<vector<Tile*>>());

				for (int  z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(layers, vector<Tile*>());
				
				}
			}
		}
		if (!this->tileTextureSheet.loadFromFile(texture_file));
		{
			cout << "Error" << endl;
		}
		while (in_file >> x >> y >> z >> trX >> trY >>collision >> type)
		{
			this->map[x][y][z].push_back(new Tile(x,y,this->gridSizeF,this->tileTextureSheet, IntRect(trX,trY,this->gridSizeI,this->gridSizeI),collision,type));
		}
	}
	else
	{
		cout << "Blad z plikiemw TileMap" << endl;
	}
	
	in_file.close();//zamykam sobie
}

void TileMap::update(Entity* entity, const float& dt)
{
	if (entity->getPosition().x<0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x+ entity->getGlobalBounds().width > this->maxSizeWorldGrid.x)
	{
		entity->setPosition(this->maxSizeWorldGrid.x- entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().y,0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldGrid.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldGrid.y- entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;




	this->toX =entity->getGridPosition(gridSizeI).x+3;
	if (this->toX < 0)
	{
		toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x ;
	}



	this->fromY = entity->getGridPosition(gridSizeI).y - 1;
	if (this->fromY < 0)
	{
		fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}



	this->toY = entity->getGridPosition(gridSizeI).y + 3;
	if (this->toY < 0)
	{
		toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	


	for (int x =this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < map[x][y][this->layer].size(); k++)
			{
				this->map[x][y][this->layer][k]->update();
				FloatRect playerBounds = entity->getGlobalBounds();//f sa w Tile
				FloatRect nextPositionsBounds = entity->getNextPositionBounds(dt);//f jest w entity
				FloatRect wallBounds = map[x][y][this->layer][k]->getGlobalBounds();
				if (this->map[x][y][this->layer][k]->getCollision() && this->map[x][y][this->layer][k]->intersects(playerBounds))
				{
					//bottom
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}
					//top
					else if (playerBounds.top > wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + playerBounds.height);
					}
					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
			
			

			
		}
		
	}

}

