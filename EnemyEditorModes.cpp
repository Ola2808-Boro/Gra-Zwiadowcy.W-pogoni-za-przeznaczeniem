#include "stdafx.h"
#include "EnemyEditorModes.h"

//konstruktor,pamieatj o dziedziczeniu
EnemyEditorModes::EnemyEditorModes(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data):EditorModes(state_data, tile_map, editor_state_data)//dziedziczy publicznie
{
	this->initVariables();
	this->initGui();
	
}
//destruktor
EnemyEditorModes::~EnemyEditorModes()
{
}

///////////////////////////////////////////////////funkcje//////////////////////////////////////////////////////////
void EnemyEditorModes::initGui()
{
	//text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->editorStateData->mousePostView->x, this->editorStateData->mousePostView->y);

	// Gui-sidebar
	this->sidebar.setSize(Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolutions.height)));
	this->sidebar.setFillColor(Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	//selector
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}
void EnemyEditorModes::initVariables()//inicjuje zmienne znajdujace sie w private
{
	this->type = 0;
	this-> amount=1;
	this->timeToSpawn = 60;
	this->maxDistance=100.f;

}
void EnemyEditorModes::updateInput(const float& dt)
{

}

void EnemyEditorModes::updateGui(const float& dt)
{
	this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	this->cursorText.setPosition(this->editorStateData->mousePostView->x + 100.f, this->editorStateData->mousePostView->y - 50.f);

	stringstream ss;
	ss <<
		"\n" << "Enemy type: " << this->type <<
		"\n" << "Enemy amount: " << this->amount <<
		"\n" << "Time to spawn: " << this->timeToSpawn <<
		"\n" << "Max distance: " << this->maxDistance;

	this->cursorText.setString(ss.str());
}

void EnemyEditorModes::update(const float& dt)//bede trzymac wszytskie jej odgalezienia
{
	this->updateInput(dt);//dt
	this->updateGui(dt);//dt
}

void EnemyEditorModes::renderGui(sf::RenderTarget& target)//drukuje moje wartosci z private
{
	target.setView(this->stateData->window->getDefaultView());//sprawdzic
	target.draw(this->selectorRect);
	target.draw(this->cursorText);
	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void EnemyEditorModes::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
