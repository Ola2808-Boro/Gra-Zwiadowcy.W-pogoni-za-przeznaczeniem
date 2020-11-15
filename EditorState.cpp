#include "EditorState.h"


void EditorState::initKeybinds()
{
	ifstream ifs("Config/editorstate_keybinds.ini");
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

void EditorState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void EditorState::initButtom()
{
	
}

void EditorState::initBackground()
{

}
void EditorState::initVariables()
{

}



EditorState::EditorState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states) :State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->InitFonts();
	this->initKeybinds();
	this->initButtom();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::updateButton()
{

	system("cls");
	cout << this->mousePostView.x << " " << this->mousePostView.y << endl;
	for (auto& it : this->buttons)
	{
		it.second->update(mousePostView);
	}
	
}

void EditorState::renderButtton(RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}


void EditorState::update(const float& dt)
{

	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButton();



}



void EditorState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}


	this->renderButtton(*target);

}

void EditorState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->endState();
	}
}