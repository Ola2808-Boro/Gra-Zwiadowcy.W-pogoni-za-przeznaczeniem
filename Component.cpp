#include "stdafx.h"
#include "Component.h"
//------------------KONSTRUKTOR------------------------------//
Component::Component(Entity& self, Entity& entity):self(self), entity(entity)
{

}
//------------------DESTRUKTOR------------------------------//
Component::~Component()
{
}
//------------------Funkcje------------------------------//
void Component::update(const float& dt)
{
}
