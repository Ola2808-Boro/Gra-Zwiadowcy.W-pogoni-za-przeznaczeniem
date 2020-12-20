#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "Gui.h"
class Player;
//class RectangleShape;


class PlayerGui
{
private:

	VideoMode& vm;
	Player* player;
	Font font;

	//Level Element
	string  levelElementString;
	RectangleShape  levelElementBack;
	Text levelElementText;


	//exp
	gui::ProgressBar* expBar;

	//hp
	gui::ProgressBar* hpBar;


	void initFont();
	void initHPBar();
	void initExpBar();
	void initLevelElement();
public:
	PlayerGui(Player* player,VideoMode& vm);
	virtual~PlayerGui();

	void update(const float& dt);
	void render(RenderTarget& target);
	void renderHPBar(RenderTarget& target);
	void renderExpBar(RenderTarget& target);
	void renderLevelElement(RenderTarget& target);
	void updateHPBar();
	void updateLevelElement();
	void updateExpBar();
};
#endif // !PLAYERGUI_H
