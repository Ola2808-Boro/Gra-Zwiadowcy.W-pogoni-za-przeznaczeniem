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
		button.getPosition().y);//da nam napis na samym srodku
	
	
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

void gui::Button::update(Vector2i& mousePostWindow)
{
	this->buttonState = button_idle;

	//sprawdzic czy bedzie wcisniety
	if (this->button.getGlobalBounds().contains(static_cast<Vector2f>(mousePostWindow)))//metoda z prostokatem
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
	for (unsigned i = 0; i < nrOfElements; i++)
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

void gui::DropDownList::update(Vector2i& mousePostWindow, const float& dt)
{
	this->updateKeyTime(dt);
	activeElement->update(mousePostWindow);
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
			i->update(mousePostWindow);

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
/////////////////////////////////////////////////////// TextureSelector///////////////////////////////////////

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,float gridSize,const Texture* textureSheet, Font& font, string text)
{
	keyTimeMax = 1.f;
	keyTime = 0.f;
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	float offest = 100.f;
	this->bounds.setPosition(x+offest, y);
	this->bounds.setSize(Vector2f(width, height));
	this->bounds.setFillColor(Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(Color(255, 255, 255, 200));

	this->sheet.setTexture(*textureSheet);
	this->sheet.setPosition(x+offest, y);

	if (this->sheet.getGlobalBounds().width>bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(IntRect(0, 0, static_cast<int>(bounds.getGlobalBounds().width),static_cast<int>( sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(IntRect(0, 0, static_cast<int>(sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(Vector2f(gridSize, gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineColor(Color::Red);

	this->texuretRect.width = static_cast<int>(gridSize);
	this->texuretRect.height = static_cast<int>(gridSize);

	this->hiddenButton =  new gui::Button(x,y, 50, 50, text, font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, 30, Color::Red, Color::Yellow, Color::White,0);
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hiddenButton;
}


void gui::TextureSelector::update(Vector2i& mousePosWindow,const float &dt)
{

	this->hiddenButton->update(mousePosWindow);
	if (this->hiddenButton->isPressed()&& getKeyTime())
	{
		if (hidden)
		{
			hidden = false;
		}
		else
		{
			hidden = true;
		}
	}
	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<Vector2f>(mousePosWindow)))
		{
			this->active = true;
		}
		else
		{
			this->active = false;
		}

		if (this->active)
		{
			this->mousePosGrid.x = ((mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(gridSize));
			this->mousePosGrid.x = ((mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(gridSize));
			this->selector.setPosition(this->bounds.getPosition().x + mousePosGrid.x * this->gridSize, this->bounds.getPosition().y + mousePosGrid.y * this->gridSize);
		}
		this->texuretRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
		this->texuretRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
	}
	else
	{

	}

}


void gui::TextureSelector::render(RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(bounds);
		target.draw(sheet);
		if (this->active)
		{
			target.draw(selector);
		}
	}
	this->hiddenButton->render(target);
}
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->texuretRect;
}
const bool gui::TextureSelector::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

void gui::TextureSelector::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax)
	{
		keyTime += dt * 10;
	}
}



