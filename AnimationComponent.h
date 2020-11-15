#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <iostream>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFMl/Network.hpp>
using namespace std;
using namespace sf;
class AnimationComponent
{
private:
	class Animation
	{
	public:
		Sprite& sprite;
		Texture& textureSheet;
		float animationTimer;
		float timer;
		int width,height;
		IntRect startRect;
		IntRect endRect;
		IntRect currentRect;
		Animation(Sprite& sprite,Texture& textureSheet, float animation_timer,int start_frame_x,int start_frame_y,int end_frame_x,int end_frame_y,int width,int height)
			:sprite(sprite),textureSheet(textureSheet), animationTimer(animationTimer),width(width),height(height)
		{
			timer = 0.f;
			this->startRect = IntRect(start_frame_x*width, start_frame_y*width, width, height);
			currentRect = startRect;
			this->endRect = IntRect(end_frame_x * height, end_frame_y*height, width, height);
			this->sprite.setTexture(textureSheet);
			this->sprite.setTextureRect(startRect);// Ustawia rozmiar widocznej czêœci rysowanej tekstury
		}
		~Animation();
		bool play(const float& dt)
		{
			bool done = false;
			//Update timer
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}

			return done;
		}
		bool play(const float& dt,float mod_percent)
		{
			bool done = false;
			if (mod_percent<0.5f)
			{
				mod_percent = 0.5f;//ustam min wartosc
			}
			timer +=mod_percent*dt*100.f ;
			if (timer>=animationTimer)
			{
				timer = 0.f;//resetuje timer
				if (currentRect!=endRect)
				{
					currentRect.left = currentRect.left + width;
				}
				else
				{
					currentRect.left = startRect.left;
					done = true;
				}
				this->sprite.setTextureRect(currentRect);
			}
			return done;
		}
		void reset()
		{
			timer = 0.f;
			currentRect = startRect;
		}
		void pause();

	};
	map <string, Animation*> animation;//spojrz na clase Animation
	Sprite& sprite;
	Texture& textureSheet;
	Animation* lastAnimation;
	Animation* priorityanimation;//pryjotetowa animacja 
public:

	AnimationComponent(Sprite& sprite, Texture &texture_sheet);
	virtual ~AnimationComponent();

	void play(const string key,const float &dt, const bool priority=false);
	void play(const string key,const float &dt,const float &modifier,const float &modifier_max, const bool priority = false);
	void addAnimation(const string key, float animation_timer, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height);

};




#endif // !ANIMATIONCOMPONENT_H


//Klasa Rect
//Klasa narzêdziowa do manipulowania prostok¹tami wyrównanymi w osi 2D.
//
//Prostok¹t jest definiowany przez jego lewy górny róg i jego rozmiar.

// Define a rectangle, located at (0, 0) with a size of 20x5
//sf::IntRect r1(0, 0, 20, 5);
//// Define another rectangle, located at (4, 2) with a size of 18x10
//sf::Vector2i position(4, 2);
//sf::Vector2i size(18, 10);
//sf::IntRect r2(position, size);
//// Test intersections with the point (3, 1)
//bool b1 = r1.contains(3, 1); // true
//bool b2 = r2.contains(3, 1); // false
//// Test the intersection between r1 and r2
//sf::IntRect result;
//bool b3 = r1.intersects(r2, result); // true
//// result == (4, 2, 16, 3)