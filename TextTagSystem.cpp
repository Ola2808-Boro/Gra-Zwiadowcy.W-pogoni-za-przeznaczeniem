#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::initVariables()
{
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[Default_Tag] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::White, 25, 100.f, true, 200.f, 200.f, 2);
	this->tagTemplates[Negative_Tag] = new TextTag(this->font, "", 100.f, 100.f, 0.f, 1.f, sf::Color::Red, 25, 100.f, true, 200.f, 200.f, 1);
	this->tagTemplates[Experience_Tag] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::Cyan, 30, 200.f, true, 200.f, 200.f, 2);
}

void TextTagSystem::initFont(string font_file)
{
	if (!this->font.loadFromFile(font_file))
	{
		cout << "NIe udalo ie zaladowac czcionki w TextTagSystem" << endl;
	}
}

TextTagSystem::TextTagSystem(string font_file)
{
	this->initVariables();
	this->initTagTemplates();
	this->initFont(font_file);
}

TextTagSystem::~TextTagSystem()
{
	for (auto* tag : this->textTags)
	{
		delete tag;
	}

	//Clean up templates
	for (auto& tag : this->tagTemplates)
	{
		delete tag.second;
	}
}

void TextTagSystem::addTextTag(const unsigned tag_types, const float x_position, const float y_position, const string _string, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss << prefix << " " << _string << " " << postfix;
	this->textTags.push_back(new TextTag(this->tagTemplates[tag_types],x_position,y_position,_string));//dodaje element na koniec
	//TextTag& tag, float x_position, float y_position
}

void TextTagSystem::addTextTag(const unsigned tag_types, const float x_position, const float y_position, const int i, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss<<prefix<<" "<< i<<" "<<postfix;
	this->textTags.push_back(new TextTag(this->tagTemplates[tag_types], x_position, y_position, ss.str()));//dodaje element na koniec
	//TextTag& tag, float x_position, float y_position
}
void TextTagSystem::addTextTag(const unsigned tag_types, const float x_position, const float y_position, const float f, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss << prefix << " " << f << " " << postfix;
	this->textTags.push_back(new TextTag(this->tagTemplates[tag_types], x_position, y_position, ss.str()));//dodaje element na koniec
	//TextTag& tag, float x_position, float y_position
}


void TextTagSystem::update(const float& dt)
{
	for (size_t i = 0; i < textTags.size(); i++)
	{
		this->textTags[i]->update(dt);
		if (this->textTags[i]->isExpired())
		{
			delete this->textTags[i];
			this->textTags.erase(this->textTags.begin() + i);//usuwam te element z vectora
		}
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->textTags)
	{
		tag->render(target);
	}
}