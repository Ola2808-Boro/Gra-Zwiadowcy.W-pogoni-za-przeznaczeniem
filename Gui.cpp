#include"stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor, Color outlinehoverColor, Color outlineidleColor,
	Color outlineactiveColor, unsigned character_size, Color text_idle, Color text_hover, Color text_active, short unsigned id)

{
	//Inicjacja obramowan
	this->outlinehoverColor=outlinehoverColor;
	this->outlineidleColor= outlineidleColor;
	this->outlineidleColor= outlineidleColor;

	//Inicjacja przycisku
	this->buttonState = button_idle;
	this->button.setPosition(Vector2f(x, y));
	this->button.setSize(Vector2f(width,height));
	this->button.setOutlineThickness(1.f);
	this->button.setOutlineColor(outlineidleColor);

	//Inicjacja czcionki
	this->font_button = font_button;

	//Inicjacja Textu
	this->text_button.setFont(this->font_button);
	this->text_button.setString(text_button);
	this->text_button.setFillColor(text_idle);
	this->text_button.setCharacterSize(character_size);

	//Inicjacja kolorow tesktu
	this->activeColor = activeColor;
	this->hoverColor = hoverColor;
	this->idleColor = idleColor;

	this->text_idle= text_idle;
	this->text_idle= text_idle;
	this->text_active= text_active;

	//Polozenie tekstu w przycisku
	this->text_button.setPosition(
		(button.getPosition().x + (this->button.getGlobalBounds().width / 2.f))-this->text_button.getGlobalBounds().width/2.f,
		(button.getPosition().y + (this->button.getGlobalBounds().height / 2.f))- this->text_button.getGlobalBounds().height/ 2.f);//da nam napis na samym srodku
	
	
}

gui::Button::~Button()
{
}

const bool gui::Button::isPressed()const
{
	if (this->buttonState == button_pressed)
		return true;

	return false;

	
}

const string gui::Button::getText()const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const//zwracam id 
{
	return this->id;
}

const unsigned short & gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();//wyrzuca blad
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setText(string text)
{
	return this->text.setString(text);
}

void gui::Button::render(RenderTarget &target)
{
	target.draw(button);
	target.draw(text_button);
}

void gui::Button::update(Vector2f mousePos)
{
	this->buttonState = button_idle;

	//sprawdzic czy bedzie wcisniety
	if (this->button.getGlobalBounds().contains(mousePos))//metoda z prostokatem
	{
		this->buttonState = button_hover;//prawdzam czy zostalo najehane myszka na przycisk
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = button_pressed;
		}
	}
	switch (buttonState)//sprawdzam stan tego bool i bede pod niego zmieniac kolory
	{
	case button_idle:
	{
		this->button.setFillColor(idleColor);
		this->text_button.setFillColor(text_idle);
		this->button.setOutlineColor(outlineidleColor);
		break;
	}
	case button_hover:
	{
		this->button.setFillColor(hoverColor);
		this->text_button.setFillColor(text_hover);
		this->button.setOutlineColor(outlinehoverColor);
		break;
	}
	case button_pressed:
	{
		this->button.setFillColor(activeColor);
		this->text_button.setFillColor(text_active);
		this->button.setOutlineColor(outlineactiveColor);
		break;
	}
	default:
		this->button.setFillColor(Color::Red);
		this->text_button.setFillColor(Color::Yellow);
		this->button.setOutlineColor(Color::Green);
		break;
	}
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, string list[], Font& font, unsigned nrOfElements, unsigned default_index ):font(font),showList(showList),keyTimeMax(1.f),keyTime(0.f)//domysle wartosci
{
	this->showList = showList;
	this->activeElement = new gui::Button(x, y, width, height, list[default_index], this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Black, Color::Blue, 12, Color::Red, Color::Yellow, Color::White,0);
	//unsigned nrOfElement = sizeof(list) / sizeof(string);//ile lementow jest w liscie
	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(new gui::Button(x, y+(/*spojrz na gorsze, czemu plus jeden*/(i+1)*height), width, height, list[i], this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Black, Color::Blue, 12, Color::Red, Color::Yellow, Color::White,i));
	}
	
	
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

void gui::DropDownList::render(RenderTarget& target)
{
	this->activeElement->render(target);
	if (showList)//jezeli istnieje
	{
		for (auto& i : this->list)
		{
			i->render(target);

		}
	}
}

void gui::DropDownList::update(Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);
	activeElement->update(mousePos);
	if (this->activeElement->isPressed()&& this->getKeyTime())
	{
		if (showList)
		{
			showList = false;
		}
		else
		{
			showList = true;
		}
		
	}
	if (showList)//jezeli istnieje
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed()&& getKeyTime())
			{
				 this->showList = false;
				 this->activeElement->setText(i->getText());
				 this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::updateKeyTime(const float &dt)
{
	if (keyTime<keyTimeMax)
	{
		keyTime += dt * 10;
	}
}

const bool gui::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}
