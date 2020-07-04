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
	enemypollIndex[ZombieIndex * 1000] = 1;
	enemypoll[ZombieIndex * 1000] = new Zombie();
	enemypoll[ZombieIndex * 1000]->isFree = true;

	enemypollIndex[BatIndex * 1000] = 1;
	Bat* bat = new Bat();
	bat->player = player;
	enemypoll[BatIndex * 1000] = bat;
	enemypoll[BatIndex * 1000]->isFree = true;

	enemypollIndex[WoftIndex * 1000] = 1;
	Woft* wolf = new Woft();
	wolf->player = player;
	enemypoll[WoftIndex * 1000] = wolf;
	enemypoll[WoftIndex * 1000]->isFree = true;

	enemypollIndex[KnightIndex * 1000] = 1;
	Knight* knight = new Knight();
	knight->player = player;
	enemypoll[KnightIndex * 1000] = knight;
	enemypoll[KnightIndex * 1000]->isFree = true;

	enemypollIndex[BossIndex * 1000] = 1;
	Boss* boss = new Boss();
	boss->player = player;
	enemypoll[BossIndex * 1000] = boss;
	enemypoll[BossIndex * 1000]->isFree = true;

	enemypollIndex[GhostIndex * 1000] = 1;
	Ghost* ghost = new Ghost();
	ghost->player = player;
	enemypoll[GhostIndex * 1000] = ghost;
	enemypoll[GhostIndex * 1000]->isFree = true;

	enemypollIndex[SkeletonIndex * 1000] = 1;
	Skeleton* skeleton = new Skeleton();
	skeleton->player = player;
	enemypoll[SkeletonIndex * 1000] = skeleton;
	enemypoll[SkeletonIndex * 1000]->isFree = true;

	enemypollIndex[SkeletonBoneIndex * 1000] = 1;
	SkeletonBone* bone = new SkeletonBone();
	bone->player = player;
	enemypoll[SkeletonBoneIndex * 1000] = bone;
	enemypoll[SkeletonBoneIndex * 1000]->isFree = true;
}

void EnemySpawn::Clear(LPGAMEOBJECT player)
{
	this->player = player;

	enemypollIndex[ZombieIndex * 1000] = 1;
	enemypoll[ZombieIndex * 1000] = new Zombie();
	enemypoll[ZombieIndex * 1000]->isFree = true;

	enemypollIndex[BatIndex * 1000] = 1;
	Bat* bat = new Bat();
	bat->player = player;
	enemypoll[BatIndex * 1000] = bat;
	enemypoll[BatIndex * 1000]->isFree = true; 

	enemypollIndex[WoftIndex * 1000] = 1;
	Woft* wolf = new Woft();
	wolf->player = player;
	enemypoll[WoftIndex * 1000] = wolf;
	enemypoll[WoftIndex * 1000]->isFree = true;

	enemypollIndex[KnightIndex * 1000] = 1;
	Knight* knight = new Knight();
	knight->player = player;
	enemypoll[KnightIndex * 1000] = knight;
	enemypoll[KnightIndex * 1000]->isFree = true;

	enemypollIndex[BossIndex * 1000] = 1;
	Boss* boss = new Boss();
	boss->player = player;
	enemypoll[BossIndex * 1000] = boss;
	enemypoll[BossIndex * 1000]->isFree = true;

	enemypollIndex[GhostIndex * 1000] = 1;
	Ghost* ghost = new Ghost();
	ghost->player = player;
	enemypoll[GhostIndex * 1000] = ghost;
	enemypoll[GhostIndex * 1000]->isFree = true;

	enemypollIndex[SkeletonIndex * 1000] = 1;
	Skeleton* skeleton = new Skeleton();
	skeleton->player = player;
	enemypoll[SkeletonIndex * 1000] = skeleton;
	enemypoll[SkeletonIndex * 1000]->isFree = true;

	enemypollIndex[SkeletonBoneIndex * 1000] = 1;
	SkeletonBone* bone = new SkeletonBone();
	bone->player = player;
	enemypoll[SkeletonBoneIndex * 1000] = bone;
	enemypoll[SkeletonBoneIndex * 1000]->isFree = true;
}

void EnemySpawn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			Enemy* e = enemypoll[enemyType * 1000 + enemyIdex];
			if (e->state==OBJ_DIE) {
				e->isFree = true;
			/*	int index = enemypollIndex[enemyType * 1000];
				enemypollIndex[enemyType * 1000] = index-1;*/
			}else
				if(!enemypoll[enemyType * 1000 + enemyIdex]->isFree)
					enemypoll[enemyType * 1000 + enemyIdex]->Update(dt,coObjects);
		}
	}
}

void EnemySpawn::Render()
{
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			if (!enemypoll[enemyType * 1000 + enemyIdex]->isFree) {
				enemypoll[enemyType * 1000 + enemyIdex]->Render();
			}
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
			enemypoll[type * 1000 + i] = enemy;
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
	if (type == BatIndex) {
		enemy = new Bat();
		enemy->player = this->player;
	}
	if (type == WoftIndex) {
		enemy = new Woft();
		enemy->player = this->player;
	}
	if (type == KnightIndex) {
		enemy = new Knight();
		enemy->player = this->player;
	}
	if (type == BossIndex) {
		enemy = new Boss();
		enemy->player = this->player;
	}
	if (type == GhostIndex) {
		enemy = new Ghost();
		enemy->player = this->player;
	}
	if (type == SkeletonIndex) {
		enemy = new Skeleton();
		enemy->player = this->player;
	}
	if (type == SkeletonBoneIndex) {
		enemy = new SkeletonBone();
		enemy->player = this->player;
	}
	enemy->isFree = false;
	enemy->SetState(0);
	enemy->SetPosition(x, y);
	enemypoll[type * 1000 + index] = enemy;
	index++;
		enemypollIndex[type * 1000] = index;

	return enemypoll[type * 1000 + index-1];

}

vector<LPGAMEOBJECT>* EnemySpawn::getEnemlist()
{
	vector<LPGAMEOBJECT>* result = new vector<LPGAMEOBJECT>();
	for (int enemyType = 1; enemyType <= COUNT; enemyType++) {
		int numberofaeneytype = enemypollIndex[enemyType * 1000];
		for (int enemyIdex = 0; enemyIdex < numberofaeneytype; enemyIdex++) {
			if (enemypoll[enemyType * 1000 + enemyIdex]->GetState() != OBJ_DIE) {
				result->push_back(enemypoll[enemyType * 1000 + enemyIdex]);
			}
		}
	}
	return result;
}


EnemySpawn::~EnemySpawn()
{
}
