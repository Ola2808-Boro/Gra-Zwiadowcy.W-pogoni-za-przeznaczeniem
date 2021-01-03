#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H
//nazwy typow napisow, ktore swoim wygladem beda dostosowane, do teog, co dzieje sie z bohaterem
enum TagTypes
{
	Default_Tag = 0,
	Negative_Tag,
	Positiive_Tag,
	Experience_Tag,
	Envirometal_Tag
};
class TextTagSystem
{
private:
	class TextTag
	{
	private:
		//zmienne
		Text text;
		float dir_x;
		float dir_y;
		float lifetime;
		float speed;
		float acceleration;
		Vector2f velocity;
		int fadeValue;
		bool reverse;
		
	public:
		//2 konstruktory
		TextTag(Font& font, string text, float x_position, float y_position, float direction_x, float direction_y,
			Color color, unsigned characterSize, float lifetime, bool reverse,float speed, float acceleration,int fadeValue)
		{
			this->text.setFont(font);
			this->text.setCharacterSize(characterSize);
			this->text.setPosition(Vector2f(x_position, y_position));
			this->text.setFillColor(color);
			this->dir_x = direction_x;
			this->dir_y = direction_y;
			this->lifetime = lifetime;
			this->speed = speed;
			this->acceleration = acceleration;
			this->fadeValue = fadeValue;
			this->reverse = reverse;
			if (this->reverse)
			{
				this->velocity.x = this->dir_x * this->speed;
				this->velocity.y = this->dir_y * this->speed;
			}
			
		}
		//konstruktor
		TextTag(TextTag* tag, float x_position, float y_position, string _string)
		{
			this->text = tag->text;
			this->text.setPosition(Vector2f(x_position, y_position));
			this->text.setString(_string);
			this->dir_x = tag->dir_x;
			this->dir_y = tag->dir_y;
			this->lifetime = tag->lifetime;
			this->speed = tag->speed;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			this->reverse = tag->reverse;
			this->velocity = tag->velocity;
		}
		//destruktor
		virtual~TextTag()
		{

		}

		//funkcje
		void update(const float& dt)
		{
			if (this->lifetime > 0.f)
			{
				this->lifetime -= 100.f * dt;

				if (this->acceleration > 0.f)
				{
					this->velocity.x -= this->dir_x * this->acceleration * dt;
					this->velocity.y -= this->dir_y * this->acceleration * dt;


					if (abs(this->velocity.x) < 0.f)
					{
						this->velocity.x = 0.f;
					}

					if (abs(this->velocity.y) < 0.f)
					{
						this->velocity.y = 0.f;
					}
					this->text.move(this->velocity * dt);
				}
				else
				{
					this->text.move(this->dir_x * this->speed * dt, this->dir_y * this->speed * dt);
				}
				if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue)
				{
					this->text.setFillColor
					(
						Color(
							this->text.getFillColor().r,
							this->text.getFillColor().g,
							this->text.getFillColor().b,
							this->text.getFillColor().a - this->fadeValue
						)
					);
				}
			}
		}
		void render(RenderTarget& target)
		{
			target.draw(text);
		}

		//funkcje dostepu
		inline const bool isExpired() const
		{
			return this->lifetime <= 0.f;
		}
	};


	Font font;
	vector<TextTag*>textTags;
	map<unsigned, TextTag*> tagTemplates;
	//funckje prywatne
	void initVariables();
	void initTagTemplates();
	void initFont(string font_file);

public:
	//konstruktor
	TextTagSystem(string font_file);
	//destruktor
	virtual~TextTagSystem();

	//fucnkje
	//prefix i profix sluza jako przedroski i przyrostki, np zeby do liczby oznaczjacej exp dopisac slowo exp
	void addTextTag(const unsigned tag_types, const float x_position, const float y_position,const string _string, const string prefix, const string postfix);
	void addTextTag(const unsigned tag_types, const float x_position, const float y_position,const int i, const string prefix, const string postfix);
	void addTextTag(const unsigned tag_types, const float x_position, const float y_position,const float f, const string prefix, const string postfix);
	//funckje glowne
	void update(const float& dt);
	void render(RenderTarget& target);
};

#endif // !TEXTTAGSYSTEM_H