#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Stairs.h"
#include "PlayerStatus.h"
#include "StairStep.h"

#define SIMON_WALKING_SPEED		0.05f  //0.05

#define SIMON_JUMP_SPEED_Y		/*0.27*/ 0.22
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			/*0.0013f*/ 0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_DUCK			500
#define SIMON_STATE_CLIMP		600
#define SIMON_STATE_CLIMPDOWN		700

#define SIMON_ANI_IDLE_LEFT		0
#define SIMON_ANI_IDLE_RIGHT			1
#define SIMON_ANI_WALKING_LEFT			2
#define SIMON_ANI_WALKING_RIGHT			3
#define SIMON_ANI_DUCK_LEFT		4	
#define SIMON_ANI_DUCK_RIGHT	5
#define SIMON_ANI_JUMP_LEFT			6
#define SIMON_ANI_JUMP_RIGHT		7	
#define SIMON_ANI_DAMAGED_LEFT		8
#define SIMON_ANI_DAMAGED_RIGHT		9
#define SIMON_ANI_CLIMB_UP_LEFT 10
#define SIMON_ANI_CLIMB_UP_RIGHT 11
#define SIMON_ANI_CLIMB_DOWN_LEFT 12
#define SIMON_ANI_CLIMB_DOWN_RIGHT 13
#define SIMON_ANI_WHIP_SUB_LEFT 14
#define SIMON_ANI_WHIP_SUB_RIGHT 15
#define SIMON_ANI_DOWN_WHIP_SUB_LEFT 16
#define SIMON_ANI_DOWN_WHIP_SUB_RIGHT 17
#define SIMON_ANI_CLIMP_STAND_LEFT 18
#define SIMON_ANI_CLIMP_STAND_RIGHT 19
#define SIMON_ANI_DIE_LEFT 20
#define SIMON_ANI_DIE_RIGHT 21
#define SIMON_ANI_WHIP_CLIMPUP_LEFT 22
#define SIMON_ANI_WHIP_CLIMPUP_RIGHT 23
#define SIMON_ANI_WHIP_CLIMPDOWN_LEFT 24
#define SIMON_ANI_WHIP_CLIMPDOWN_RIGHT 25

#define	SIMON_STA_NOR	1
#define SIMON_STA_ATK   2
#define SIMON_STA_STANDUP 3

#define SIMON_BIG_BBOX_WIDTH  14
#define SIMON_BIG_BBOX_HEIGHT 30

#define SIMON_BIG_ATK_BBOX_WIDTH  45
#define SIMON_BIG_ATK_BBOX_HEIGHT 30

#define SIMON_SMALL_BBOX_WIDTH  16
#define SIMON_SMALL_BBOX_HEIGHT 23

#define SIMON_UNTOUCHABLE_TIME 1000


class CSimon : public CGameObject
{
	int status;
	int untouchable;
	DWORD untouchable_start;
	int onAir;
	int isJump;
	Whip* whip;
	SubWeapon* subweapon;
	StairStep* demcauthang;
	bool isCauthang;
	bool isducking;
	long jumptimer;
	long atkcdtimer;
public:
	Stairs* cauthang;
public:
	CSimon() : CGameObject()
	{
		status = SIMON_STA_NOR;
		onAir = 0;
		isJump = 0;
		jumptimer = 0;
		cauthang = NULL;
		untouchable = 0;
		isCauthang = false;
		whip = new Whip();
		atk_able = false;
		subweapon = new SubWeapon();
		int subwptype;
		isducking = false;
		PlayerStatus::getInstance()->getSubWeaponIndex(subwptype);
		subweapon->SetWeaponType(subwptype);
		atkcdtimer = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetStatus(int l) { status = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void atk();
	void setSubweapon(int weapon) { subweapon->SetWeaponType(weapon); };
	void getSubweapon(int &sub) { subweapon->GetWeaponType(sub); };
	void subatk();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};