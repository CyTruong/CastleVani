#include "PlayerStatus.h"
#include "debug.h"
#include "Game.h"


PlayerStatus* PlayerStatus::___instance = NULL;

PlayerStatus * PlayerStatus::getInstance()
{
	if (___instance == NULL) 
		___instance = new PlayerStatus();
	return ___instance;
}

PlayerStatus::PlayerStatus()
{
	PlayerHp = 10;
	PlayerMana = 10;
	SubWeaponIndex = 0;
	Score = 0;
	Whipslevel = 0;
	enemyHp = 16;
}


PlayerStatus::~PlayerStatus()
{
}
