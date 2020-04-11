#include "EnemySpawn.h"

EnemySpawn* EnemySpawn::__instance = NULL;

EnemySpawn* EnemySpawn::getInstance() {
	if (__instance == NULL) __instance = new EnemySpawn();
	return __instance;
}

void EnemySpawn::LoadDefaut()	{

}

EnemySpawn::EnemySpawn()
{
	enemypollIndex[ZombieIndex*1000] = 1;
	enemypoll[ZombieIndex * 1000 ] = new Zombie();
	enemypoll[ZombieIndex * 1000]->isFree = true;
}

void EnemySpawn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//enemypoll[ZombieIndex * 1000]->Update(dt,coObjects);
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			enemypoll[enemyType * 1000 + enemyIdex]->Update(dt,coObjects);
		}
	}
}

void EnemySpawn::Render()
{
	//enemypoll[ZombieIndex * 1000]->Render();
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			enemypoll[enemyType * 1000 + enemyIdex]->Render();
		}
	}
}



Enemy* EnemySpawn::getEnemy(int type,float x,float y) {
	int index = enemypollIndex[type * 1000];
	for (int i = 0; i < index; i++) {
		Enemy* enemy = enemypoll[type * 1000 + i];
		if (enemy->isFree) {
			enemy->SetPosition(x, y);
			enemy->SetState(0);
			enemy->isFree = false;
			return enemypoll[type * 1000 + i];
		}
		else
		{
			if (enemy->state == OBJ_DIE) {
				enemy->isFree = true;
				enemy->SetPosition(x, y);
				enemy->SetState(0);
				return enemypoll[type * 1000 + i];
			}
		}
	}

	//create new obj in pool
	Enemy* enemy = new Zombie();
	if (type == ZombieIndex) {
		enemy = new Zombie();
		
	}
	enemy->isFree = false;
	enemy->SetState(0);
	enemy->SetPosition(x, y);
	enemypoll[type * 1000 + index] = enemy;
	index++;
	enemypollIndex[type * 1000] = index;

	return enemypoll[type * 1000 + index-1];

}

vector<LPGAMEOBJECT> EnemySpawn::getEnemlist()
{
	vector<LPGAMEOBJECT> result;
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			if (enemypoll[enemyType * 1000 + enemyIdex]->GetState() !=OBJ_DIE) {
				result.push_back(enemypoll[enemyType * 1000 + enemyIdex]);
			}
		}
	}
	return result;
}


EnemySpawn::~EnemySpawn()
{
}
