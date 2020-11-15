#ifndef BUTTON_H
#define BUTTON_H
#include "GameStates.h"
//#include<SFML/Graphics.hpp>
//#include<SFML/Window.hpp>
//#include<SFML/System.hpp>
//#include<SFML/Audio.hpp>
//#include<SFMl/Network.hpp>
//#include<fstream>
//#include<iostream>
//#include<cstdlib>
//#include<ctime>

	enum button_states 
	{
		button_idle = 0, button_hover ,button_pressed 

	};//wylicznie

class Button
{
private:
	RectangleShape button;
	bool pressed;//czy wscisnal
	bool hover;//czy najechal
	short unsigned buttonState;
	//idle to co jest normalnie
	//hover to jak najade
	// active to jak nacisne
	Font font_button;
	Text text_button;
	Color hoverColor;
	Color idleColor;
	Color activeColor;
	unsigned character_size;
	Color text_idle; 
	Color text_hover; 
	Color text_active;

public:
	Button(float x, float y,float width, float height,string text_button,Font font_button, Color hoverColor, Color activeColor, Color idleColor, unsigned character_size, Color text_idle, Color text_hover, Color text_active);
	~Button();
	const bool isPressed()const;
	void render(RenderTarget &target);
	void update(Vector2f mousePos);
};

#endif // !BUTTON_H


