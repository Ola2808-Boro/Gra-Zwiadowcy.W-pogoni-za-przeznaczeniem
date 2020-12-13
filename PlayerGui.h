#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
class Player;
//class RectangleShape;


class PlayerGui
{
private:
	Player* player;
	Font font;

	//Level Element
	string  levelElementString;
	RectangleShape  levelElementBack;
	Text levelElementText;


	//exp
	Text expBarText;
	string expBarString;
	RectangleShape expBarBack;
	RectangleShape expBarInner;
	float expBarMaxSizeWidth;

	//hp
	Text hpBarText;
	string hpBarString;
	RectangleShape hpBarBack;
	RectangleShape hpBarInner;
	float hpBarMaxSizeWidth;

	void initFont();
	void initHPBar();
	void initExpBar();
	void initLevelElement();
public:
	PlayerGui(Player* player);
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