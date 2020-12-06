#ifndef GUI_H
#define GUI_H

//#include "GameStates.h"

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFMl/Network.hpp>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
using namespace sf;

	enum button_states 
	{
		button_idle = 0, button_hover ,button_pressed 

	};//wylicznie
	namespace gui
	{
		class Button
		{
		private:

			RectangleShape shape;
			RectangleShape button;
			Text text;
			Font* font;


			bool pressed;//czy wscisnal
			bool hover;//czy najechal

			short unsigned buttonState;
			short unsigned id;

			//idle to co jest normalnie
			//hover to jak najade
			// active to jak nacisne

			
			//Kolory tla
			Color hoverColor;
			Color idleColor;
			Color activeColor;

			//Kolor obramowania
			Color outlinehoverColor;
			Color outlineidleColor;
			Color outlineactiveColor;

			//Tekst zmiennne
			Text text_button;
			Font font_button;

			//Teks czcinka
			unsigned character_size;

			//Tekst kolor
			Color text_idle;
			Color text_hover;
			Color text_active;

		public:
			Button(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor, Color outlinehoverColor,Color outlineidleColor,
			Color outlineactiveColor, unsigned character_size, Color text_idle, Color text_hover, Color text_active, short unsigned id);
			~Button();
			const bool isPressed()const;
			const string getText()const;
			const short unsigned& getId() const;

			void setId(const short unsigned id);
			void setText(string text);
			void render(RenderTarget& target);
			void update(Vector2i& mousePostWindow);

		};

		class DropDownList
		{
		private:
			Font& font;
			gui::Button* activeElement;
			vector<gui::Button*> list;//* , bo nowe
			bool showList;
			float keyTime;
			float keyTimeMax;
		public:
			DropDownList(float x, float y, float width, float height, string list[],Font& font, unsigned nrOfElements, unsigned default_index = 0);
			~DropDownList();
			void render(RenderTarget& target);
			void update(Vector2i& mousePostWindow, const float& dt);
			const bool getKeyTime();
			void updateKeyTime(const float& dt);
			
			const short unsigned& getActiveElementId() const;
			
		};
		class TextureSelector
		{
		private:
			RectangleShape bounds;
			Sprite sheet;
			RectangleShape selector;
			IntRect texuretRect;
			Vector2u mousePosGrid;
			float gridSize;
			bool active;
			bool hidden;
			gui::Button* hiddenButton;
			float keyTime;
			float keyTimeMax;

		public:
			//Konstruktor
			TextureSelector(float x, float  y,float width,float height, float gridSize, const Texture* textureSheet,Font& font,string text);
			//Destruktor
			~TextureSelector();
			//Potrzebne do dostepu
			const bool& getActive() const;
			const IntRect& getTextureRect() const;
			const bool getKeyTime();
			
			//Funkcje
			void update(Vector2i& mousePosWindow, const float& dt);
			void render(RenderTarget& target);
			void updateKeyTime(const float& dt);
		};
	}
#endif // !BUTTON_H
