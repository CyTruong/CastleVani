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
	SubWeaponIndex = 1;
}


PlayerStatus::~PlayerStatus()
{
}
