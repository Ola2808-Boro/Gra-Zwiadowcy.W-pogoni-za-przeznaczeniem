#ifndef ENTITY_H
#define  ENTITY_H
//poliforfizm, klasa ogolna da postaci 

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

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
	SkillComponent* skillComponent;
public:
	Entity();
	virtual ~Entity();

	void setTexture(Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, float deceleration);
	void createAnimationComponent(Texture& texture_sheet);
	void createHitboxComponent(Sprite &sprite, float offset_x, float offset_y, float width, float height);
	void creatAttributeComponent(const int level);
	void creatSkillComponent();

	virtual const FloatRect getGlobalBounds()const;
	virtual const Vector2f& getPosition()const;
	virtual const Vector2i getGridPosition(const int GridSizeI)const;
	virtual const FloatRect getNextPositionBounds(const float& dt) const;
	virtual const Vector2f getCenter() const;

	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt, Vector2f& mouse_pos_view)=0;
	virtual void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox) = 0;
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual void move(const float x,const float  y, const float&dt);

	

};

#endif 
