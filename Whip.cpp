#include "Whip.h"
#include "debug.h"
#include "Textures.h"
#include "Grid.h"
#include "Heart.h"
#include "ItemSpaw.h"
Whip::Whip()
{

	aniCount = 0;
	isAtk = false;
	level = 0;
}

void Whip::getWhipLv(int &lv) {
	lv = this->whipLv;
}

void Whip::Update()
{
	if (level < WHIP_LEVEL_MAX) {
		level++;
	}
}

void Whip::setWhipLv(int lv) {
	this->whipLv = lv;
}

void Whip::atk(int dir) {
		lastFrameTime = GetTickCount();
		aniCount = 0;
		isAtk = true;
		this->dir = dir;
}

void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	int BBoxWidth = level > WHIP_LEVEL_0 ? WHIP_BBOX_WIDTH_LONG : WHIP_BBOX_WIDTH_SHORT;
	if (this->dir == WHIP_DIR_LEFT) {
		left = x - BBoxWidth;
		top = y;
		right = x;
		bottom = y + WHIP_BBOX_HEIGHT;
	}
	else {
		left = x;
		top = y;
		right = x + BBoxWidth;
		bottom = y + WHIP_BBOX_HEIGHT;

	}

}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	if (isAtk) {
		CGameObject::Update(dt, coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		CalcPotentialCollisions(coObjects, coEvents);
		float wl, wt, wr, wb;
		this->GetBoundingBox(wl,wt,wr,wb);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->atk_able && coObjects->at(i)->state!=OBJ_DIE) {
				float l, t, r, b;
				coObjects->at(i)->GetBoundingBox(l, t, r, b);
				if (l > wl && l < wr) {
					if (!(b < wt || t > wb)) {
						coObjects->at(i)->SetState(OBJ_DIE);
						ItemSpaw::getInstance()->CreateObj(coObjects->at(i)->x, coObjects->at(i)->y);
					}
				}
			}
			
		
		}

	}
}

void Whip::Render() {
	if (isAtk) {
		CSprites * sprites = CSprites::GetInstance();
		//if left			srprite bắt đầu| level (100) | trái| +1 nữa ra phải 
		int spriteIndex = SPRITE_ID_START + 100*level+  1 + dir;

		spriteIndex += 10 * aniCount;
		sprites->Get(spriteIndex)->Draw(x, y);
		//RenderBoundingBox();
		//DebugOut(L"draw whips ani %d \n", spriteIndex);
		DWORD now = GetTickCount();		
		DWORD t = 80;
		if (now - lastFrameTime > t)
		{
			aniCount++;
			lastFrameTime = now;
			
			if (aniCount == 3) {
				aniCount = 0;
				isAtk = false;
				return;
			}
		}
		
	}
}

Whip::~Whip()
{
}
