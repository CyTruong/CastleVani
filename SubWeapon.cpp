#include "SubWeapon.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "Axe.h"
#include "Boomerang.h"
#include "EnemySpawn.h"	
#include "PlayerStatus.h"
SubWeapon::SubWeapon()
{
	PlayerStatus::getInstance()->getSubWeaponIndex(weapon_type);
	isready = true;
	damage = 0;
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
	default:
		break;
	}
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
	
	if (weapon_type!= SUB_WEAPON_NON && isready) {
		isready = false;
		this->effted = true;
		this->weapon->SetPosition(x, y+5);
		int mana = 0;
		PlayerStatus::getInstance()->SubMana(1);
		//Nếu ít mana ko cho play
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
				this->weapon->vx = -0.15;
			}
			else
				this->weapon->vx = 0.15;
			this->weapon->vy = -0.16f;
		}
		if (weapon_type == SUB_WEAPON_BOMERANG) {
			if (dir < 0) {
				this->weapon->vx = -0.3;
			}
			else
				this->weapon->vx = 0.3;
		}
	}
	
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (weapon_type != SUB_WEAPON_NON) {
		weapon->Update(dt,coObjects);
		float wl, wt, wr, wb;
		this->weapon->GetBoundingBox(wl, wt, wr, wb);
		vector<LPGAMEOBJECT>* enemys = EnemySpawn::getInstance()->getEnemlist();
		for (UINT i = 0; i < enemys->size(); i++) {
			if (enemys->at(i)->state != OBJ_DIE) {
				float l, t, r, b;
				enemys->at(i)->GetBoundingBox(l, t, r, b);
				if (l > wl && l < wr) {
					if (!(b < wt || t > wb)) {
						if (effted) {
							effted = false;
							Enemy* enemy = dynamic_cast<Enemy *>(enemys->at(i));
							DebugOut(L"enemy hp %d \n", enemy->Hp);
							if (enemy->minusHp(damage)) {
								enemys->at(i)->SetState(OBJ_DIE);

							}
							weapon->SetState(-1);

							//	ItemSpaw::getInstance()->CreateObj(coObjects->at(i)->x, coObjects->at(i)->y-20);
						}

					}
				}
			}
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
