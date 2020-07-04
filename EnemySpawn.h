#pragma once
#include <Windows.h>
#include "Zombie.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Bat.h"
#include "Woft.h"
#include "Knight.h"
#include "Boss.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "SkeletonBone.h"


#define ZombieIndex 1
#define BatIndex 2
#define WoftIndex 3
#define KnightIndex 4
#define BossIndex 5
#define GhostIndex 6
#define SkeletonIndex 7
#define SkeletonBoneIndex 8
#define COUNT 8


class EnemySpawn
{
private:
	LPGAMEOBJECT player;
	static EnemySpawn* __instance;
	unordered_map<int, Enemy*> enemypoll;
	unordered_map<int, int> enemypollIndex;
private:
	void LoadDefaut();
public:
	static EnemySpawn* getInstance();
	EnemySpawn();
	void Clear(LPGAMEOBJECT player);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	Enemy* getEnemy(int EnemyType,float x, float y);
	vector<LPGAMEOBJECT>*  getEnemlist();
	~EnemySpawn();
};

