#include "Boss.h"
#include "PlayerStatus.h"
#include "Game.h"
#include "Brick.h"
#include "Grid.h"
#include "ItemSpaw.h"

Boss::Boss()
{
	Hp = 16;
	dirX = 0;
	dirY = 0;
	this->vx = 0;
	this->vy = 0;
	this->state = BOSS_ANI_IDLE;
	canchangepharse = true;
	state = false;
	PlayerStatus::getInstance()->SetEnemyHp(Hp);
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOSS_BBOX_WIDTH;
	bottom = y + BOSS_BBOX_HEIGHT;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"this - player %f %f - %f %f \n",this->x,this->y,player->x,player->y);
	if (this->x+30 < player->x && start == false) {
		start = true;
		LastPx = player->x;
		LastPy = player->y;
		StartX = this->x;
		StartY = this->y;
		pharse = BOSS_PHARSE_1;
	}
	if (start) {
		float vexX = LastPx - this->x;
		float vexY = LastPy - this->y;
		this->dirX = (this->dirX + vexX) / 2;
		this->dirY = (this->dirY + vexY) / 2;

		if (dirX > 0) {
			this->vx = BOSS_SPEED;
		}
		else {
			this->vx = -BOSS_SPEED;
		}
		this->vy = dirY * this->vx / dirX;

		if (abs(vy) > BOSS_SPEED*1.5) {
			if (vy < 0) {
				vy = -BOSS_SPEED;
			}
			if (vy > 0) {
				vy = BOSS_SPEED;
			}
		}
		float dis = sqrt((LastPx - this->x)*(LastPx - this->x) + (LastPy - this->y)*(LastPy - this->y));
		if (dis < 5 && canchangepharse) {
			if (pharse == BOSS_PHARSE_1) {
				//chuyển sang pharse 2
				int ranX = rand() % 100 - 50;
				int ranY = rand() % 50;
				LastPx = StartX + ranX;
				LastPy = StartY + ranY;
				pharse = BOSS_PHARSE_2;
			}
			else
				if (pharse == BOSS_PHARSE_2) {
					//Chuyển vền pharse 1
					pharse = BOSS_PHARSE_1;					
					LastPx = player->x;
					LastPy = player->y;
				}
			canchangepharse = false;
		}
		else {
			canchangepharse = true;
		}

		if (!PlayerStatus::getInstance()->isCamLocked()) {
			PlayerStatus::getInstance()->LockCamBoss();
			CBrick* brick = new CBrick();
			brick->SetPosition(575, 224);
			Grid::GetInstance()->Insert(brick);
		}
		CGame::GetInstance()->SetCamPos2(575, 36.8f, 768, 240);

	}
	
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (state == OBJ_DIE) {
		PlayerStatus::getInstance()->UnLockCamBoss();
	}

}

void Boss::Render()
{
	int ani = 0;

	if (vx != 0) {
		ani = BOSS_ANI_FLY;
	}
	if (vx = 0) {
		ani = BOSS_ANI_IDLE;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

bool Boss::minusHp(int dam)
{
	Hp = Hp - dam;
	PlayerStatus::getInstance()->SetEnemyHp(Hp);
	if (Hp <= 0) {
		ItemSpaw::getInstance()->CreateObj(this->x,this->y, 8);

		return true;
	}
	return false;
}

Enemy * Boss::clone()
{
	return nullptr;
}


Boss::~Boss()
{
}
