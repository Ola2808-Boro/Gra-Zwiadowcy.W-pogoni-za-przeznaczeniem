#ifndef SILLCOMPONENT_H
#define SKILLCOMPONENT_H


enum SKILLS
{
	Health = 0,
	Attack,
	Accuracy,
	Defence,
	Ranged,
	Melee, 
	Woodcutting,
	Mining,
	Hiperattack,
	Endurance,
};
class SkillComponent
{
private:
	
	class Skill
	{
	private:
		int type;
		int level;
		int levelCap;
		int exp;
		int expNext;
	public:
		Skill(int type)
		{
			this->type = type;
			this->level = 1;
			this->exp = 0;
			this->exp = 100;
			this->levelCap = 99;
		}
		~Skill()
		{

		}
		 void gainExp(const int exp)
		{ 
			this->exp += exp;
			this->updateLevel();
		}
		inline void loseExp(const int exp)
		{
			this->exp -= exp;
			
		}

	
		void updateLevel(const bool up=true)
		{
			if (up)
			{
				if (this->level < this->levelCap)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelCap)
						{
							this->level++;
							this->expNext = static_cast<int>(pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
			else
			{
				if (this->level >0)
				{
					while (this->exp<0)
					{
						if (this->level >0)
						{
							this->level--;
							this->expNext = static_cast<int>(pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
		}
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }
		inline const int& getType() const { return this->type; }

		void setLevel(const int level) { this->level=level; }
		void setLevelCap(const int levelCap) {this->levelCap=levelCap ; }
	};
	vector<Skill> skills;


public:
	SkillComponent();
	virtual~SkillComponent();

	const int getSkill(const int skill)const;
	const int gainExp(const int skill, const int exp);
};
#endif // !SILLCOMPONENT_H

