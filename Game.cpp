#include"stdafx.h"
#include "Game.h"


//---------------------------------------------Konstruktor-------------------------------------------------------//
Game::Game()//od razu 
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}
//---------------------------------------------Destruktor-------------------------------------------------------//
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();//zwraca wartość szczytowego elementu na stosie.
		this->states.pop();//zdjęcie istniejącego elementu ze szczytu stosu;

	}
}
//---------------------------------------------Funkcje-------------------------------------------------------//
void Game::initVariables()//nadaje zmiennym w private wartosci
{
	this->window = NULL;
	this->gridSize = 64.f;
	this->dt = 0.f;
}

void Game::initWindow()//inicjuje okno, pobiera dane z pliku
{
	
	if (this->gfxSettings.fullscreen)
	{
		//cout << "Fullscreen" << endl;
		this->window = new RenderWindow(VideoMode(gfxSettings.resolutions.width, gfxSettings.resolutions.height), gfxSettings.title, Style::Fullscreen, gfxSettings.contextSettings);
	}
	else
	{
		this->window = new RenderWindow(VideoMode(gfxSettings.resolutions.width, gfxSettings.resolutions.height), gfxSettings.title, Style::Titlebar|Style::Close, gfxSettings.contextSettings);
	}
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}
void Game::initKeys()
{
	ifstream ifs("Config/supported_keys.ini");
	if (ifs.is_open())
	{
		string key = "";
		int key_value = 0;

		while (ifs>>key>>key_value)//dopoki pobiera te dwie wartosci
		{
			this->supportedKeys[key] = key_value;
		}

	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();
	
	for (auto i :this->supportedKeys)
	{
		cout << i.first <<" "<< i.second << endl;

	}

}
void Game::initGraphicsSettings()
{
	gfxSettings.loadToFile("Config/graphics.ini");	
}
void Game::initStates()//doda ma poczatek
{
	this->states.push(new MainMenuState(&this->stateData));
	
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::updateSFMLEvent()
{
	while (this->window->pollEvent(sfEvent))
	{
		if (this->sfEvent.type == Event::Closed)
			this->window->close();
		
	}
}

void Game::update()
{
	this->updateSFMLEvent();

	if (!this->states.empty())
	{
		if (window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
			
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	//Application end
	else
	{
		this->endApplication();
		/*cout << "Jestem" << endl;*/
		this->window->close();
	}
}


void Game::run()
{
	
	Music music;


	if (!music.openFromFile("Music/proba1music.wav"));
	{
			cout << "Blad w muzyce" << endl;
	}
	music.setVolume(40);//pamietaj
	music.setLoop(true);
	music.play();
	while (this->window->isOpen())
	{
		
		this->updateDT();
		
		this->update();
		
		this->render();
	}
}

//void Game::saveToFile(string path)
//{
//	ofstream ofs(path);
//	if (ofs.is_open())
//	{
//		ofs << 1;
//
//	}
//	ofs.clear();
//	ofs.seekp(0);//ustaw na poczatek
//	ofs.close();
//}

//void Game::loadFromFile(string path)
//{
//	ifstream ifs(path);
//	if (ifs.is_open())
//	{
//		ifs >> music;
//	}
//	ifs.clear();
//	ifs.seekg(0);//beginning
//	ifs.close();
//}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())//return true if states are empty
	{
		this->states.top()->render(this->window);
	}
	this->window->display();
}

void Game::endApplication()
{
	cout << "ending Aplication" << endl;
}

void Game::updateDT()
{

	this->dt = this->dtClock.restart().asSeconds();
	//system("cls");
	//cout << this->dt << "\n";
}
