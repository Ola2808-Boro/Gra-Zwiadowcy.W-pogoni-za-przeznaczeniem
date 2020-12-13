#ifndef ENTITY_H
#define  ENTITY_H
//poliforfizm, klasa ogolna da postaci 

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;

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
	AttributeComponent* attributeComponent;
public:
	Entity();
	virtual ~Entity();

	void setTexture(Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, float deceleration);
	void createAnimationComponent(Texture& texture_sheet);
	void createHitboxComponent(Sprite &sprite, float offset_x, float offset_y, float width, float height);
	void creatAttributeComponent(const int level);

	virtual const FloatRect getGlobalBounds()const;
	virtual const Vector2f& getPosition()const;
	virtual const Vector2i getGridPosition(const int GridSizeI)const;
	virtual void setPosition(const float x, const float y);
	virtual const FloatRect getNextPositionBounds(const float& dt) const;


	virtual void update(const float& dt)=0;
	virtual void render(RenderTarget &target)=0;//virtual
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual void move(const float x,const float  y, const float&dt);

	

};

#endif 
