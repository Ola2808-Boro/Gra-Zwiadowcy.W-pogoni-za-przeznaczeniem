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

void MainMenuState::initGui()
{

	const VideoMode& vm = this->stateData->gfxSettings->resolutions;

	//Tlo
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	if (!this->backgroundtexture.loadFromFile("Resources/Images/background/pobrane.jpg"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	background.setTexture(&this->backgroundtexture);

	//tla dla przysikow w menu
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));


	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize

	//(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor);
	this->buttons["Game_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(30.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "New Game", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);
	this->buttons["Exit_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(40.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Quit", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);
	this->buttons["Editor_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(50.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Editor", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);
	this->buttons["Settings_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Settings", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Yellow, Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);//sprobowac migania z 0
}


void MainMenuState::initVariables()
{
}

void MainMenuState::resetGui()
{

	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	this->buttons.clear();
	this->initGui();
}



MainMenuState::MainMenuState(StateData* stateData):State(stateData)
{
	
	this->initVariables();
	this->InitFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();

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
	target->draw(this->btnBackground);
	this->renderButtton(*target);
	
}

void MainMenuState::updatePlayerInput(const float& dt)
{
	
}
