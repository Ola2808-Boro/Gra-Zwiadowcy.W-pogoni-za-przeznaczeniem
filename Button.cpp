#include "Button.h"

Button::Button(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor,unsigned character_size, Color text_idle,Color text_hover,Color text_active)
{
	this->buttonState = button_idle;

	this->button.setPosition(Vector2f(x, y));
	this->button.setSize(Vector2f(width,height));

	this->font_button = font_button;

	this->text_button.setFont(this->font_button);
	this->text_button.setString(text_button);
	this->text_button.setFillColor(text_idle);
	this->text_button.setCharacterSize(character_size);

	this->activeColor = activeColor;
	this->hoverColor = hoverColor;
	this->idleColor = idleColor;

	this->text_idle= text_idle;
	this->text_idle= text_idle;
	this->text_active= text_active;

	this->text_button.setPosition(
		(button.getPosition().x + (this->button.getGlobalBounds().width / 2.f))-this->text_button.getGlobalBounds().width/2.f,
		(button.getPosition().y + (this->button.getGlobalBounds().height / 2.f))- this->text_button.getGlobalBounds().height/ 2.f);//da nam napis na samym srodku
	
	
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState==button_pressed)//jezeli nacisnety to prawda, realizuje zmiane stanow f update
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Button::render(RenderTarget &target)
{
	target.draw(button);
	target.draw(text_button);
}

void Button::update(Vector2f mousePos)
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
		break;
	}
	case button_hover:
	{
		this->button.setFillColor(hoverColor);
		this->text_button.setFillColor(text_hover);
		break;
	}
	case button_pressed:
	{
		this->button.setFillColor(activeColor);
		this->text_button.setFillColor(text_active);
		break;
	}
	default:
		this->button.setFillColor(Color::Red);
		this->text_button.setFillColor(Color::Yellow);
		break;
	}
}
