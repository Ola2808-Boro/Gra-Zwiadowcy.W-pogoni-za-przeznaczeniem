#ifndef ATTRIBUTTECOMPONENT
#define ATTRIBUTTECOMPONENT


class AttributeComponent
{
public:
	//level
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//atrybuty
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//inne
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;
	//konstruktor
	AttributeComponent(int level);
	//destruktor
	virtual~AttributeComponent();
	//funkcje
	string debugPrint()const;
	void updateStats(const bool reset);
	void updateLevel();
	void update();//glowna
	void gainExp(const int exp);
};
#endif // !ATTRIBUTTECOMPONENT
