#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H


#include<iostream>
#include<cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFMl/Network.hpp>
using namespace std;
using namespace sf;
class HitboxComponent
{
private:
	Sprite& sprite;
	RectangleShape hitbox;
	float offset_x; 
	float offset_y;
	
public:
	HitboxComponent(Sprite& sprite, float offset_x, float offset_y,float width,float height);
	virtual ~HitboxComponent();
	void update();
	void render(RenderTarget &target);
	bool checkIntersect(const FloatRect frect);

};

#endif // !HITBOXCOMPONENT_H