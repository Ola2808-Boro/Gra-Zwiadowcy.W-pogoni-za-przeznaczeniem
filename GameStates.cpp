GameStates::GameStates(StateData* stateData) :State(stateData)
{
	//11 funkcji
	this->iniDefferedRender();
	this->initView();
	this->initKeybinds();
	this->InitFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initKeyTime();
	this->initDebugText();
	this->initPlayers();
	this->initPlayerGui();
	this->initEnemySystem();
	this->initEnemy();
	this->initTileMap();
	this->initSystems();




}
//--------------------------------------------------------Destruktor-----------------------------------------------//
GameStates::~GameStates()
{
	delete this->pauseMenu;
	delete this->player;
	delete this->playerGui;
	delete this->tileMap;
	delete this->enemysystem;
	delete this->tts;
	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
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
	/*if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/sprite/PLAYER_SHEET2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}*/
	this->temp.loadFromFile("Resources/Images/sprite/PLAYER_SHEET2.png");
	this->textures["Player_1"] =temp;
	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/sprite/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
	if (!this->textures["PLAYER2_SHEET"].loadFromFile("Resources/Images/sprite/PLAYER_SHEET.png"))
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
	if (!this->textures["FIGHTER_SHEET"].loadFromFile("Resources/Images/sprite/wojownikduzy.png"))
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

void GameStates::initEnemySystem()
{
	
	this->enemysystem = new EnemySystem(this->activeEnemies, this->textures,*this->player);
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
	this->rat = new Rat(500, 600, this->textures["RAT1_SHEET"]);
}


void GameStates::initPlayers()
{
	this->player = new Player(0, 0, this->textures["Player_1"]);
	this->player2 = new Player2(800, 600, this->textures["PLAYER2_SHEET"]);
	this->fighter = new Fighter(1000, 400, this->textures["FIGHTER_SHEET"]);
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
	
	if (!paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->updateWorldBoundsCollision(player,dt);//musze sprawdzic kolizje przed ruszeniem postaci, koniecznie o tym pamietaj
		this->updateTileMap(player,dt);
		this->player->update(dt,this->mousePostView,this->view);
		this->player2->update(dt,this->mousePostView,this->view);
		this->fighter->update(dt,this->mousePostView,this->view);
		this->rat->update(dt,this->mousePostView,this->view);
		this->playerGui->update(dt);
		this->updateDistance(player, player2, dt);
		this->updateCombat(player,player2,dt);
		this->updateEmemies(dt);
		this->tts->update(dt);
		
		
		
	}
	else
	{

		this->pauseMenu->update(this->mousePostWindow);
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
	this->player2->render(this->renderTexture);
	this->fighter->render(this->renderTexture);
	this->rat->render(this->renderTexture);
	renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);
	if (this->paused)
	{
		renderTexture.setView(this->renderTexture.getDefaultView());
		this->pauseMenu->render(renderTexture);
	}
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(renderSprite);


	

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
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)/*::Key(this->keybinds.at("Close")*/ && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameStates::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
}

void GameStates::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePostView, this->view);
	this->player2->update(dt, this->mousePostView, this->view);

}

void GameStates::updateEmemies(const float& dt)
{

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		this->player->setInitAttack(true);
	}
	this->player->setInitAttack(false);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
		this->player->setInitAttack(true);
	{
		this->updateWorldBoundsCollision(player, dt);
		this->updateWorldBoundsCollision(player2, dt);
		

		if (player2->isDead())
		{
			this->player->gainExp(enemy->getGainExp());
			this->tts->addTextTag(Experience_Tag, this->player->getPosition().x - 40.f, this->player->getPosition().y - 30.f, static_cast<int>(enemy->getGainExp()), "+", "EXP");
			delete player2;
		}
		

	}

	this->player->setInitAttack(false);
	
}

void GameStates::updateCombat(Player* player ,Player2*player2,const float& dt)
{
	
	if (this->player->getInitAttack()
		&& player2->getGlobalBounds().contains(this->mousePostView) 
		&& player2->getDistance(*this->player) < this->player->getWeapon()->getRange())
	{
		
			int damage = static_cast<int>(this->player->getWeapon()->getDamage());
			player2->loseHp(damage);
			this->tts->addTextTag(Default_Tag, player2->getPosition().x, player2->getPosition().y , damage,"","");
		
	}
	if (player2->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
		int damage = player2->getAttributeComponent()->damageMax;
		this->player->loseHp(damage);
		this->tts->addTextTag(Negative_Tag, player->getPosition().x - 30.f, player->getPosition().y, damage, "-", "HP");
	}
}

void GameStates::updateDebugText(const float dt)
{

	std::stringstream ss;

	ss << "Mouse Pos View: " << this->mousePostView.x << " " << this->mousePostView.y << "\n"
		<< "Active Enemies: " << this->activeEnemies.size() << "\n";

	this->debugText.setString(ss.str());
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

void GameStates::updateDistance(Player* player, Player2* player2,const float&dt)
{
	Vector2f moveVec;
	moveVec.x = player->getPosition().x - player2->getPosition().x;
	moveVec.y = player->getPosition().y - player2->getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((player->getPosition().x != player2->getPosition().x) && abs(vecLength) < 500.f|| (player->getPosition().y != player2->getPosition().y) && abs(vecLength) < 500.f)//jezeli ich pozycje sa rozne
	{
		if (player->getPosition().x - player2->getPosition().x > 60|| player->getPosition().y - player2->getPosition().y > 60)
		{
			player2->move(moveVec.x, moveVec.y, dt);
		}
		else
		{
			player2->stopVelocity();
		}

	}


	Vector2f moveVec1;
	moveVec1.x = player->getPosition().x - fighter->getPosition().x;
	moveVec1.y = player->getPosition().y - fighter->getPosition().y;

	float vecLength1 = sqrt(pow(moveVec1.x, 2) + pow(moveVec1.y, 2));

	moveVec1 /= vecLength1;

	if ((player->getPosition().x != fighter->getPosition().x) && abs(vecLength1) < 500.f || (player->getPosition().y != fighter->getPosition().y) && abs(vecLength1) < 500.f)//jezeli ich pozycje sa rozne
	{
		if (player->getPosition().x - fighter->getPosition().x > 60 || player->getPosition().y - fighter->getPosition().y > 60)
		{
			fighter->move(moveVec1.x, moveVec1.y, dt);
		}

	}
	else
	{
		fighter->stopVelocity();
	}
}






