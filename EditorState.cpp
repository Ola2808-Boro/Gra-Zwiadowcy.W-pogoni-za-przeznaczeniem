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
	this->cameraSpeed = 1000.f;
}



EditorState::EditorState(StateData* stateData) :State(stateData)
{
	//10

	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->InitFonts();
	this->initKeybinds();
	this->initBackground();
	this->initPauseMenu();
	this->initButtom();
	this->initTileMap();
	this->initGui();
	this->initModes();

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
	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}
void EditorState::initPauseMenu()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize
	this->pauseMenu = new PausedMenu(this->stateData->gfxSettings->resolutions, this->font);
	this->pauseMenu->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f,vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");
	this->pauseMenu->addButtons("Save", gui::p2pY(46.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Save");//poprawic
	this->pauseMenu->addButtons("Load", gui::p2pY(37.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Load");//poprawic
}
void EditorState::initTileMap()
{
	//float gridSize, unsigned width, unsigned height
	this->tileMap = new TileMap(this->stateData->gridSize,10,10,"Resources/Images/tile/tilesheet1.png");// nie daje jej tego wszytskiego, co StateSetting, MainMenuState itd
}
void EditorState::initGui()
{
	
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultMode(this->stateData, this->tileMap, &this->editorStateData));
}
void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keyTime;
	this->editorStateData.keytimeMax = &this->keyTimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePostScreen = &this->mousePostScreen;
	this->editorStateData.mousePostView = &this->mousePostView;
	this->editorStateData.mousePostWindow = &this->mousePostWindow;
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
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
	if (this->pauseMenu->isButtonPressed("Save"))
	{
		this->tileMap->saveToFile("text.ini");
	}
	if (this->pauseMenu->isButtonPressed("Load"))
	{
		this->tileMap->loadFromFile("text.ini");
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
	
}

void EditorState::renderModes(RenderTarget& target)
{
	this->modes[EditorMode::DEFAULT_EDITOR_MODE]->render(target);
}


void EditorState::update(const float& dt)
{

	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updatePlayerInput(dt);//to to samo co updateInput, jak masz czas to zmien

	if (!this->paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateButton();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
		
	}
	else
	{

		this->pauseMenu->update(mousePostWindow);//w PausedMenu
		this->updatePauseMenuButtons();

	}
	this->updateButton();

}

void EditorState::updateModes(const float& dt)
{
	this->modes[EditorMode::DEFAULT_EDITOR_MODE]->update(dt);
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, Vector2f(), true);
	this->tileMap->renderDeferred(*target);
	target->setView(this->window->getDefaultView());
	this->renderButtton(*target);
	this->renderGui(*target);
	this->renderModes(*target);
	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pauseMenu->render(*target);
	}
	
	
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
}
