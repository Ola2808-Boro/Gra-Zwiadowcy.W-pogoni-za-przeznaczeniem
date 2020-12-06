#include"stdafx.h"
#include "EditorState.h"


void EditorState::initView()
{
	this->view.setSize(Vector2f(static_cast<float>(this->stateData->gfxSettings->resolutions.width), static_cast<float>(this->stateData->gfxSettings->resolutions.height)));
	this->view.setCenter(static_cast<float>(this->stateData->gfxSettings->resolutions.width) / 2.f, static_cast<float>(this->stateData->gfxSettings->resolutions.height) / 2.f);
}

void EditorState::initKeybinds()
{
	//ifstream ifs("Config/editorstate_keybinds.ini");
	//if (ifs.is_open())
	//{
	//	string key = " ";
	//	string key2 = " ";

	//	while (ifs >> key >> key2)//dopoki pobiera te dwie wartosci
	//	{
	//		//this->supportedKeys[key] = this->supportedKeys->at(key2);
	//	}

	//}
	//ifs.clear();
	//ifs.seekg(0);//beginning
	//ifs.close();
	ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void EditorState::initButtom()
{
	//Keyboard::Key;
}

void EditorState::initBackground()
{

}
void EditorState::initVariables()
{
	texture_Rect = IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTaps::DEFAULT;//jest w Tile.h DEFAULT=0
	this->cameraSpeed = 10000.f;//jest w klasie EditorState, bede mnaozyc razy dt
}



EditorState::EditorState(StateData* stateData) :State(stateData)
{
	//10

	this->initVariables();
	this->initView();
	this->InitFonts();
	this->initText();
	this->initKeybinds();
	this->initBackground();
	this->initPauseMenu();
	this->initButtom();
	this->initTileMap();
	this->initGui();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pauseMenu;
	delete this->tileMap;
	delete this->textureSeletor;
}
void EditorState::initPauseMenu()
{
	this->pauseMenu = new PausedMenu(*this->window, this->font);
	this->pauseMenu->addButtons("Quit", 250, 400.f,100.f,50.f, "Quit");
	this->pauseMenu->addButtons("Save", 250.f, 800.f, 100.f, 50.f, "Save");//poprawic
	this->pauseMenu->addButtons("Load", 250.f, 600.f, 100.f, 50.f, "Load");//poprawic
}
void EditorState::initTileMap()
{
	//float gridSize, unsigned width, unsigned height
	this->tileMap = new TileMap(this->stateData->gridSize,100,100,"Resources/Images/tile/1.png");// nie daje jej tego wszytskiego, co StateSetting, MainMenuState itd
}
void EditorState::initGui()
{
	this->sidebar.setSize(Vector2f(80.f,static_cast<float>(this->stateData->gfxSettings->resolutions.height)));
	this->sidebar.setFillColor(Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(Color(200, 200, 200, 100));
	this->sidebar.setOutlineThickness(1.f);


	this->selectorRect.setSize(Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(Color::Red);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(Color::Green);
	this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(texture_Rect);

	this->textureSeletor = new gui::TextureSelector(20.f,20.f,500.f,500.f,this->stateData->gridSize,this->tileMap->getTileTextureSheet(),font,"Cos tam");
}
void EditorState::initText()
{
	cursorText.setFillColor(Color::Red);
	cursorText.setFont(font);
	cursorText.setCharacterSize(12);
	cursorText.setPosition(mousePostView.x, mousePostView.y - 50.f);
}
void EditorState::updateButton()
{

	system("cls");
	cout << this->mousePostView.x << " " << this->mousePostView.y << endl;
	for (auto& it : this->buttons)
	{
		it.second->update(mousePostWindow);
	}
	
}

void EditorState::updateGui(const float &dt)
{
	this->textureSeletor->update(mousePostWindow,dt);
	if (!this->textureSeletor->getActive())
	{
		this->selectorRect.setTextureRect(texture_Rect);
		this->selectorRect.setPosition(mousePosGrid.x * this->stateData->gridSize, mousePosGrid.y * this->stateData->gridSize);
	}
	cursorText.setPosition(mousePostView.x, mousePostView.y - 50.f);
	std::stringstream s;
	s<<this-> mousePostView.x << " " << mousePostView.y <<" "<< texture_Rect.left << " " << texture_Rect.top <<" "<<"Collision"<<" "<<this->collision<<" "<<"Type"<<" "<<this->type<< endl;
	cursorText.setString(s.str());
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
	if (this->pauseMenu->isButtonPressed("Save"))
	{
		this->tileMap->saveToFile("text.txt");
	}
	if (this->pauseMenu->isButtonPressed("Load"))
	{
		this->tileMap->loadFromFile("text.txt");
	}
}

void EditorState::renderButtton(RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(RenderTarget& target)
{
	if (!this->textureSeletor->getActive())
	{
		target.setView(view);
		target.draw(selectorRect);
	}
	target.setView(this->window->getDefaultView());
	this->textureSeletor->render(target);
	target.draw(sidebar);

	target.setView(view);
	target.draw(cursorText);


}


void EditorState::update(const float& dt)
{

	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updatePlayerInput(dt);//to to samo co updateInput, jak masz czas to zmien

	if (!paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateButton();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else
	{

		this->pauseMenu->update(mousePostWindow);//w PausedMenu
		this->updatePauseMenuButtons();

	}
	this->updateButton();

}



void EditorState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->setView(this->view);
	this->tileMap->render(*target);
	target->setView(this->window->getDefaultView());
	this->renderButtton(*target);
	this->renderGui(*target);
	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pauseMenu->render(*target);
	}
	
	target->draw(cursorText);
}

void EditorState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)/*Key(this->keybinds.at("Close")*/ && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//sprawdzanie zdarzen dla kamery

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Camera_Up"))))
	{
		this->view.move(0.f, -this->cameraSpeed*dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Camera_Down"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Camera_Left"))))
	{
		this->view.move(-this->cameraSpeed* dt,0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Camera_Right"))))
	{
		this->view.move(this->cameraSpeed * dt,0.f);
	}

	//Powinno dzialac dla mapy
	if (Mouse::isButtonPressed(Mouse::Left) && this->getKeyTime())//dodam prostokaty
	{
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(mousePostWindow)))
		{
			if (!this->textureSeletor->getActive())//jezeli nie wchodzi na basek z boku
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, texture_Rect,collision,type);
			}
			else
			{
				this->texture_Rect = this->textureSeletor->getTextureRect();
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && this->getKeyTime())//usune prostokaty
		{
			if (!this->textureSeletor->getActive())
			{
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
		//Collision
		if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Collision") && this->getKeyTime())))
		{
			if (collision)
			{
				collision = false;
			}
			else
			{
				collision = true;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Increase_Type") && this->getKeyTime())))
		{
			type++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Decrease_Type") && this->getKeyTime())))
		{
			if (this->type > 0)
			{
				type--;
			}
		}
	}

	
}
