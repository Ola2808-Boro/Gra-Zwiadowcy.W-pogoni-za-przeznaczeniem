#ifndef TILE_H
#define TILE_H

#include<vector>
#include<stack>
#include<map>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFMl/Network.hpp>
using namespace std;
using namespace sf;

class Tile
{
private:

protected:
	RectangleShape shape;


public:
	Tile();
	Tile(float x, float y,float gridSizeF,Texture& texture,const IntRect& textureRect);
	virtual ~Tile();


	//Funkcje
	void update();
	void render(RenderTarget& target);
	

};
#endif // !TILE_H
