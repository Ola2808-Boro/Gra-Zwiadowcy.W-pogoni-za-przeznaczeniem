#include"stdafx.h"
#include "EditorState.h"


void EditorState::initKeybinds()
{
	ifstream ifs("Config/editorstate_keybinds.ini");
	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";

		while (ifs >> key >> key2)//dopoki pobiera te dwie wartosci
		{
			//this->supportedKeys[key] = this->supportedKeys->at(key2);
		}

	}
	ifs.clear();
	ifs.seekg(0);//beginning
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
	
}

void EditorState::initBackground()
{

}
void EditorState::initVariables()
{

}



EditorState::EditorState(RenderWindow* window,GraphicsSettings gfxSettings, map <string, int>* supportedKeys, stack <State*>* states) :State(window, gfxSettings,supportedKeys,states)
{
	this->initVariables();
	this->initBackground();
	this->InitFonts();
	this->initKeybinds();
	this->initButtom();
	this->initPauseMenu();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pauseMenu;
}
void EditorState::initPauseMenu()
{
	this->pauseMenu = new PausedMenu(*this->window, this->font);
	this->pauseMenu->addButtons("Quit", 100.f, 100.f, "Quit");
}
void EditorState::updateButton()
{

	system("cls");
	cout << this->mousePostView.x << " " << this->mousePostView.y << endl;
	for (auto& it : this->buttons)
	{
		it.second->update(mousePostView);
	}
	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
}

void EditorState::renderButtton(RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}


void EditorState::update(const float& dt)
{

	this->updatePlayerInput(dt);
	this->updateMousePosition();
	this->updateKeyTime(dt);
	
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updatePlayerInput(dt);//to to samo co updateInput, jak masz czas to zmien

	if (!paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateButton();
	}
	else
	{

		this->pauseMenu->update(this->mousePostView);
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


	this->renderButtton(*target);
	this->maps.render(*target);
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}

}

void EditorState::updatePlayerInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
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
