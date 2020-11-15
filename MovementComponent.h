#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

//dobrze
#include "AnimationComponent.h"

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

enum MovingStates
{
	Idle,Moving, MovingDown, MowingUp, MowingLeft, MovingRight
};
class MovementComponent
{
private:
	Sprite& sprite;

	float maxVelocity;//predkosc
	float acceleration;//przyspieszeni
	float deceleration;//spowolnienie

	Vector2f velocity;//predkosc
public:
	MovementComponent(Sprite& sprite,float maxVelocity,float acceleration,float deceleration);
	virtual ~MovementComponent();
	const Vector2f& getVelocity() const;
	void update(const float& dt);
	void move(const float x, const float y, const float& dt);
	const bool getStates(unsigned state)const;//do tej dalam wszytskie wczesniejsze , rodzielone osobno
	const bool& getMaxVelocity() const;
};

#endif //

