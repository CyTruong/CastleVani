#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
//26 13
#define SPRITE_ID_START 41000

#define WHIP_BBOX_WIDTH_SHORT 30
#define WHIP_BBOX_HEIGHT 8
#define WHIP_BBOX_WIDTH_LONG 45

#define WHIP_LEVEL_0 0
#define WHIP_LEVEL_1 1
#define WHIP_LEVEL_MAX 1

#define WHIP_ANI_0_LEFT 0
#define WHIP_ANI_0_RIGHT 1
#define WHIP_ANI_1_LEFT 2
#define WHIP_ANI_1_RIGHT 3

#define WHIP_DIR_LEFT 0
#define WHIP_DIR_RIGHT 1	

class Whip : public CGameObject
{
private:
	int whipLv;
	int aniCount;
	DWORD lastFrameTime;
	bool isAtk;
	int Direction;
	int dir;
	int level;
public:
	Whip();
	void atk(int dir);
	void setWhipLv(int lv);
	void getWhipLv(int &lv);
	void Update();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~Whip();
};

