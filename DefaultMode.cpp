#include "stdafx.h"
#include "DefaultMode.h"

DefaultMode::DefaultMode(StateData* state_data, TileMap* tile_Map, EditorStateData* editor_state_data):EditorModes(state_data,tile_Map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

DefaultMode::~DefaultMode()
{
	delete this->textureSelector;
}

void DefaultMode::updateInput(const float& dt)
{
	//Powinno dzialac dla mapy
	if (Mouse::isButtonPressed(Mouse::Left) && this->getKeytime())//dodam prostokaty
	{
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePostWindow)))
		{
			if (!this->textureSelector->getActive())//jezeli nie wchodzi na basek z boku
			{
				this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right) && this->getKeytime())//usune prostokaty
	{
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePostWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0));
					{
						this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
					}
				}
				else
				{
					this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
				}
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//Collision
	if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("Collision") && this->getKeytime())))
	{
		if (this->collision)
		{
			this->collision = false;
		}
		else
		{
			this->collision = true;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("Increase_Type") && this->getKeytime())))
	{
		++this->type;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("Decrease_Type") && this->getKeytime())))
	{
		if (this->type > 0)
		{
			--this->type;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::L))
	{
		if (this->tileAddLock)
		{
			this->tileAddLock = false;
		}
		else
		{
			this->tileAddLock = true;
		}
	}



}

void DefaultMode::updateGui(const float& dt)
{
	this->textureSelector->update(*this->editorStateData->mousePostWindow, dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->editorStateData->mousePostView->x + 100.f, this->editorStateData->mousePostView->y - 50.f);

	std::stringstream ss;
	ss << this->editorStateData->mousePostView->x << " " << this->editorStateData->mousePostView->y <<
		"\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type <<
		"\n" << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) <<
		"\n" << "Tile lock: " << this->tileAddLock;

	this->cursorText.setString(ss.str());
}

void DefaultMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void DefaultMode::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);
}

void DefaultMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}

void DefaultMode::initVariables()
{
	this->textureRect = IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;//jest w Tile.h DEFAULT=0
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultMode::initGui()
{
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->editorStateData->mousePostView->x, this->editorStateData->mousePostView->y);

	//General GUI
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolutions.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 1000.f, 500.f,
		this->stateData->gridSize, this->tileMap->getTileTextureSheet(),
		*this->editorStateData->font, "TS"
	);
}
