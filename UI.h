#pragma once
#include "d3dx9.h"
#include "Utils.h"
#include "Game.h"
#include "Sprites.h"
#define GAME_FONT L"prstart.ttf"

class UI
{
private:
	ID3DXFont *font;
	string info;

	int simonHP;
	int enemyHP;
	int uiHP;

	int score;
	int time;
	int item;
	int simonEnergy;
	int simonLife;
	int stage;
	int subWeapon;
public:
	UI(int simonHP, int simonEnergy, int simonLife, int stage);
	~UI();

	bool Initialize();
	void Update(int time, int simonHP, int simonEnergy, int simonLife, int stage,int subweapon,int score,int enemyHp);
	void Render();

	void LoadResource();
};

