#ifndef STATE_H
#define STATE_H

#include "Entity.h"


class State
{
protected:
	stack <State*>* states;
	RenderWindow* window;
	map <string, int>* supportedKeys;
	map <string, int> keybinds;//przypisywaæ klawiszom klawiatury i przyciskom myszki okreœlone przez u¿ytkownika skróty 
	bool quit;
	map<string,Texture*> textures;
	Vector2i mousePostScreen; /*Vector2 to klasa(w³aœciwie to template klasy) 
							  sk³adaj¹ca siê z dwóch zmiennych.Vector2f i Vector2i
							  to typedefy dla odpowiednio Vector2<float> i Vector2<int>.
							  Tzn.w przypadku tego pierwszego, te dwie zmienne w strukturze s¹ typu float,
							  a w drugim typu int.*/
	Vector2i mousePostWindow;
	Vector2f mousePostView;

	virtual void initKeybinds() = 0;

public:
	State(RenderWindow* window, map <string,int>* supportedKeys, stack <State*>* states);//creat window 
	virtual ~State();
	const bool& getQuit() const;
	virtual void update(const float& dt) = 0;//virtual
	void endState();
	//virtual void endStateUpdate() = 0;//virtual
	virtual void updateInput(const float& dt) = 0;//virtual
	virtual void render(RenderTarget *target=NULL) = 0;//virtual
	virtual void updateMousePosition();
};

#endif 