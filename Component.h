#ifndef COMPONENT_H
#define COMPONENT_H

#include "Option.h"
#include "Follow.h"
class Component 
{
private:
	Entity& entity;
	Entity& self;

public:
	//konstruktor
	Component(Entity& self, Entity& entity);
	//destruktor
	virtual~Component();

	//funkcja
	void update(const float& dt);
};
#endif // !COMPONENT_H
