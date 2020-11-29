#include"stdafx.h"
#include "SettingState.h"

//Konstruktor
SettingState::SettingState(StateData* stateData):State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->InitFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}
//Destruktor
SettingState::~SettingState()//wszystko sobie usuwam
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	

	auto it2 = this->dropDownList.begin();
	for (auto it2 = this->dropDownList.begin(); it2 != dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
}

//Funkcje z MainMenuState
void SettingState::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";

		while (ifs >> key >> key2)//dopoki pobiera te dwie wartosci
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();
}

void SettingState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void SettingState::initGui()//twprze i przycisk i liste
{
	//(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor);
	this->buttons["Back"] = new gui::Button(350, 400, 150, 50, "Back", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Black, Color::Blue, 20, Color::Red, Color::Yellow, Color::White,0);
	this->buttons["Apply"] = new gui::Button(350, 300, 150, 50, "Apply", this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Red, Color::Black, Color::Blue, 20, Color::Red, Color::Yellow, Color::White,0);//sprobowac migania z 0
	
	vector<string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + to_string(i.height));
	}

	//string li[] = { "1920x1080","800x600","640x480"};//nie musze okreslac ilosci
	this->dropDownList["Resolution"] = new gui::DropDownList(350, 200, 200, 50, modes_str.data(), font,modes_str.size());
	/*	float x, float y, float width, float height, string list[], Font& font, unsigned nrOfElements, unsigned default_index = 0*/

}

void SettingState::initBackground()
{
	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	if (!this->backgroundtexture.loadFromFile("Resources/Images/background/pobrane.jpg"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	background.setTexture(&this->backgroundtexture);
}

void SettingState::initVariables()//uzywam tego w liscie
{
	modes = VideoMode::getFullscreenModes();
}
void SettingState::initText()
{
	optionsText.setFont(font);
	optionsText.setCharacterSize(30);
	optionsText.setPosition(Vector2f(100.f, 00.f));
	optionsText.setFillColor(Color::Blue);
	optionsText.setString("Resolution\n Fullscreen \n Vsync \ Antialasing");
}
void SettingState::updateGui(const float& dt)
{

	system("cls");
	cout << this->mousePostView.x << " " << this->mousePostView.y << endl;//wypisuje sobie wspolrzedne,moje pomocnicze
	//wszytsko do button
	for (auto& it : this->buttons)
	{
		it.second->update(mousePostView);
	}
	if (this->buttons["Back"]->isPressed())//wychodze , pomyslec nad tym, bo ma cos do glownego menu, a wyrzucqa z gry
	{
		this->endState();
	}
	if (this->buttons["Apply"]->isPressed())//wychodze 
	{
		this->stateData->gfxSettings->resolutions = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];
		window->create(this->stateData->gfxSettings->resolutions, this->stateData->gfxSettings->title, Style::Default);
	}
	//wszytsko do listy
	for (auto& it : this->dropDownList)
	{
		it.second->update(mousePostView,dt);
	}
	
}

void SettingState::renderGui(RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownList)
	{
		it.second->render(target);
	}
}

void SettingState::update(const float& dt)
{

	this->updatePlayerInput(dt);
	this->updateMousePosition();
	this->updateGui(dt);
	


}



void SettingState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderGui(*target);
	target->draw(optionsText);

}

void SettingState::updatePlayerInput(const float& dt)
{

}

