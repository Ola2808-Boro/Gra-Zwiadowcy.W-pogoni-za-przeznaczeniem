#ifndef PLAYER_H
#define  PLAYER_H

#include "Entity.h"//donrze

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
    void update(const float& dt);
  
 



};
#endif // !PLAYER_H
