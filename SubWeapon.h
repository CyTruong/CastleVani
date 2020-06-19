#pragma once
#include "GameObject.h"

#define SUB_WEAPON_NON 0
#define SUB_WEAPON_DAGGER 1
#define SUB_WEAPON_HOLY 2
#define SUB_WEAPON_AXE 3
#define SUB_WEAPON_BOMERANG 4
class SubWeapon 
{
private:
	int weapon_type;
	LPGAMEOBJECT weapon;
	bool effted;
public:
	bool isready;
public:
	SubWeapon();
	void GetWeapponX(float &x) { x = weapon->x; }
	void SetWeaponType(int weapon_id);
	void GetWeaponType(int &weapon_id);
	void GetWeapon(LPGAMEOBJECT &weapon);
	void Atk(float x, float y,float dir);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~SubWeapon();
};

