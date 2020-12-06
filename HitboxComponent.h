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
	FloatRect nextPosition;
	float offset_x; 
	float offset_y;
	
public:
	HitboxComponent(Sprite& sprite, float offset_x, float offset_y,float width,float height);
	virtual ~HitboxComponent();
	const Vector2f& getPosition() const;
	void update();
	void render(RenderTarget &target);
	void setPosition(const Vector2f position);
	void setPosition(const float x, const float y);
	bool intersect(const FloatRect frect);
	const FloatRect getGlobalBounds() const;
	const FloatRect& getNextPosition(const Vector2f& velocity);

};

#endif // !HITBOXCOMPONENT_H
