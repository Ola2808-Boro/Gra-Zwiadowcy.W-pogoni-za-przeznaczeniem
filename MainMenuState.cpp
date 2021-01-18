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
	if (!this->font.loadFromFile("Fonts/Langar-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void MainMenuState::initGui()
{

	const VideoMode& vm = this->stateData->gfxSettings->resolutions;

	//Tlo
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	if (!this->backgroundtexture.loadFromFile("Resources/Images/background/zwiadowcy2.jpg"))
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

	 //float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor, Color outlinehoverColor, Color outlineidleColor,
	//Color outlineactiveColor, unsigned character_size, Color text_idle, Color text_hover, Color text_active, short unsigned id
	this->buttons["Game_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(35.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "New Game", this->font, Color(217,146,24,85), Color::Cyan, Color::Yellow, Color(240,101,14,94), Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color(235,44,19,92), Color::White);
	this->buttons["Load_Game"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(45.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Load Game", this->font, Color(217,146,24,85), Color::Cyan, Color::Yellow, Color(240,101,14,94), Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color(235,44,19,92), Color::White);
	this->buttons["Exit_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(55.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Quit", this->font, Color(217, 146, 24, 85), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red, Color(235, 44, 19, 92), Color::White);
	this->buttons["Settings_State"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), "Settings", this->font, Color(217, 146, 24, 85), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Red, Color::Black, gui::calucuateCharacterSize(vm), Color::Red,  Color(235,44,19,92), Color::White);//sprobowac migania z 0
	

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
	
	for (auto &it:this->buttons )
	{
		it.second->update(mousePostWindow);
	}
	if (this->buttons["Game_State"]->isPressed())
	{
		this->states->push(new GameStates(this->stateData));
		this->saveToFileNOT("Config/saveGui.txt");
	}
	if (this->buttons["Settings_State"]->isPressed())
	{
		
			this->saveToFileNOT("Config/will.txt");
		
			this->saveToFileNOT("Config/alyss.txt");
		
			this->saveToFileNOT("Config/horace.txt");

			this->saveToFileNOT("Config/saveGui.txt");
	
		this->states->push(new SettingState(this->stateData));
	}
	if (this->buttons["Exit_State"]->isPressed())
	{

		//this->saveToFileNOT("Config/will.txt");

		//this->saveToFileNOT("Config/alyss.txt");

		//this->saveToFileNOT("Config/horace.txt");

		//this->saveToFileNOT("Config/saveGui.txt");

		this->endState();
	}
	if (this->buttons["Load_Game"]->isPressed())
	{
		this->states->push(new LoadGameState(this->stateData));
		this->saveToFile("Config/saveGui.txt");
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
void MainMenuState::saveToFileNOT(string path)
{
	ofstream ofs(path);
	if (ofs.is_open())
	{
		ofs << 0 << endl;

	}
	ofs.clear();
	ofs.seekp(0);//ustaw na poczatek
	ofs.close();
}
void MainMenuState::saveToFile(string path)
{
	ofstream ofs(path);
	if (ofs.is_open())
	{
		ofs << 1 << endl;

	}
	ofs.clear();
	ofs.seekp(0);//ustaw na poczatek
	ofs.close();
}
