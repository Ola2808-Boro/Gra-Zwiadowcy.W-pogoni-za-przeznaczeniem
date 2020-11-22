#include"stdafx.h"
#include "State.h"

void State::initKeybinds()
{
}

State::State(RenderWindow* window, GraphicsSettings  gfxSettings, map <string, int>* supportedKeys, stack <State*>* states)//konstruktor, nadaje sobie wartosci
{
	this->window = /*stateData.*/window;
	this->supportedKeys =/*stateData.*/supportedKeys;
	this->states = /*stateData.*/states;
	this->quit = false;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = /*stateData.*/gridSize;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (keyTime>=keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

void State::endState()
{
	this->quit = true;
}
//
//void State::endStateUpdate()
//{
//}

void State::updatePlayerInput(const float& dt)
{
}

void State::updateMousePosition()
{
	this->mousePostScreen = Mouse::getPosition();
	this->mousePostWindow = Mouse::getPosition(*this->window);
	this->mousePostView=this->window->mapPixelToCoords(Mouse::getPosition(*this->window));


}

void State::updateKeyTime(const float& dt)
{
	if (keyTime<keyTimeMax)
	{
		keyTime +=dt*100.f ;
	}
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}


