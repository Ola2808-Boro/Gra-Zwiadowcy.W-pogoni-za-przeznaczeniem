#ifndef FOLLOW_H
#define FOLLOW_H

#include "Option.h"
class Follow:public Option
{
private:

public:
	//konstruktor
	Follow(Entity& self, Entity& entity);
	//destruktor
	virtual~Follow();

	//funkcje
	void update(const float& dt);
};

#endif // !FOLLOW_H