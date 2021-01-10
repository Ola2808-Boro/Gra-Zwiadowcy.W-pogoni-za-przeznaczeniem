#ifndef PLAYER2_H
#define  PLAYER2_H


#include "Entity.h"
class Enemy :public Entity
{
   
    private:
        Clock damageTimer;
        Int32 damageTimerMax;

        //4 funckje inicjujace, sprawdz w konstruktorze
        void initVariables();
        void initComponents();
        void initAnimation();// beda znajdowaly sie to funkcje dotyczace ruchu postaci 
      

        bool initAttack;
        bool attacking;

      
protected:
    unsigned gainExp;

    public:
        //konstruktor
        Enemy(float x, float y, Texture& texture_sheet);
        //destruktor
        virtual ~Enemy();

        //funkcje dostepu
        AttributeComponent* getAttributeComponent();
        const bool& getInitAttack()const;
        const bool getDamageTimer();
        const bool isDead() const;
        //funkcje glowne
        void update(const float& dt, Vector2f& mouse_pos_view, const View& view);//wszytskie position sa w statec
        void render(RenderTarget& target, const bool show_hitbox = false);
        void generateAttributes(const unsigned level);

        //funckja animacji
        void updateAnimation(const float& dt);

        //funckje do hp i exp
        void loseHp(const int hp);

        //funkcje modyfikujace
        void setInitAttack(const bool initAttack);

        const unsigned& getGainExp() const;

 };
#endif // !PLAYER2_H



