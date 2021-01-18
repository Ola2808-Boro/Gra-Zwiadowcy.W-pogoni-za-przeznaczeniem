#include "stdafx.h"
#include "PlayerGui.h"

//-------------------------------------------------Konstruktor----------------------------------------------//
PlayerGui::PlayerGui(Player* player, VideoMode& vm):LoadAttributeComponent(level),vm(vm)
{
	this->player = player;
	this->initFont();
	this->initLevelElement();
	this->initExpBar();
	this->initHPBar();
	this->initPlayerTabs(vm,font,*player);
	this->loadFromFile("Config/saveGame.txt");
	this->loadFromFileGui("Config/saveGui.txt");
}
//-------------------------------------------------Destruktor----------------------------------------------//
PlayerGui::~PlayerGui()
{
	delete this->hpBar;
	delete this->expBar;
	delete this->playerGuiTabs;
}
//-------------------------------------------------Funkcje----------------------------------------------//
void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf");
}

void PlayerGui::initHPBar()
{
	
	this->hpBar = new gui::ProgressBar(1.f, 8.3f, 10.4f, 2.8f, this->player->getAttributeComponent()->hpMax, Color::Red, 180, &this->font, this->vm);

}

void PlayerGui::initExpBar()//bedzie nizej niz hp
{
	
		this->expBar = new gui::ProgressBar(1.f, 5.6f, 10.4f, 1.9f, this->player->getAttributeComponent()->expNext ,Color::Blue, 220, &this->font, this->vm);

}

void PlayerGui::initLevelElement()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelElementBack.setSize(sf::Vector2f(width, height));
	this->levelElementBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelElementBack.setPosition(x, y);

	this->levelElementText.setFont(this->font);
	this->levelElementText.setCharacterSize(gui::calucuateCharacterSize(this->vm, 150));
	this->levelElementText.setPosition(this->levelElementBack.getPosition().x + gui::p2pX(0.53f, this->vm), this->levelElementBack.getPosition().y + gui::p2pY(0.5f, this->vm));
}

void PlayerGui::initPlayerTabs(VideoMode& vm, Font& font, Player& player)
{
	this->playerGuiTabs = new PlayerGuiTabs(vm, font, player);
}

void PlayerGui::update(const float& dt)
{
	//4 funkcje

	this->updateLevelElement();
	this->updateExpBar();
	this->updateHPBar();
	this->updatePlayerGuiTabs();
	
}

void PlayerGui::render(RenderTarget& target)
{
	//4 funkcje
	this->renderLevelElement(target);
	this->renderExpBar(target);
	this->renderHPBar(target);
	this->renderPlayerGuiTabs(target);
	
}

void PlayerGui::renderHPBar(RenderTarget& target)
{
	this->hpBar->renderProgressBar(target);

}

void PlayerGui::renderExpBar(RenderTarget& target)
{
	this->expBar->renderProgressBar(target);
}

void PlayerGui::renderLevelElement(RenderTarget& target)
{
	target.draw(levelElementBack);
	target.draw(levelElementText);
	
}

void PlayerGui::updateHPBar()
{
	
		cout << "Player Gui Hp " <<" "<< this->player->getAttributeComponent()->hp<<endl;
		this->hpBar->updateProgressBar(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);

}


void PlayerGui::updateLevelElement()
{
	cout <<"Leve"<<" "<< this->player->getAttributeComponent()->level << endl;
		this->levelElementString = to_string(this->player->getAttributeComponent()->level);
		this->levelElementText.setString(this->levelElementString);
}

void PlayerGui::updatePlayerGuiTabs()
{
	this->playerGuiTabs->update();
}

void PlayerGui::renderPlayerGuiTabs(RenderTarget& target)
{
	this->playerGuiTabs->render(target);
}

const bool PlayerGui::getTabsOpen() const
{
	return this->playerGuiTabs->tapsOpen();
}

void PlayerGui::toggleCharacterTab() 
{
	this->playerGuiTabs->toggleTab(PlayerTabs::Character_Tab);
}

void PlayerGui::updateExpBar()
{
	
		cout << "Player Gui exp " <<" "<< this->player->getAttributeComponent()->exp<< endl;
		this->expBar->updateProgressBar(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
	
	
}
void PlayerGui::loadFromFile(string path)
{
	load = true;
	ifstream ifs(path);
	if (ifs.is_open())
	{

		ifs >> playerPosition_x;
		ifs >> playerPosition_y;
		ifs >> playerHp;
		ifs >> playerExp;
		ifs >> enemyPosition_x;
		ifs >> enemyPosition_y;
		ifs >> enemyHp;
		ifs >> enemyExp;
		ifs >> saveNumber;
		ifs >> levelSave;
	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();

}

void PlayerGui::loadFromFileGui(string path)
{
	ifstream ifs(path);
	if (ifs.is_open())
	{
		ifs >> prawda_czy_falsz;
	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();

}
