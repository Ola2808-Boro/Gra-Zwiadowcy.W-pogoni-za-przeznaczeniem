#include "State.h"

void State::initKeybinds()
{
}

State::State(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}
//
//void State::endStateUpdate()
//{
//}

void State::updateInput(const float& dt)
{
}

void State::updateMousePosition()
{
	this->mousePostScreen = Mouse::getPosition();
	this->mousePostWindow = Mouse::getPosition(*this->window);
	this->mousePostView=this->window->mapPixelToCoords(Mouse::getPosition(*this->window));


}


