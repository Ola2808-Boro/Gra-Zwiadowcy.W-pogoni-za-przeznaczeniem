#ifndef ENTITY_H
#define  ENTITY_H
//poliforfizm, klasa ogolna da postaci 

#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	
	
	Sprite sprite;//obiekt klasy sprite
	//RectangleShape shape;//tworze prostokat
	MovementComponent * movementComponent;
	AnimationComponent* animationcomponent;
	HitboxComponent* hitboxcomponent;
public:
	Entity();
	virtual ~Entity();

	void setTexture(Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, float deceleration);
	void createAnimationComponent(Texture& texture_sheet);
	void createHitboxComponent(Sprite &sprite, float offset_x, float offset_y, float width, float height);

	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(RenderTarget &target);//virtual
	virtual void move(const float x,const float  y, const float&dt);

	

};

#endif 