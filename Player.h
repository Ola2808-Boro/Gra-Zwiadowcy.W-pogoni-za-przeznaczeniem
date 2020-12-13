#ifndef PLAYER_H
#define  PLAYER_H

#include "Entity.h"//donrze
class Entity;

class Player :
    public Entity
{
private:
    void initVariables();
    void initComponents();
    bool attacking;

   
public:
    Player(float x, float y, Texture& texture_sheet);
    virtual ~Player();

    AttributeComponent* getAttributeComponent();

    void update(const float& dt);
    void render(RenderTarget& target);
    void updateAnimation(const float& dt);
    void updateAttack();
    void loseHp(const int hp);
    void gainHp(const int hp);
    void loseExp(const int exp);
    void gainExp(const int exp);
  
 



};
#endif // !PLAYER_H
