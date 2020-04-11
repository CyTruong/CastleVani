#include "SubWeapon.h"
#include "Dagger.h"


SubWeapon::SubWeapon()
{
	weapon_type = 0;

}

void SubWeapon::SetWeaponType(int weapon_id)
{
	this->weapon_type = weapon_id;
	switch (weapon_id) {
	case SUB_WEAPON_DAGGER: 
		weapon = new Dagger();
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
	if (dir<0) {
		this->weapon->vx = -0.3;
	}
	else
		this->weapon->vx = 0.3;

	if (weapon_type!= SUB_WEAPON_NON) {
		this->weapon->SetPosition(x, y+5);
	}
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (weapon_type != SUB_WEAPON_NON) {
		weapon->Update(dt,coObjects);
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
