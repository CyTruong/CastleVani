#include "Whip.h"
#include "debug.h"
#include "Textures.h"
#include "Grid.h"
#include "Heart.h"
#include "ItemSpaw.h"
#include "EnemySpawn.h"
#include "PlayerStatus.h"
#include "Effect.h"
Whip::Whip()
{

	aniCount = 0;
	isAtk = false;
	level = 0;
	PlayerStatus::getInstance()->getWhipsLevel(level);
}

void Whip::getWhipLv(int &lv) {
	lv = this->whipLv;
}

void Whip::Update()
{
	if (level < WHIP_LEVEL_MAX) {
		level++;
	}
	PlayerStatus::getInstance()->SetWhipsLevel(level);

}

void Whip::setWhipLv(int lv) {
	PlayerStatus::getInstance()->SetWhipsLevel(lv);
	this->whipLv = lv;
}

void Whip::atk(int dir) {
		lastFrameTime = GetTickCount();
		aniCount = 0;
		isAtk = true;
		this->dir = dir;
		effted = true;
}

void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	//Độ dài roi
	int BBoxWidth = WHIP_BBOX_WIDTH_NONE;
	if (aniCount >=2) {
		 BBoxWidth = level > WHIP_LEVEL_0 ? WHIP_BBOX_WIDTH_LONG : WHIP_BBOX_WIDTH_SHORT;
	}
	if (this->dir == WHIP_DIR_LEFT) {
		left = x - BBoxWidth + EXTRA_MOD_SIMONWIDTH -5;
		top = y+ EXTRA_MOD_SIMONHEIGHT;
		right = x + EXTRA_MOD_SIMONWIDTH;
		bottom = y + WHIP_BBOX_HEIGHT + EXTRA_MOD_SIMONHEIGHT;
	}
	else {
		left = x;
		top = y + EXTRA_MOD_SIMONHEIGHT;
		right = x + BBoxWidth;
		bottom = y + WHIP_BBOX_HEIGHT + EXTRA_MOD_SIMONHEIGHT;

	}
	/*if (aniCount >= 2) {
		DebugOut(L"Box l %f t %f r %f b %f \n", left,top,right,bottom);
	}*/
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	if (isAtk) {
		CGameObject::Update(dt, coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		CalcPotentialCollisions(coObjects, coEvents);
		float wl, wt, wr, wb;
		this->GetBoundingBox(wl,wt,wr,wb);

		//DebugOut(L"ani count %d \n",aniCount);
		if(aniCount >=1 )
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->atk_able && coObjects->at(i)->state!=OBJ_DIE) {
				float l, t, r, b;
				coObjects->at(i)->GetBoundingBox(l, t, r, b);

				//if ((wl < r && wr > l && wt < b && wb > t)|| //va chạm bên
				//		(wl < l && wr > r &&   wt > t && wb > b )||
				//			(wl < l && wr > r &&   wt < t && wb < b)
				//	) { 
				//	
				//}
				if (CheckCollisionWith(l, t, r, b)) {
					Effect::getInstance()->setHitEffect(true);
					Effect::getInstance()->setHitEffectPos(coObjects->at(i)->x + 3, coObjects->at(i)->y + 5);
					coObjects->at(i)->SetState(OBJ_DIE);
					ItemSpaw::getInstance()->CreateObj(coObjects->at(i)->x, coObjects->at(i)->y, coObjects->at(i)->dropItem);

					Effect::getInstance()->setDesEffect(true);
					Effect::getInstance()->setDesEffect(l + 3, t + 5);
				}
				
			}	
		}
		//enemy
		vector<LPGAMEOBJECT>* enemys = EnemySpawn::getInstance()->getEnemlist();
		for (UINT i = 0; i < enemys->size();i++) {
			if (enemys->at(i)->state!=OBJ_DIE) {
				float l, t, r, b;
				enemys->at(i)->GetBoundingBox(l, t, r, b);
				if (CheckCollisionWith(l, t, r, b)) {
					if (effted) {
						effted = false;
						Enemy* enemy = dynamic_cast<Enemy *>(enemys->at(i));
						DebugOut(L"enemy hp %d \n", enemy->Hp);
						if (enemy->minusHp(1)) {
							enemys->at(i)->SetState(OBJ_DIE);
							PlayerStatus::getInstance()->increaseScore(100);
							Effect::getInstance()->setDesEffect(true);
							Effect::getInstance()->setDesEffect(l + 3, t + 5);
						}
						Effect::getInstance()->setHitEffect(true);
						Effect::getInstance()->setHitEffectPos(enemys->at(i)->x + 3, enemys->at(i)->y + 5);
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
		DWORD now = GetTickCount();		
		
		DWORD t = 125;
		if (aniCount == 2) {
			t = 200;
		}
		if (now - lastFrameTime > t)
		{
			aniCount++;
			lastFrameTime = now;
			
			if (aniCount == 3) {
				
				aniCount = 0;
				isAtk = false;
				return;
			}
			else {

			}
		}
		RenderBoundingBox();
	}
}

Whip::~Whip()
{
}
