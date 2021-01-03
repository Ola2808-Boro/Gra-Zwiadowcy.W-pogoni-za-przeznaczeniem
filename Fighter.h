#ifndef FIGHTER_H
#define FIGHTER_H


#include "Entity.h"
#include "Sword.h"
#include "Inventory.h"
class Entity;

class Fighter :public Entity
{
    Clock damageTimer;
    Int32 damageTimerMax;

    //4 funckje inicjujace, sprawdz w konstruktorze
    void initVariables();
    void initComponents();
    void initAnimation();// beda znajdowaly sie to funkcje dotyczace ruchu postaci 
    void initInventory();//do konstruktora

    bool initAttack;
    bool attacking;

    Weapon* weapon;//inicjuje w konstruktorze, usuwam w destruktorze
    Inventory* inventory;


public:
    //konstruktor
    Fighter(float x, float y, Texture& texture_sheet);
    //destruktor
    virtual ~Fighter();

    //funkcje dostepu
    AttributeComponent* getAttributeComponent();
    Weapon* getWeapon()const;
    const string toStringCharacterTab()const;
    const bool& getInitAttack()const;
    const bool getDamageTimer();
    const unsigned getDamage()const;

    //funkcje glowne
    void update(const float& dt, Vector2f& mouse_pos_view, const View& view);//wszytskie position sa w statec
    void render(RenderTarget& target, const bool show_hitbox = false);


    //funckja animacji
    void updateAnimation(const float& dt);

    //funckje do hp i exp
    void loseHp(const int hp);
    void gainHp(const int hp);
    void loseExp(const int exp);
    void gainExp(const int exp);

    //funkcje modyfikujace
    void setInitAttack(const bool initAttack);
};
#endif // !FIGHTER_H
