#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

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

		bool done;

		int width,height;

		IntRect startRect;
		IntRect endRect;
		IntRect currentRect;

		//Konstrktor
		Animation(Sprite& sprite,Texture& textureSheet, float animation_timer,int start_frame_x,int start_frame_y,int end_frame_x,int end_frame_y,int width,int height)
			:sprite(sprite),textureSheet(textureSheet),timer(0.f),done(false) ,animationTimer(animationTimer),width(width),height(height)
		{
			timer = 0.f;
			this->startRect = IntRect(start_frame_x*width, start_frame_y*width, width, height);
			currentRect = startRect;
			this->endRect = IntRect(end_frame_x * height, end_frame_y*height, width, height);
			this->sprite.setTexture(textureSheet,true);
			this->sprite.setTextureRect(startRect);// Ustawia rozmiar widocznej części rysowanej tekstury
		}
		//Destruktor
		~Animation();
		//funkcje inline
		const bool& isDone() const 
		{
			return this->done;
		}
		const bool& play(const float& dt)
		{
			//Update timer
			/*this->done = false;*/
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
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}

			return this->done;
		}
		const bool& play(const float& dt,float mod_percent)
		{
			
			if (mod_percent<0.5f)
			{
				mod_percent = 0.5f;//ustam min wartosc
			}
			this->done = false;
			timer +=mod_percent*dt*100.f ;
			if (timer>=animationTimer)
			{
				timer = 0.f;//resetuje timer

				if (currentRect!=endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					currentRect.left = startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(currentRect);
			}
			return this->done;
		}
		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
		/*void pause();*///sprawdzic, ale chyba nie potrzebuje jej

	};



	//Zmienne dla klasy AnimationComponent
	map <string, Animation*> animation;//spojrz na clase Animation
	Sprite& sprite;
	Texture& textureSheet;
	Animation* lastAnimation;
	Animation* priorityanimation;//pryjotetowa animacja 






public:
	//konstruktor
	AnimationComponent(Sprite& sprite, Texture &texture_sheet);
	//destruktor
	virtual ~AnimationComponent();

	//funckje dostepu
	const bool &isDone(string key);
	const bool& play(const string key,const float &dt, const bool priority=false);
	const bool& play(const string key,const float &dt,const float &modifier,const float &modifier_max, const bool priority = false);
	//funckje
	void addAnimation(const string key, float animation_timer, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height);

};




#endif // !ANIMATIONCOMPONENT_H


//Klasa Rect
//Klasa narzędziowa do manipulowania prostokątami wyrównanymi w osi 2D.
//
//Prostokąt jest definiowany przez jego lewy górny róg i jego rozmiar.

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

