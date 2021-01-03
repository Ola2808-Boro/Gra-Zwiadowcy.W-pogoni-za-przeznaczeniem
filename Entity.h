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
	//konstruktor
	Entity();
	//destruktor
	virtual ~Entity();

	void setTexture(Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, float deceleration);
	void createAnimationComponent(Texture& texture_sheet);
	void createHitboxComponent(Sprite &sprite, float offset_x, float offset_y, float width, float height);
	void creatAttributeComponent(const int level);
	void creatSkillComponent();
	void createArtificalInteligence();




	virtual MovementComponent* getMovementComponent();
	virtual AnimationComponent* getAnimationComponent();
	virtual AttributeComponent* getAttributeComponent();
	virtual SkillComponent* getSkillComponent();

	virtual const FloatRect getGlobalBounds()const;
	virtual const Vector2f& getPosition()const;
	virtual const Vector2i getGridPosition(const int gridSizeI)const;
	virtual const FloatRect getNextPositionBounds(const float& dt) const;
	virtual const Vector2f getCenter() const;
	virtual const Vector2f getSpriteCenter() const;
	virtual const Vector2f& getSpritePosition() const;


	virtual void setPosition(const float x, const float y);
	//funkcje glowne
	virtual void update(const float& dt, Vector2f& mouse_pos_view,const View& view)=0;
	virtual void render(RenderTarget& target,  const bool show_hitbox) = 0;
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual void move(const float x,const float  y, const float&dt);

	virtual const float getDistance(const Entity& entity) const;
	virtual const float getSpriteDistance(const Entity& entity) const;
	

};

#endif 