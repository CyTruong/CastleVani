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
	PlayerMana = 0;
	SubWeaponIndex = 0;
	Score = 0;
	Whipslevel = 0;
	EnemyHp = 16;
	StateIndex = 1;
	ZA_WARUDO = false;
	PlayerLife = 0;
}

void PlayerStatus::Renew()
{
	PlayerHp = 10;
	PlayerMana = 0;
	SubWeaponIndex = 0;
	Score = 0;
	Whipslevel = 0;
	EnemyHp = 16;
	StateIndex = 1;
	ZA_WARUDO = false;
	PlayerLife = 0;
}

void PlayerStatus::Reset()
{
	PlayerHp = 10;
	PlayerMana = 0;
	SubWeaponIndex = 0;
	Score = 0;
	Whipslevel = 0;
	EnemyHp = 16;
	ZA_WARUDO = false;
	PlayerLife=PlayerLife-1;
}


PlayerStatus::~PlayerStatus()
{
}
