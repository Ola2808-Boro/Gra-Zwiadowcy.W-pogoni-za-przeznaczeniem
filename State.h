#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings; 
class State;

class StateData
{
public:
	StateData()
	{

	}
	virtual~StateData()
	{

	}
	float gridSize;
	RenderWindow* window;
	map <string, int>* supportedKeys;
	stack <State*>* states;
	GraphicsSettings* graphicsSettings;
};


class State
{
protected:
	StateData* stateData;
	stack <State*>* states;
	RenderWindow* window;
	map <string, int>* supportedKeys;
	map <string, int> keybinds;//przypisywać klawiszom klawiatury i przyciskom myszki określone przez użytkownika skróty 
	bool quit;
	bool paused;//uwzglednie to w gamestate w update
	float keyTime;
	float keyTimeMax;
	float gridSize;
	map<string,Texture*> textures;
	Vector2i mousePostScreen; /*Vector2 to klasa(właściwie to template klasy) 
							  składająca się z dwóch zmiennych.Vector2f i Vector2i
							  to typedefy dla odpowiednio Vector2<float> i Vector2<int>.
							  Tzn.w przypadku tego pierwszego, te dwie zmienne w strukturze są typu float,
							  a w drugim typu int.*/
	Vector2i mousePostWindow;
	Vector2f mousePostView;

	virtual void initKeybinds() = 0;

public:
	State(RenderWindow* window, GraphicsSettings  gfxSettings, map <string, int>* supportedKeys, stack <State*>* states);//creat window 
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeyTime();

	void endState();

	//virtual void endStateUpdate() = 0;//virtual
	virtual void updatePlayerInput(const float& dt) = 0;//virtual
	virtual void render(RenderTarget *target=NULL) = 0;//virtual
	virtual void updateMousePosition();
	virtual void update(const float& dt) = 0;//virtual
	virtual void updateKeyTime(const float& dt);

	//funkcje do pasued
	void pauseState();//kiedy jest pauza
	void unpauseState();//kiedy nie ma pauzy
};

#endif 
