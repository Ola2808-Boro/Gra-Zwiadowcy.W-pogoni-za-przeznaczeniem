#include "stdafx.h"
#include "LoadGameState.h"


//----------------------------------------------Konstruktor-------------------------------------------------//
LoadGameState::LoadGameState(StateData* stateData) :State(stateData)
{
	//11 funkcji
	this->iniDefferedRender();
	this->initView();
	this->initKeybinds();
	this->InitFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPauseMenuGameOver();
	this->initHelpState();
	this->initKeyTime();
	this->initDebugText();
	this->loadFromFile("Config/saveGame.txt");
	this->initPlayers();
	this->initEnemy();
	this->initPlayerGui();
	this->initEnemyGui();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();
	




}
//--------------------------------------------------------Destruktor-----------------------------------------------//
LoadGameState::~LoadGameState()
{
	delete this->pauseMenu;
	delete this->gameOverState;
	delete this->helpState;
	delete this->player;
	delete this->enemy;
	delete this->playerGui;
	delete this->enemyGui;
	delete this->tileMap;
	delete this->tts;
	
}

//----------------------------------------------Funkcje---------------------------------/
void LoadGameState::iniDefferedRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0, this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height));
}

void LoadGameState::initView()
{

	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolutions.width / 2),
			static_cast<float>(this->stateData->gfxSettings->resolutions.height / 2)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolutions.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolutions.height) / 2.f
		)
	);
}

void LoadGameState::initKeybinds()
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

void LoadGameState::initTextures()
{

	
	if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Images/sprite/enemy.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
	if (!this->textures["WILL_SHEET"].loadFromFile("Resources/Images/sprite/will.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ALYSS_SHEET"].loadFromFile("Resources/Images/sprite/alyss.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["HORACE_SHEET"].loadFromFile("Resources/Images/sprite/horace.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY1_SHEET"].loadFromFile("Resources/Images/sprite/enemy1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY2_SHEET"].loadFromFile("Resources/Images/sprite/enemy2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY3_SHEET"].loadFromFile("Resources/Images/sprite/enemy3.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY4_SHEET"].loadFromFile("Resources/Images/sprite/enemy4.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY5_SHEET"].loadFromFile("Resources/Images/sprite/enemy5.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY6_SHEET"].loadFromFile("Resources/Images/sprite/enemy6.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["ENEMY7_SHEET"].loadFromFile("Resources/Images/sprite/enemy7.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
}
void LoadGameState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/Langar-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void LoadGameState::initPauseMenu()//tyczy sie new game
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize
	this->pauseMenu = new PausedMenu(this->stateData->gfxSettings->resolutions, this->font);
	this->pauseMenu->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");
	this->pauseMenu->addButtons("Save", gui::p2pY(60.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Save");
	/*this->pauseMenu->addButtons("Save", 250.f, 800.f,100.f,50.f, "Save");*/
}

void LoadGameState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,"Resources/Images/tile/tilesheet1.png" );//sprawdzic, czy ze zmiana dziala bylo 10 10
	//this->tileMap=new TileMap("text.txt");// zmienic nazwe funkcji na loadFromFile
}

void LoadGameState::initPlayerGui()
{
	/*Player* player, VideoMode& vm*/
	this->playerGui = new PlayerGui(this->player, this->stateData->gfxSettings->resolutions);//sprawdzic czy jest w konstruktorze i destruktorze
}

void LoadGameState::initEnemyGui()
{
	this->enemyGui = new EnemyGui(this->enemy, this->stateData->gfxSettings->resolutions);//sprawdzic czy jest w konstruktorze i destruktorze
}

void LoadGameState::initEnemySystem()
{

	
}

void LoadGameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/FjallaOne-Regular.ttf");
}

void LoadGameState::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void LoadGameState::initDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}

void LoadGameState::initEnemy()
{
	
	if (changeEnemy)
	{
		cout << "JESTEM w CHANGE ENEMY" << endl;
		changeEnemy = false;
		switch (enemyNumberSave)
		{
		case 1:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				break;
			}
		case 2:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY1_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY1_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;

				break;
			}


		case 3:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY2_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY2_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = this->enemyHp;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
		case 4:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY3_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY3_SHEET"]);//WROG

				break;
			}
		case 5:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY4_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY4_SHEET"]);//WROG

				break;
			}
		case 6:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY5_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY5_SHEET"]);//WROG

				break;
			}

		case 7:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY6_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY6_SHEET"]);//WROG

				break;
			}
		case 8:
			if (this->player->getPosition().x != enemyPosition_x && this->player->getPosition().y != enemyPosition_y)
			{
				this->enemy = new Enemy(enemyPosition_x, enemyPosition_y, this->textures["ENEMY76_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(enemyPosition_x + 400.f, enemyPosition_y + 400.f, this->textures["ENEMY7_SHEET"]);//WROG

				break;
			}

		default:
			break;
		}
	}
	else
	{
		cout << "JESTEM w Rand ENEMY" << endl;
		srand(time(NULL));
		enemyNumber = rand() % 3 + 1;
		position_enemy_x = rand() % 1500 + 300;
		position_enemy_y = rand() % 700 + 300;
		cout << "Numer wroga" << " " << enemyNumber << endl;
		switch (enemyNumber)
		{
		case 1:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				break;
			}
		case 2:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY1_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY1_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;

				break;
			}


		case 3:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY2_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY2_SHEET"]);//WROG
				this->enemy->getAttributeComponent()->hp = 6;
				cout << "Hp wroga" << " " << this->enemy->getAttributeComponent()->hp << endl;
				cout << "Pozycja wroga" << " " << enemy->getPosition().x << " " << enemy->getPosition().y << endl;
				break;
			}
		case 4:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY3_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY3_SHEET"]);//WROG

				break;
			}
		case 5:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY4_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY4_SHEET"]);//WROG

				break;
			}
		case 6:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY5_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY5_SHEET"]);//WROG

				break;
			}

		case 7:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY6_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY6_SHEET"]);//WROG

				break;
			}

		case 8:
			if (this->player->getPosition().x != position_enemy_x && this->player->getPosition().y != position_enemy_y)
			{
				this->enemy = new Enemy(position_enemy_x, position_enemy_y, this->textures["ENEMY7_SHEET"]);//WROG

				break;
			}
			else
			{
				this->enemy = new Enemy(position_enemy_x + 400.f, position_enemy_y + 400.f, this->textures["ENEMY7_SHEET"]);//WROG

				break;
			}

		default:
			break;
		}

	}


	

}

void LoadGameState::initPauseMenuGameOver()
{

	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	this->gameOverState = new GameOverState(this->stateData->gfxSettings->resolutions, this->font);
	this->gameOverState->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");

}

void LoadGameState::initHelpState()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	this->helpState = new HelpState(this->stateData->gfxSettings->resolutions, this->font);
	this->helpState->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");
}


void LoadGameState::initPlayers()
{
	

	this->chooseCharacter();


	if (characterWill == 1)
	{

		this->player = new Player(playerPosition_x, playerPosition_y, this->textures["WILL_SHEET"]);
		

	}

	if (characterAlyss == 1)
	{

		this->player = new Player(playerPosition_x, playerPosition_y, this->textures["ALYSS_SHEET"]);
		
	}

	if (characterHorace == 1)
	{
		this->player = new Player(playerPosition_x, playerPosition_y, this->textures["HORACE_SHEET"]);
		
	}


}

void LoadGameState::updateView(const float& dt)
{
	this->view.setSize(Vector2f(static_cast<float>(stateData->gfxSettings->resolutions.width), static_cast<float>(stateData->gfxSettings->resolutions.height)));
	this->view.setCenter(
		floor(this->player->getPosition().x + (static_cast<float>(this->mousePostWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolutions.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->mousePostWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolutions.height / 2)) / 10.f)
	);

	this->mousePosGrid.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->mousePosGrid.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void LoadGameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	this->updatePlayer(dt);
	this->updatePlayerGui(dt);
	this->updateDebugText(dt);

	if (!paused && !gameOver && !help)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->updateWorldBoundsCollision(player, dt);//musze sprawdzic kolizje przed ruszeniem postaci, koniecznie o tym pamietaj
		this->updateTileMap(player, dt);
		this->player->update(dt, this->mousePostView, this->view);
		this->enemy->update(dt, this->mousePostView, this->view);
		this->playerGui->update(dt);
		this->enemyGui->update(dt);
		this->updateDistance(player, enemy, dt);
		this->updateEmemies(dt);
		this->playerGui->update(dt);
		this->enemyGui->update(dt);
		this->tts->update(dt);




	}
	else
	{
		if (help)
		{
			this->helpState->update(this->mousePostWindow);

		}
		else if (gameOver)
		{
			this->gameOverState->update(this->mousePostWindow);

		}
		else if (paused)
		{
			this->pauseMenu->update(this->mousePostWindow);

		}
		this->updatePauseMenuButtons();
	}
}

void LoadGameState::updateTileMap(Entity* entity, const float& dt)//sprawdzic
{

}


void LoadGameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->renderTexture.clear();
	//renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);
	this->tts->render(this->renderTexture);
	this->player->render(this->renderTexture);
	this->enemy->render(this->renderTexture);
	renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);
	this->enemyGui->render(this->renderTexture);

	if (gameOver)
	{
		renderTexture.setView(this->renderTexture.getDefaultView());
		this->gameOverState->render(renderTexture);
	}
	else if (help)
	{
		renderTexture.setView(this->renderTexture.getDefaultView());
		this->helpState->render(renderTexture);
	}
	else if (paused)
	{
		renderTexture.setView(this->renderTexture.getDefaultView());
		this->pauseMenu->render(renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(renderSprite);




}

void LoadGameState::saveToFile(string path)
{
	ofstream ofs(path);
	if (ofs.is_open())
	{
		ofs << this->player->getPosition().x << endl;
		ofs << this->player->getPosition().y << endl;
		ofs << this->player->getAttributeComponent()->hp << endl;
		ofs << this->player->getAttributeComponent()->exp << endl;
		ofs << this->enemy->getPosition().x << endl;
		ofs << this->enemy->getPosition().y << endl;
		ofs << this->enemy->getAttributeComponent()->hpEnemy << endl;
		ofs << this->enemy->getAttributeComponent()->exp << endl;
		ofs << this->enemyNumber << endl;
		ofs << this->playerGui->level << endl;

	}
	ofs.clear();
	ofs.seekp(0);//ustaw na poczatek
	ofs.close();

}

void LoadGameState::saveToFileGui(string path)
{
	ofstream ofs(path);
	if (ofs.is_open())
	{
		ofs << 1;

	}
	ofs.clear();
	ofs.seekp(0);//ustaw na poczatek
	ofs.close();
}

void LoadGameState::loadFromFile(string path)
{
	cout << "Pobieram dane z saveGame" << endl;
	load = true;
	changeEnemy = true;
	ifstream ifs(path);
	if (ifs.is_open())
	{
	
		ifs >> playerPosition_x;
		cout << playerPosition_x << endl;
		ifs >> playerPosition_y;
		cout << playerPosition_y << endl;
		ifs >> playerHp;
		cout << playerHp << endl;
		ifs >> playerExp;
		cout << playerHp << endl;
		ifs >> enemyPosition_x;
		cout << enemyPosition_x << endl;
		ifs >> enemyPosition_y;
		cout << enemyPosition_y << endl;
		ifs >> enemyHp;
		cout << enemyHp << endl;
		ifs >> enemyExp;
		cout << enemyHp << endl;
		ifs >> enemyNumberSave;
		cout <<"NUMER WROGA"<<" "<< enemyNumberSave << endl;
		ifs >> levelSave;
		cout << "Level Save" << " " << levelSave << endl;
	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();
	load = false;
}

void LoadGameState::loadFromFileGui(string path)
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

const bool LoadGameState::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

void LoadGameState::updatePlayerInput(const float& dt)//sprawdzoen,dziala
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left"))))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Right"))))
	{
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Up"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Down"))))
	{
		this->player->move(0.f, 1.f, dt);
	}


}

void LoadGameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
	if (Keyboard::isKeyPressed(Keyboard::C) && this->getKeyTime())
	{
		this->playerGui->toggleCharacterTab();
	}
}

void LoadGameState::updateInput(const float dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape) && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
	{
		if (!this->paused)
		{
			this->pauseinState();
			this->ungameOverStateinState();
			this->unhelpinState();
		}
		else
		{
			this->unpauseinState();
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::F1) && this->getKeyTime())
	{
		if (!this->help)
		{
			this->helpStateinState();
			this->ungameOverStateinState();
			this->unpauseinState();
		}
		else
		{
			this->unhelpinState();
		}
	}

}

void LoadGameState::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
	if (helpState->isButtonPressed("Quit"))
	{
		this->endState();
	}
	if (gameOverState->isButtonPressed("Quit"))
	{
		this->endState();
	}
	if (pauseMenu->isButtonPressed("Save"))
	{
		this->saveToFile("Config/saveGame.txt");
		this->saveToFileGui("Config/saveGui.txt");
	}
}


void LoadGameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePostView, this->view);
	this->enemy->update(dt, this->mousePostView, this->view);

}

void LoadGameState::updateEmemies(const float& dt)
{

	if (Mouse::isButtonPressed(Mouse::Left) && this->player->getWeapon()->getAttackTimer())
	{
		this->player->setInitAttack(true);
	}

	enemy->update(dt, this->mousePostView, this->view);
	this->updateCombat(player, enemy, dt);


	this->updateWorldBoundsCollision(player, dt);
	this->updateWorldBoundsCollision(enemy, dt);


		controlExp = true;
		if (enemy->isDead())
		{
			cout << "Jestem w enemy Dead" << endl;
			if (controlExp)
			{
				this->player->gainExp(enemy->getGainExp());
			}

			cout << "Update Enemy Hp w updateEnemies" << endl;
			cout << "Gain EXP" << endl;
			this->tts->addTextTag(Experience_Tag, this->player->getPosition().x - 40.f, this->player->getPosition().y - 30.f, static_cast<int>(enemy->getGainExp()), "+", "EXP");
			this->initEnemy();
			this->initEnemyGui();
			controlExp = false;
		}


	this->player->setInitAttack(false);

}

void LoadGameState::updateCombat(Player* player, Enemy* enemy, const float& dt)
{

	this->player->getAttributeComponent()->updateLevel();
	if (this->player->getInitAttack() && enemy->getGlobalBounds().contains(this->mousePostWindow.x, this->mousePostWindow.y)
		&& enemy->getDistance(*this->player) < this->player->getWeapon()->getRange() && enemy->getDamageTimerDone())
	{

		cout << "Jestem " << endl;
		int damage = static_cast<int>(this->player->getWeapon()->getDamage());
		enemy->loseHp(damage);
		this->tts->addTextTag(Default_Tag, enemy->getPosition().x, enemy->getPosition().y, damage, "", "");


	}
	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
		this->player->getAttributeComponent()->updateLevel();
		cout << "Jestem 2" << endl;
		int damage = enemy->getAttributeComponent()->damageMax;
		this->player->loseHp(damage);
		this->playerGui->updateHPBar();
		this->tts->addTextTag(Negative_Tag, player->getPosition().x - 30.f, player->getPosition().y, damage, "-", "HP");
		if (this->player->getAttributeComponent()->hp == 0)
		{
			
			if (!this->gameOver)
			{
				this->gameOverStateinState();
				this->unhelpinState();
				this->unpauseinState();
				this->initPauseMenuGameOver();
			}
			else
			{
				this->ungameOverStateinState();
			}


		}
	}
}

void LoadGameState::updateDebugText(const float dt)
{

}
void LoadGameState::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->stateData->gfxSettings->resolutions.width)
	{
		entity->setPosition(this->stateData->gfxSettings->resolutions.width - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->stateData->gfxSettings->resolutions.height)
	{
		entity->setPosition(entity->getPosition().x, this->stateData->gfxSettings->resolutions.height - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}

void LoadGameState::updateDistance(Player* player, Enemy* enemy, const float& dt)
{
	Vector2f moveVec;
	moveVec.x = player->getPosition().x - enemy->getPosition().x;
	moveVec.y = player->getPosition().y - enemy->getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if (characterAlyss == 1)
	{
		if ((player->getPosition().x != enemy->getPosition().x) && abs(vecLength) < 400.f || (player->getPosition().y != enemy->getPosition().y) && abs(vecLength) < 400.f)//jezeli ich pozycje sa rozne
		{
			if ((player->getPosition().x - enemy->getPosition().x <= 55 && player->getMovementComponent()->getVelocity().x == 0) || (player->getPosition().y - enemy->getPosition().y <= 55 && player->getMovementComponent()->getVelocity().y == 0))
			{
				enemy->stopVelocity();
			}
			else
			{
				enemy->move(moveVec.x, moveVec.y, dt);

			}

		}
	}

	if (characterHorace == 1)
	{
		if ((player->getPosition().x != enemy->getPosition().x) && abs(vecLength) < 500.f || (player->getPosition().y != enemy->getPosition().y) && abs(vecLength) < 500.f)//jezeli ich pozycje sa rozne
		{
			if ((player->getPosition().x - enemy->getPosition().x <= 50 && player->getMovementComponent()->getVelocity().x == 0) || (player->getPosition().y - enemy->getPosition().y <= 50 && player->getMovementComponent()->getVelocity().y == 0))
			{
				enemy->stopVelocity();
			}
			else
			{
				enemy->move(moveVec.x, moveVec.y, dt);

			}

		}
	}
	if (characterWill == 1)
	{
		if ((player->getPosition().x != enemy->getPosition().x) && abs(vecLength) < 400.f || (player->getPosition().y != enemy->getPosition().y) && abs(vecLength) < 400.f)//jezeli ich pozycje sa rozne
		{
			if ((player->getPosition().x - enemy->getPosition().x <= 60 && player->getMovementComponent()->getVelocity().x == 0) || (player->getPosition().y - enemy->getPosition().y <= 60 && player->getMovementComponent()->getVelocity().y == 0))
			{
				enemy->stopVelocity();
			}
			else
			{
				enemy->move(moveVec.x, moveVec.y, dt);

			}

		}
	}
}
void LoadGameState::chooseCharacter()
{
	ifstream ifsAlyss("Config/alyss.txt");
	if (ifsAlyss.is_open())
	{
		ifsAlyss >> characterAlyss;
	}
	ifsAlyss.clear();
	ifsAlyss.seekg(0);//beginning
	ifsAlyss.close();


	ifstream ifsHorace("Config/horace.txt");
	if (ifsHorace.is_open())
	{
		ifsHorace >> characterHorace;
	}
	ifsHorace.clear();
	ifsHorace.seekg(0);//beginning
	ifsHorace.close();


	ifstream ifsWill("Config/will.txt");
	if (ifsWill.is_open())
	{
		ifsWill >> characterWill;
	}
	ifsWill.clear();
	ifsWill.seekg(0);//beginning
	ifsWill.close();

}
