#include"stdafx.h"
#include "SettingState.h"

//--------------------------------------------------------Konstruktor------------------------------------------//
SettingState::SettingState(StateData* stateData):State(stateData)
{
	this->initVariables();
	this->InitFonts();
	this->initKeybinds();
	this->initGui();
	this->loadTextures();

}
//---------------------------------------------------------Destruktor-------------------------------------------//
SettingState::~SettingState()//wszystko sobie usuwam
{
	
}

//---------------------------------------------------Funkcje-----------------------------------------------------------------//
void SettingState::initKeybinds()
{
	
}

void SettingState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/Langar-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void SettingState::initGui()//twprze i przycisk i liste
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;

	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	if (!this->backgroundtexture.loadFromFile("Resources/Images/background/tloczarne1.jpg"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	background.setTexture(&this->backgroundtexture);



	this->infoText.setFont(font);
	this->infoText.setFillColor(Color::Red);
	this->infoText.setPosition(gui::p2pX(25.f, vm), gui::p2pY(5.f, vm));
	this->infoText.setString("CHOOSE THE CHARACTER");
	this->infoText.setCharacterSize(100);

	this->horaceShowingText.setFont(font);
	this->horaceShowingText.setFillColor(Color::Red);
	this->horaceShowingText.setPosition(gui::p2pX(72.f, vm), gui::p2pY(20.f, vm));
	this->horaceShowingText.setString("Hard");
	this->horaceShowingText.setCharacterSize(60);

	this->alyssShowingText.setFont(font);
	this->alyssShowingText.setFillColor(Color::Red);
	this->alyssShowingText.setPosition(gui::p2pX(43.f, vm), gui::p2pY(20.f, vm));
	this->alyssShowingText.setString("Medium");
	this->alyssShowingText.setCharacterSize(60);

	this->willShowingText.setFont(font);
	this->willShowingText.setFillColor(Color::Red);
	this->willShowingText.setPosition(gui::p2pX(20.f, vm), gui::p2pY(20.f, vm));
	this->willShowingText.setString("Easy");
	this->willShowingText.setCharacterSize(60);

	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize
	//(float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor);
	this->buttons["Back"] = new gui::Button(gui::p2pX(72.f, vm), gui::p2pY(90.5f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),  "Back", this->font, Color(240, 101, 14, 94), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Black, Color::Blue, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);	
	//Will
	this->buttons["Will"] = new gui::Button(gui::p2pX(15.f, vm), gui::p2pY(75.5f, vm),gui::p2pX(20.f, vm), gui::p2pY(6.f, vm), "Will Treaty", this->font, Color(240, 101, 14, 94), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Black, Color::Blue, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);//sprobowac migania z 0
	//Alyss
	this->buttons["Alyss"] = new gui::Button(gui::p2pX(40.f, vm), gui::p2pY(75.5f, vm),gui::p2pX(23.f, vm), gui::p2pY(6.f, vm), "Alyss Mainwaring", this->font, Color(240, 101, 14, 94), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Black, Color::Blue, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);//sprobowac migania z 0
	//Horace
	this->buttons["Horace"] = new gui::Button(gui::p2pX(65.f, vm), gui::p2pY(75.5f, vm),gui::p2pX(20.f, vm), gui::p2pY(6.f, vm), "Horace Altman", this->font, Color(240, 101, 14, 94), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Black, Color::Blue, gui::calucuateCharacterSize(vm), Color::Red, Color::Yellow, Color::White);//sprobowac migania z 0
	
	

	
}

void SettingState::resetGui()
{
	
}



void SettingState::initVariables()//uzywam tego w liscie
{
	modes = VideoMode::getFullscreenModes();
}



void SettingState::loadTextures()
{
	//Will
	this->willTreatyShowing.setSize(Vector2f(300,500));
	if (!this->willTreatyShowingTexture.loadFromFile("Resources/Images/sprite/will111.png"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	willTreatyShowing.setTexture(&this->willTreatyShowingTexture);
	willTreatyShowing.setPosition(300, 300);
	

	//ALYSS
	this->alyssShowing.setSize(Vector2f(300,500));
	if (!this->alyssShowingTexture.loadFromFile("Resources/Images/sprite/alisse11.png"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	alyssShowing.setTexture(&alyssShowingTexture);
	alyssShowing.setPosition(800, 300);

	//HORACE
	this->horaceShowing.setSize(Vector2f(300, 500));
	if (!this->horaceShowingTexture.loadFromFile("Resources/Images/sprite/horace11.png"))
	{
		cout << "Error, wrong in initBackground()" << endl;//jezeli nie uda sie zaladowowac
	}
	//ustawilam tylko dla backgroundtexture, a teraz dla background
	horaceShowing.setTexture(&horaceShowingTexture);
	horaceShowing.setPosition(1300, 300);
}

void SettingState::updateGui(const float& dt)
{

	for (auto& it : this->buttons)
	{
		it.second->update(mousePostWindow);
	}
	if (this->buttons["Back"]->isPressed())//wychodze , pomyslec nad tym, bo ma cos do glownego menu, a wyrzucqa z gry
	{
		this->endState();
	}

	if (this->buttons["Will"]->isPressed())//wychodze 
	{
		this->saveToFile("Config/will.txt");

	}
	

	if (this->buttons["Alyss"]->isPressed())//wychodze 
	{
		this->saveToFile("Config/alyss.txt");

	}
	

	if (this->buttons["Horace"]->isPressed())//wychodze 
	{
		this->saveToFile("Config/horace.txt");

	}
	
	
	
}

void SettingState::renderGui(RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}


}

void SettingState::saveToFile(string path)
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


void SettingState::update(const float& dt)
{
	this->updateMousePosition();
	this->updatePlayerInput(dt);
	this->updateGui(dt);
	
}

void SettingState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->willTreatyShowing);
	target->draw(this->alyssShowing);
	target->draw(this->horaceShowing);
	target->draw(this->horaceShowingText);
	target->draw(this->alyssShowingText);
	target->draw(this->willShowingText);
	this->renderGui(*target);
	target->draw(optionsText);
	target->draw(infoText);

}

void SettingState::updatePlayerInput(const float& dt)
{
	
}


