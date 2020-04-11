#pragma once
#include <Windows.h>
#include "Zombie.h"
#include "Enemy.h"
#include "Zombie.h"

#define ZombieIndex 1
#define COUNT 1


class EnemySpawn
{
private:
	static EnemySpawn* __instance;
	unordered_map<int, Enemy*> enemypoll;
	unordered_map<int, int> enemypollIndex;
private:
	void LoadDefaut();
public:
	static EnemySpawn* getInstance();
	EnemySpawn();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	Enemy* getEnemy(int EnemyType,float x, float y);
	vector<LPGAMEOBJECT>  getEnemlist();
	~EnemySpawn();
};

