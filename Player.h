#ifndef PLAYER_H
#define  PLAYER_H

#include "Entity.h"//donrze
#include "Sword.h"
class Entity;

class Player :public Entity
{
private:
    void initVariables();
    void initComponents();
    void initAnimation();// beda znajdowaly sie to funkcje dotyczace ruchu postaci 
    bool attacking;
    Sword *sword;
  
   
public:
    Player(float x, float y, Texture& texture_sheet);
    virtual ~Player();

    AttributeComponent* getAttributeComponent();

    void update(const float& dt,Vector2f & mouse_pos_view);//wszytskie position sa w statec
    void render(RenderTarget& target, Shader* shader = NULL, const Vector2f light_position = Vector2f(), const bool show_hitbox = false);
 
    void updateAnimation(const float& dt);
    void updateAttack();

    void loseHp(const int hp);
    void gainHp(const int hp);
    void loseExp(const int exp);
    void gainExp(const int exp);
  
 



};
#endif // !PLAYER_H
