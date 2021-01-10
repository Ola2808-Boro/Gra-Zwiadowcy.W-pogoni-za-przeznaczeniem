#ifndef LOADATTRIBUTECOMPONENT
#define LOADATTRIBUTECOMPONENT


class LoadAttributeComponent
{
public:

	bool load;
	bool loadAttribute;
	//zmienne dotyczace 
	float playerPosition_x;
	float playerPosition_y;
	int playerHp;
	int playerExp;

	float enemyPosition_x;
	float enemyPosition_y;
	int enemyHp;
	int enemyExp;

	//level
	int level;
	int exp;
	int expNext;
	int attributePoints;
	Text gameover;
	Font font;

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
	LoadAttributeComponent(int level);
	//destruktor
	virtual~LoadAttributeComponent();
	//funkcje
	string debugPrint()const;
	const bool isDead()const;
	//funckje update
	void updateStats(const bool reset);
	void updateLevel();
	void update();//glowna

	//funckje Hp
	void loseHp(const int hp);
	void gainHp(const int hp);
	//funckje Exp
	void gainExp(const int exp);
	void loseExp(const int exp);

	void render(RenderTarget& target);

	void loadFromFile(string path);
};
#endif // !LOADATTRIBUTECOMPONENT
