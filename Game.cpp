#include "Game.h"


void Game::initVariables()//nadaje zmiennym w private wartosci
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()//inicjuje okno, pobiera dane z pliku
{
	unsigned frame=120;
	bool condition1 = false;
	bool condition2 = true;
	string title="Ola";
	VideoMode window_1=VideoMode::getDesktopMode();
	this->videomodes = VideoMode::getFullscreenModes();
	unsigned antialiasing_level = 0;
	ifstream ifs("Config/window.txt");
	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_1.width >> window_1.height;
		ifs >> fullscreen;
		ifs >> frame;
		ifs >> condition1;
		ifs >> condition2;
		ifs >> antialiasing_level;

	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
	{
		this->window = new RenderWindow(VideoMode(window_1.width, window_1.height), title, Style::Fullscreen, windowSettings);
	}
	else
	{
		this->window = new RenderWindow(VideoMode(window_1.width, window_1.height), title, Style::Titlebar|Style::Close, windowSettings);
	}
	///this->window->setFramerateLimit(frame);
	//this->window->setVerticalSyncEnabled(condtion1);
	this->window->setVerticalSyncEnabled(condition2);
	//this->window = new RenderWindow(VideoMode(800, 600), "title");
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
void Game::initStates()//doda ma poczatek
{
	this->states.push(new MainMenuState(this->window,&this->supportedKeys,&this->states));
	
}



Game::Game()//od razu 
{
	this->initWindow();
	this->initKeys();
	this->initStates();
	
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();//zwraca wartoœæ szczytowego elementu na stosie.
		 this->states.pop();//zdjêcie istniej¹cego elementu ze szczytu stosu;

	}
}

void Game::updateSFMLEvent()
{
	while (this->window->pollEvent(sfEvent))
	{
		if ((sfEvent.type == Event::Closed)||(Keyboard::isKeyPressed(Keyboard::Escape)))
		{
			this->window->close();
		}
		
	}
}

void Game::update()
{
	this->updateSFMLEvent();

	if (!this->states.empty())
	{
	
		
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				cout << "Jestem2" << endl;
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		
	}
	//Application end
	else
	{
		this->endApplication();
		cout << "Jestem" << endl;
		this->window->close();
	}
}


void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
	}
}

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
