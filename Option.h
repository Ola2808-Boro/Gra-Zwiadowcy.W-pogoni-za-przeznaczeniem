#ifndef OPTION_H
#define OPTION_H

#include "Entity.h"
class Option
{
protected://(zeby Follow moglo odziedziczyc)
	Entity& entity;
	Entity&self;
public:
	//konstruktor
	Option(Entity& self, Entity& entity);
	//destruktor
	virtual~Option();

	//funckje wirtualne
	virtual void update(const float& dt) = 0;

};

#endif // !OPTION_H