﻿#include "SubWeapon.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "Axe.h"
#include "Boomerang.h"
#include "EnemySpawn.h"	
#include "PlayerStatus.h"
#include "TimeStop.h"
#include "ItemSpaw.h"
#include "Effect.h"
SubWeapon::SubWeapon()
{
	PlayerStatus::getInstance()->getSubWeaponIndex(weapon_type);
	isready = true;
	damage = 0;
	delaytimer = 0;
	
}

void SubWeapon::SetWeaponType(int weapon_id)
{
	this->weapon_type = weapon_id;
	PlayerStatus::getInstance()->SetSubWeapon(this->weapon_type);
	switch (weapon_id) {
	case SUB_WEAPON_DAGGER: 
		weapon = new Dagger();
		damage = 1;
		break;
	case SUB_WEAPON_HOLY:
		weapon = new HolyWater();
		damage = 1;
		break;
	case SUB_WEAPON_AXE:
		weapon = new Axe();
		damage = 2;
		break;
	case SUB_WEAPON_BOMERANG:
		weapon = new Boomerang();
		damage = 2;
		break;
	case SUB_WEAPON_THEWORD:
		weapon = new TimeStop();
		damage = 0;
	default: 
		break;
	}
	if(weapon!= NULL)
	weapon->y = 800;
}

void SubWeapon::GetWeaponType(int & weapon_id)
{
	weapon_id = this->weapon_type;
}

void  SubWeapon::GetWeapon(LPGAMEOBJECT & weapon)
{
	weapon = this->weapon;
}

void SubWeapon::Atk(float x, float y, float dir)
{
	delaytimer = 0;
	if (weapon_type!= SUB_WEAPON_NON && isready) {
		
		if (dir > 0) {
			tempoX = x+5;
		}
		else {
			tempoX = x - 5;
		}
		tempoY = y + 5;
		//this->weapon->SetPosition(x, y+5);
		int mana = 0;
		PlayerStatus::getInstance()->SubMana(1);
		//Nếu ít mana ko cho play
		/*if (mana <= 0) {
			return;
		}*/

		isready = false;
		this->effted = true;
		if (weapon_type == SUB_WEAPON_DAGGER) {
			if (dir < 0) {
				this->weapon->vx = -0.3;
			}
			else
				this->weapon->vx = 0.3;
		}
		if (weapon_type == SUB_WEAPON_HOLY) {
			if (dir < 0) {
				this->weapon->vx = -0.1;
			}
			else
				this->weapon->vx = 0.1;
			this->weapon->vy = -0.08f;
		}
		if (weapon_type == SUB_WEAPON_AXE) {
			if (dir < 0) {
				this->weapon->vx = -0.12;
			}
			else
				this->weapon->vx = 0.12;
			this->weapon->vy = -0.25f;
		}
		if (weapon_type == SUB_WEAPON_BOMERANG) {
			if (dir < 0) {
				this->weapon->vx = -0.15;
			}
			else
				this->weapon->vx = 0.15;
		}
		if (weapon_type == SUB_WEAPON_THEWORD) {
			if (weapon->vx==0) {
				this->weapon->vx = 10;
			}
		}
	}
	
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (weapon_type != SUB_WEAPON_NON) {
		float wl, wt, wr, wb;
		this->weapon->GetBoundingBox(wl, wt, wr, wb);


		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->atk_able && coObjects->at(i)->state != OBJ_DIE) {
				float l, t, r, b;
				coObjects->at(i)->GetBoundingBox(l, t, r, b);
							
				if (wl < r &&
					wr > l  &&
					wt < b &&
					wb > t) {
					coObjects->at(i)->SetState(OBJ_DIE);
					ItemSpaw::getInstance()->CreateObj(coObjects->at(i)->x, coObjects->at(i)->y, coObjects->at(i)->dropItem);
					weapon->SetState(-1);
					Effect::getInstance()->setHitEffect(true);
					Effect::getInstance()->setHitEffectPos(coObjects->at(i)->x + 3, coObjects->at(i)->y + 5);
					Effect::getInstance()->setDesEffect(true);
					Effect::getInstance()->setDesEffect((l + r) / 2, (t + b) / 2);
				}
			
			}
		}


		vector<LPGAMEOBJECT>* enemys = EnemySpawn::getInstance()->getEnemlist();
		for (UINT i = 0; i < enemys->size(); i++) {
			if (enemys->at(i)->state != OBJ_DIE) {
				float l, t, r, b;
				enemys->at(i)->GetBoundingBox(l, t, r, b);

				if (wl < r &&
					wr > l  &&
					wt < b &&
					wb > t) {
					if (effted) {
						effted = false;
						Enemy* enemy = dynamic_cast<Enemy *>(enemys->at(i));
						DebugOut(L"enemy hp %d \n", enemy->Hp);
						if (enemy->minusHp(damage)) {
							enemys->at(i)->SetState(OBJ_DIE);
							PlayerStatus::getInstance()->increaseScore(100);
						}
						Effect::getInstance()->setHitEffect(true);
						Effect::getInstance()->setHitEffectPos(enemys->at(i)->x + 3, enemys->at(i)->y + 5);
						weapon->SetState(-1);

						//	ItemSpaw::getInstance()->CreateObj(coObjects->at(i)->x, coObjects->at(i)->y-20);
					}
				}
				
			}
		}
		delaytimer += dt;
		if (delaytimer > 250) {
			if (delaytimer < 280) {
				weapon->SetPosition(tempoX, tempoY);
			}
			weapon->Update(dt, coObjects);
		}

	}
	
}

void SubWeapon::Render()
{
	if (weapon_type != SUB_WEAPON_NON) {
		weapon->Render();
	}
}


SubWeapon::~SubWeapon()
{
}
