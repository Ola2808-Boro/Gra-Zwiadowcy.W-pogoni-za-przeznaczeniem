#include"stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");
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

void MainMenuState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void MainMenuState::initButtom()
{
	//(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor);
	this->buttons["Game_State"] = new gui::Button(this->p2pX(15.6f), this->p2pY(44.4f), this->p2pX(13.f), this->p2pY(6.f), "New Game", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, 35, Color::Red, Color::Yellow, Color::White,0);
	this->buttons["Exit_State"] = new gui::Button(this->p2pX(15.6f), this->p2pY(53.7f), this->p2pX(13.f), this->p2pY(6.f), "Quit", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, 35, Color::Red, Color::Yellow, Color::White,0);
	this->buttons["Editor_State"] = new gui::Button(this->p2pX(15.6f), this->p2pY(63.f), this->p2pX(13.f), this->p2pY(6.f), "Editor", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, 35, Color::Red, Color::Yellow, Color::White,0);
	this->buttons["Settings_State"] = new gui::Button(this->p2pX(15.6f), this->p2pY(81.5f), this->p2pX(13.f), this->p2pY(6.f), "Settings", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, 35, Color::Red, Color::Yellow, Color::White,0);//sprobowac migania z 0
}

void MainMenuState::initBackground()
{
	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	if (!this->backgroundtexture.loadFromFile("Resources/Images/background/pobrane.jpg"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	background.setTexture(&this->backgroundtexture);
}

void MainMenuState::initVariables()
{
}



MainMenuState::MainMenuState(StateData* stateData):State(stateData)
{
	
	this->initVariables();
	this->initBackground();
	this->InitFonts();
	this->initKeybinds();
	this->initButtom();

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it!=buttons.end();++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateButton()
{
	
	system("cls");
	cout << this->mousePostView.x << " " << this->mousePostView.y << endl;
	for (auto &it:this->buttons )
	{
		it.second->update(mousePostWindow);
	}
	if (this->buttons["Game_State"]->isPressed())
	{
		
		this->states->push(new GameStates(this->stateData));
	}
	if (this->buttons["Settings_State"]->isPressed())
	{

		this->states->push(new SettingState(this->stateData));
	}
	if (this->buttons["Editor_State"]->isPressed())
	{

		this->states->push(new EditorState(this->stateData));
	}
	if (this->buttons["Exit_State"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::renderButtton(RenderTarget& target)
{
	
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::update(const float& dt)
{

	this->updatePlayerInput(dt);
	this->updateMousePosition();
	this->updateButton();



}



void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	
	target->draw(this->background);
	this->renderButtton(*target);
	
}

void MainMenuState::updatePlayerInput(const float& dt)
{
	
}
