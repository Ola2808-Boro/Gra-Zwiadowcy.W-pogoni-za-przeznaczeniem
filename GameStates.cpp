#include"stdafx.h"
#include "GameStates.h"

//----------------------------------------------Konstruktor-------------------------------------------------//
GameStates::GameStates(StateData* stateData) :State(stateData)
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
	this->initPlayers();
	this->initPlayerGui();
	this->initEnemy();
	this->initTileMap();
	this->initSystems();
	




}
//--------------------------------------------------------Destruktor-----------------------------------------------//
GameStates::~GameStates()
{
	delete this->pauseMenu;
	delete this->gameOverState;
	delete this->helpState;
	delete this->player;
	delete this->enemy;
	delete this->playerGui;
	delete this->tileMap;
	delete this->tts;
	
}

//----------------------------------------------Funkcje---------------------------------/
void GameStates::iniDefferedRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0, this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height));
}

void GameStates::initView()
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

void GameStates::initKeybinds()
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

void GameStates::initTextures()
{
	
	this->temp.loadFromFile("Resources/Images/sprite/PLAYER_SHEET2.png");
	this->textures["Player_1"] =temp;
	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/sprite/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
	if (!this->textures["PLAYER2_SHEET"].loadFromFile("Resources/Images/sprite/enemy.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
	if (!this->textures["BIRD1_SHEET"].loadFromFile("Resources/Images/sprite/bird1_61x57.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["HORES_SHEET"].loadFromFile("Resources/Images/sprite/horse.jpg"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["FIGHTER_SHEET"].loadFromFile("Resources/Images/sprite/a.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
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
}
void GameStates::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/Langar-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void GameStates::initPauseMenu()//tyczy sie new game
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize
	this->pauseMenu = new PausedMenu(this->stateData->gfxSettings->resolutions, this->font);
	this->pauseMenu->addButtons("Quit", gui::p2pY(74.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm),"Quit");
	this->pauseMenu->addButtons("Save", gui::p2pY(60.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm),"Save");
	/*this->pauseMenu->addButtons("Save", 250.f, 800.f,100.f,50.f, "Save");*/
}

void GameStates::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,"Resources/Images/tile/tilesheet1.png" );//sprawdzic, czy ze zmiana dziala bylo 10 10
	//this->tileMap=new TileMap("text.txt");// zmienic nazwe funkcji na loadFromFile
}

void GameStates::initPlayerGui()
{
	/*Player* player, VideoMode& vm*/
	this->playerGui = new PlayerGui(this->player,this->stateData->gfxSettings->resolutions);//sprawdzic czy jest w konstruktorze i destruktorze
}



void GameStates::initSystems()
{
	this->tts = new TextTagSystem("Fonts/FjallaOne-Regular.ttf");
}

void GameStates::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void GameStates::initDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}

void GameStates::initEnemy()
{
	
}

void GameStates::initPauseMenuGameOver()
{
	
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	this->gameOverState = new GameOverState(this->stateData->gfxSettings->resolutions, this->font);
	this->gameOverState->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");
		
}

void GameStates::initHelpState()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	this->helpState = new HelpState(this->stateData->gfxSettings->resolutions, this->font);
	this->helpState->addButtons("Quit", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm), "Quit");
}


void GameStates::initPlayers()
{
	this->chooseCharacter();

	this->enemy = new Enemy(1600, 900, this->textures["PLAYER2_SHEET"]);//WROG


	if (characterWill==1)
	{
		
		this->player = new Player(1600, 400, this->textures["WILL_SHEET"]);
		
	}

	if (characterAlyss==1)
	{
		
		this->player = new Player(1600, 400, this->textures["ALYSS_SHEET"]);	
		
	}

	if (characterHorace==1)
	{
		this->player = new Player(1600, 400, this->textures["HORACE_SHEET"]);
		
	}
}

void GameStates::updateView(const float& dt)
{
	
	this->view.setSize(Vector2f(static_cast<float>(stateData->gfxSettings->resolutions.width), static_cast<float>(stateData->gfxSettings->resolutions.height)));
	this->view.setCenter(
		floor(this->player->getPosition().x + (static_cast<float>(this->mousePostWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolutions.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->mousePostWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolutions.height / 2)) / 10.f)
	);
	
	this->mousePosGrid.x =static_cast<int>( this->view.getCenter().x )/ static_cast<int>(this->stateData->gridSize);
	this->mousePosGrid.y =static_cast<int>( this->view.getCenter().y )/ static_cast<int>(this->stateData->gridSize);
}

void GameStates::update(const float& dt)
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
		this->updateWorldBoundsCollision(player,dt);//musze sprawdzic kolizje przed ruszeniem postaci, koniecznie o tym pamietaj
		this->updateTileMap(player,dt);
		this->player->update(dt, this->mousePostView, this->view);
		this->playerGui->update(dt);
		this->enemy->update(dt,this->mousePostView,this->view);
		this->updateDistance(player, enemy, dt);
		this->updateEmemies(dt);
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

void GameStates::updateTileMap(Entity* entity,const float& dt)//sprawdzic
{
	
}


void GameStates::render(RenderTarget* target)
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
	else if(paused)
	{
			renderTexture.setView(this->renderTexture.getDefaultView());
			this->pauseMenu->render(renderTexture);
	}
	
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(renderSprite);


	

}

void GameStates::saveToFile(string path)
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
		ofs << this->enemy->getAttributeComponent()->hp << endl;
		ofs << this->enemy->getAttributeComponent()->exp << endl;
		
	}
	ofs.clear();
	ofs.seekp(0);//ustaw na poczatek
	ofs.close();

}

void GameStates::chooseCharacter()
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

const bool GameStates::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

void GameStates::updatePlayerInput(const float& dt)//sprawdzoen,dziala
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

void GameStates::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
	if (Keyboard::isKeyPressed(Keyboard::C)&& this->getKeyTime())
	{
		this->playerGui->toggleCharacterTab();
	}
}

void GameStates::updateInput(const float dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)&& this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
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

void GameStates::updatePauseMenuButtons()
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
	if(pauseMenu->isButtonPressed("Save"))
	{
		this->saveToFile("Config/saveGame.txt");
	}
}


void GameStates::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePostView, this->view);
	this->enemy->update(dt, this->mousePostView, this->view);

}

void GameStates::updateEmemies(const float& dt)
{
	if (Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
		this->player->setInitAttack(true);

	
		enemy->update(dt, this->mousePostView, this->view);

		this->updateCombat(player,enemy, dt);
		this->updateWorldBoundsCollision(player,dt);
		this->updateWorldBoundsCollision(enemy,dt);

		//DANGEROUS!!!
		if (enemy->isDead())
		{
			this->player->gainExp(enemy->getGainExp());
			this->tts->addTextTag(Experience_Tag, this->player->getPosition().x - 40.f, this->player->getPosition().y - 30.f, static_cast<int>(enemy->getGainExp()), "+", "EXP");

		}

	this->player->setInitAttack(false);
}

void GameStates::updateCombat(Player* player ,Enemy* enemy,const float& dt)
{


	if (this->player->getInitAttack()
		&& enemy->getDistance(*this->player) < this->player->getWeapon()->getRange())
	{
		
			cout << "Jestem " << endl;
			int damage = static_cast<int>(this->player->getWeapon()->getDamage());
			enemy->loseHp(damage);
			this->tts->addTextTag(Default_Tag, enemy->getPosition().x, enemy->getPosition().y , damage,"","");
			
		
	}
	

	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
		cout << "Jestem 2" << endl;
		int damage = enemy->getAttributeComponent()->damageMax;
		this->player->loseHp(damage);
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

void GameStates::updateDebugText(const float dt)
{

}
void GameStates::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width >  this->stateData->gfxSettings->resolutions.width)
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

void GameStates::updateDistance(Player* player, Enemy* enemy,const float&dt)
{

	Vector2f moveVec;
	moveVec.x = player->getPosition().x - enemy->getPosition().x;
	moveVec.y = player->getPosition().y - enemy->getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((player->getPosition().x != enemy->getPosition().x) && abs(vecLength) < 500.f|| (player->getPosition().y != enemy->getPosition().y) && abs(vecLength) < 500.f)//jezeli ich pozycje sa rozne
	{
		if (player->getPosition().x - enemy->getPosition().x > 60|| player->getPosition().y - enemy->getPosition().y > 60)
		{
			enemy->move(moveVec.x, moveVec.y, dt);
		}
		else
		{
			enemy->stopVelocity();
		}

	}
	
}




