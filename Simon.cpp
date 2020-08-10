#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"

#include "Goomba.h"
#include "Heart.h"
#include "WhipUpdate.h"
#include "Item.h"
#include "Portal.h"
#include "HolyPicker.h"
#include "AxePicker.h"
#include "DaggerPicker.h"
#include "BoomerangPicker.h"
#include "TimestopPicker.h"
#include "EnemySpawn.h"
#include "FloatingBrick.h"
#include "Heart.h"
#include "HeartMini.h"
#include "BossOrb.h"
#include "MoneyBag.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
		
	// Calculate dx, dy 
	CGameObject::Update(dt);
	jumptimer += dt;
	atkcdtimer += dt;
	// Simple fall down
	if (state != SIMON_STATE_CLIMP) {
		vy += SIMON_GRAVITY * dt;
	}

	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}


	#pragma region Simon duck
	if (state == SIMON_STATE_DUCK && cauthang != NULL) {
		this->state = SIMON_STATE_CLIMP;
	}

	#pragma endregion

	#pragma region Simon climp 

	if (untouchable && state == SIMON_STATE_CLIMP) {
		vx = 0;
		vy = 0;
	}

	// Kiểm tra xem có đi ra  khỏi cầu thang chưa
	if (cauthang != NULL) {
		if (cauthang->type == STAIRS_L2R) { // trái lên phải
			if (state != SIMON_STATE_CLIMP) {
				if (((x > cauthang->x + STAIRS_BBOX_WIDTH) || (x + SIMON_BIG_BBOX_WIDTH < cauthang->x)) && y > cauthang->y) { //ra khỏi chân cầu
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 1\n");
				}

			}
			else
			{	//ra khỏi cầu thang
				if (y + SIMON_BIG_BBOX_HEIGHT < cauthang->y) {
					cauthang = NULL;
					vy = SIMON_GRAVITY*dt;
					vx = 0;
					y = y - 3;
					DebugOut(L"Ra khỏi cầu thang 2\n");
				}
				else
					if (y + SIMON_BIG_BBOX_HEIGHT > cauthang->y + cauthang->height) {
						cauthang = NULL;
						vy = SIMON_GRAVITY*dt;
						vx = 0;
						y = y - 3;
						DebugOut(L"Ra khỏi cầu thang 2\n");
					}
			}
		}
		else
			if (cauthang->type == STAIRS_R2L) {
				if (state != SIMON_STATE_CLIMP) {
					DebugOut(L"Check ra khỏi cầu thang %f %f \n", x + SIMON_BIG_BBOX_WIDTH, cauthang->x + cauthang->width);
					if (((x > (cauthang->x + cauthang->width + STAIRS_BBOX_WIDTH)) || (x + SIMON_BIG_BBOX_WIDTH < (cauthang->x + cauthang->width))) && y < cauthang->y) { //ra khỏi chân cầu
						cauthang = NULL;
						vy = 0;
						DebugOut(L"Ra khỏi cầu thang 11\n");
					}

				}
				else
				{	//ra khỏi cầu thang
					if (y + SIMON_BIG_BBOX_HEIGHT < cauthang->y) {
						cauthang = NULL;
						vy = SIMON_GRAVITY * dt ;
						vx = 0;
						y = y - 3;
						DebugOut(L"Ra khỏi cầu thang 21\n");

					}
					else
						if (y + SIMON_BIG_BBOX_HEIGHT > cauthang->y + cauthang->height) {
							cauthang = NULL;
							y = y - 3;
							vx = 0;
							vy = SIMON_GRAVITY * dt;
							DebugOut(L"Ra khỏi cầu thang 21\n");
						}
				}
			}
	}
	//Kiểm tra xem có ra khỏi  bước đệm ko	
	if (demcauthang != NULL) {
		float l, t, r, b;
		demcauthang->GetBoundingBox(l, t, r, b);
		if (this->x+SIMON_BIG_BBOX_WIDTH < l 
			|| this->x >r 
			|| this->y+SIMON_BIG_BBOX_HEIGHT < t) {
			demcauthang = NULL;
			DebugOut(L"Ra khỏi đệm thang %f %f %f %f %f %f \n", this->x + SIMON_BIG_BBOX_WIDTH,l, this->x,r, this->y + SIMON_BIG_BBOX_HEIGHT,t);
		}
	}
	//Kiểm tra xem có leo hay đi cầu thang dc ko
	if (state == SIMON_STATE_CLIMP && cauthang==NULL && demcauthang == NULL) {
		state = SIMON_STATE_IDLE;
	}
	
	//đi trên đệm
	if (state == SIMON_STATE_CLIMP && cauthang==NULL && demcauthang != NULL) {
		if (demcauthang->GetSimonVertex(this->x, this->y, this->vx, this->vy)) {
			this->cauthang = dynamic_cast<Stairs*>( demcauthang->Stair);

			DebugOut(L"vx vy nx %f %f %d \n", vx, vy, nx);
			this->vx = 0;
			this->vy = 0;
			if (this->cauthang->type == STAIRS_L2R) {
				
			}
			if (this->cauthang->type == STAIRS_R2L) {

			}

			if (vx > 0) {
				this->nx = -1;
			}
			if (vx < 0) {
				this->nx = 1;
			}
		}
		else {
			if (vx < 0) {
				state = SIMON_STATE_WALKING_RIGHT;
			}
			else {
				state = SIMON_STATE_WALKING_LEFT;
			}
		}
		
	}
	else
	//Leo cầu thang
	if (state == SIMON_STATE_CLIMP && cauthang != NULL) {
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		cauthang->SetSimonPos(this->x, this->y, (r - l), (b - t));

		float fx, fy;
		cauthang->GetStaireVector(x,y,vx,vy, fx, fy);
		//DebugOut(L"simon stte %d v %f fx %f fy %f \n", state, this->vy, fx, fy);
		if (fx > 0) {
			this->nx = 1;
		}
		if (fx < 0) {
			this->nx = -1;
		}
		if (whip->isAtk) {
			fx = 0;
			fy = 0;
		}
		/*this->dx = fx * dt;
		this->dy = fy * dt;*/
		dx = vx * dt;
		dy = vy * dt;
	}

	#pragma endregion

	#pragma region Simon atk
	if (status == SIMON_STA_ATK) {
		whip->Update(dt, coObjects);
	}
	subweapon->Update(dt, coObjects);
	float subX = 0;
	subweapon->GetWeapponX(subX);
	LPGAMEOBJECT subwb;
	subweapon->GetWeapon(subwb);
	int subweaponid;
	subweapon->GetWeaponType(subweaponid);
	if (subweaponid!=SUB_WEAPON_NON) {
		if (abs(subX - this->x) >= SCREEN_WIDTH / 2 || subwb->vx == 0) {
			subweapon->isready = true;
		}
	}

#pragma endregion

	#pragma region Simon đứng dậy
	if (status == SIMON_STA_STANDUP && state != SIMON_STATE_CLIMP && isducking) {
		DebugOut(L"Stand up \n");
		y = y - (SIMON_BIG_BBOX_HEIGHT -1*SIMON_SMALL_BBOX_HEIGHT) - 5; //0.8 là giảm số khi đứng dậy ko bị rớt khỏi map 
		status = SIMON_STA_NOR;
		isducking = false;
	}

	#pragma endregion

	#pragma region Simon va chạm obj tĩnh
	if (coEvents.size() == 0)
	{
		onAir = 1;
		x += dx;
		y += dy;
	}
	else
	{
		isJump = 0;
		onAir = 0;
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		// bỏ qua 0 do obj 0 là simon
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];


			if (dynamic_cast<Item *>(e->obj)) {
				e->obj->state = OBJ_DIE;
				if (dynamic_cast<WhipUpdate *>(e->obj)) {
					this->whip->Update();
				}else
				if (dynamic_cast<DaggerPicker*>(e->obj)) {
					this->subweapon->SetWeaponType(SUB_WEAPON_DAGGER);
				}else
				if (dynamic_cast<HolyPicker *>(e->obj)) {
					this->subweapon->SetWeaponType(SUB_WEAPON_HOLY);
				}else
				if (dynamic_cast<AxePicker *>(e->obj)) {
					this->subweapon->SetWeaponType(SUB_WEAPON_AXE);
				}else
				if (dynamic_cast<BoomerangPicker*>(e->obj)) {
					this->subweapon->SetWeaponType(SUB_WEAPON_BOMERANG);
				}else
				if (dynamic_cast<TimestopPicker*>(e->obj)) {
					this->subweapon->SetWeaponType(SUB_WEAPON_THEWORD);
				}
				else
				if (dynamic_cast<Heart*>(e->obj)) {
					PlayerStatus::getInstance()->IncreaseMana(10);
				}
				else
				if (dynamic_cast<HeartMini*>(e->obj)) {
					PlayerStatus::getInstance()->IncreaseMana(1);
				}
				else
				if (dynamic_cast<BossOrb*>(e->obj)) {
					PlayerStatus::getInstance()->increaseScore(1000);
				}
				if (dynamic_cast<MoneyBag*>(e->obj)) {
					PlayerStatus::getInstance()->increaseScore(300);
				}
				this->y = this->y - 0.1f;
			}
			else
				if (dynamic_cast<FloatingBrick*>(e->obj)) {
					if (abs(this->vx) < abs(e->obj->vx)) {
						this->x += e->obj->dx * 2.5; //x2 bec uda 2times
					}

				}
			else
				if (dynamic_cast<Stairs *>(e->obj)) 
				{
					Stairs* stairs = dynamic_cast<Stairs*>(e->obj);
					DebugOut(L"Tren cau thang \n");

					if (stairs->type == STAIRS_L2R) {
						if (this->y > stairs->y && e->nx < 0) {
							DebugOut(L"Duung huong \n");
							this->cauthang = stairs;
						}
						if (this->y < stairs->y && e->nx > 0) {
							DebugOut(L"Duung huong \n");
							this->cauthang = stairs;
						}
					}
					if (stairs->type == STAIRS_R2L) {
						if (this->y > stairs->y && e->nx > 0) {
							DebugOut(L"Duung huong \n");
							this->cauthang = stairs;
						}
						if (this->y < stairs->y && e->ny < 0) {
							DebugOut(L"Duung huong \n");
							this->cauthang = stairs;
						}
					}
				}
				
				if (dynamic_cast<StairStep *>(e->obj)) {
					DebugOut(L"Ok đệm thang \n");
					if(cauthang==NULL)
						demcauthang = dynamic_cast<StairStep *>(e->obj);
				}
							 
				if (dynamic_cast<CPortal *>(e->obj))
				{
					CPortal *p = dynamic_cast<CPortal *>(e->obj);
					DebugOut(L"[INFO] Switching to scene %d", p->GetSceneId());
					PlayerStatus::getInstance()->SetStateIndex(p->GetSceneId());
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
		}
	}
#pragma endregion
	
	#pragma region Va chạm enemy
	if (untouchable == 0) {
		float wl, wt, wr, wb;
		this->GetBoundingBox(wl, wt, wr, wb);
		vector<LPGAMEOBJECT>* enemy = EnemySpawn::getInstance()->getEnemlist();
		for (UINT i = 0; i < enemy->size(); i++) {
			if (enemy->at(i)->state != OBJ_DIE) {
				float l, t, r, b;
				enemy->at(i)->GetBoundingBox(l, t, r, b);
				if (CheckCollisionWith(l,t,r,b)) {
					StartUntouchable();
					vy = -SIMON_JUMP_SPEED_Y * 2 / 3;
					PlayerStatus::getInstance()->SubHp(1);
					if (dynamic_cast<dRaven* >(enemy->at(i))) {
						enemy->at(i)->SetState(OBJ_DIE);
						Effect::getInstance()->setDesEffect(true);
						Effect::getInstance()->setDesEffect(enemy->at(i)->x + 5, enemy->at(i)->y + 5);
					}
				}		
			}
		}
	}
#pragma endregion

	#pragma region Zero Hp
	int hp = 0;
	PlayerStatus::getInstance()->getPlayerHp(hp);
	if (hp==0) {
		SetState(SIMON_STATE_DIE);
	}
	#pragma endregion

	// No collision occured, proceed normally
	//DebugOut(L"Simon jump %d \n", isJump);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::atk() {
	DebugOut(L"atk x %f y %f \n",x,y);
	if (atkcdtimer> 800) {
		SetStatus(SIMON_STA_ATK);
		atkcdtimer = 0;
		if (!whip->isAtk) {

			if (vx == 0) {
				if (nx > 0) {
					whip->atk(WHIP_DIR_RIGHT);
				}
				else
				{
					whip->atk(WHIP_DIR_LEFT);
				}
			}
			else {
				if (vx > 0) {
					whip->atk(WHIP_DIR_RIGHT);
				}
				else
				{
					whip->atk(WHIP_DIR_LEFT);
				}
			}
			/*whip->atk(WHIP_DIR_LEFT);*/
			if (!isJump) {
				vx = 0;
			}
		}

	}
}

void CSimon::subatk()
{
	SetStatus(SIMON_STA_ATK);
	int id = 0;
	subweapon->GetWeaponType(id);
	if (id!=SUB_WEAPON_NON) {
		if (vx == 0) {
			if (nx > 0) {
				subweapon->Atk(this->x, this->y, 1);
			}
			else
			{
				subweapon->Atk(this->x, this->y, -1);
			}
		}
		else {
			if (vx > 0) {
				subweapon->Atk(this->x, this->y, 1);
			}
			else
			{
				subweapon->Atk(this->x, this->y, -1);
			}
		}
	}	
	else
	{
		atk();
	}
}

void CSimon::Render()
{
	int ani = -1;
	if (state == SIMON_STATE_DIE)
	{
		if (vx <= 0 ) {
			ani = SIMON_ANI_DIE_LEFT;
		}
		else {
			ani = SIMON_ANI_DIE_RIGHT;
		}
	}
	else
	if ((abs(vy)>0.1 && onAir ==1)||isJump==1) {
		if (status == SIMON_STA_ATK) {
			if (vx == 0)
			{
				if (nx > 0)
					ani = SIMON_ANI_WHIP_SUB_RIGHT;
				else ani = SIMON_ANI_WHIP_SUB_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_WHIP_SUB_RIGHT;
			else ani = SIMON_ANI_WHIP_SUB_LEFT;
		}else
		if (vx == 0)
		{
			if (nx > 0)
				ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_JUMP_LEFT;
		}
		else if (vx < 0)
			ani = SIMON_ANI_JUMP_LEFT;
			else ani = SIMON_ANI_JUMP_RIGHT;


	}else
	if (state == SIMON_STATE_DUCK) {	
			isducking = true;

			if (nx > 0)
				ani = SIMON_ANI_DUCK_RIGHT;
			else ani = SIMON_ANI_DUCK_LEFT;

			if (status == SIMON_STA_ATK) {
				if (vx == 0)
				{
					if (nx > 0)
						ani = SIMON_ANI_DOWN_WHIP_SUB_RIGHT;
					else ani = SIMON_ANI_DOWN_WHIP_SUB_LEFT;
				}
				else if (vx > 0)
					ani = SIMON_ANI_DOWN_WHIP_SUB_RIGHT;
				else ani = SIMON_ANI_DOWN_WHIP_SUB_LEFT;
			}
	}
	else
	{
		if (status == SIMON_STA_NOR)
		{
			if (vx == 0)
			{
				if (nx > 0)
					ani = SIMON_ANI_IDLE_RIGHT;
				else ani = SIMON_ANI_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_WALKING_RIGHT;
			else ani = SIMON_ANI_WALKING_LEFT;
			/*	if (onAir && vy !=0) {
					if (nx > 0) {
						ani = SIMON_ANI_JUMP_RIGHT;
					}
					else
						ani = SIMON_ANI_JUMP_LEFT;
				}*/
		}
		if (status == SIMON_STA_ATK) {
			if (vx == 0)
			{
				if (nx > 0)
					ani = SIMON_ANI_WHIP_SUB_RIGHT;
				else ani = SIMON_ANI_WHIP_SUB_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_WHIP_SUB_RIGHT;
			else ani = SIMON_ANI_WHIP_SUB_LEFT;
		}
	}
	 
	if (state == SIMON_STATE_CLIMP) {
		if (vy < 0) {
			if (vx == 0)
			{
				if (nx > 0)
					ani = SIMON_ANI_CLIMB_UP_RIGHT;
				else ani = SIMON_ANI_CLIMB_UP_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_CLIMB_UP_RIGHT;
			else ani = SIMON_ANI_CLIMB_UP_LEFT;
		}
		else {
			if (vy > 0) {
				if (vx == 0)
				{
					if (nx > 0)
						ani = SIMON_ANI_CLIMB_DOWN_RIGHT;
					else ani = SIMON_ANI_CLIMB_DOWN_LEFT;
				}
				else if (vx > 0)
					ani = SIMON_ANI_CLIMB_DOWN_RIGHT;
				else ani = SIMON_ANI_CLIMB_DOWN_LEFT;
			}
			else
			{
				if (nx > 0)
					ani = SIMON_ANI_CLIMP_STAND_RIGHT;
				else ani = SIMON_ANI_CLIMP_STAND_LEFT;
			}
			
		}
		if (status == SIMON_STA_ATK) {
			
			switch (ani)
			{
			 case SIMON_ANI_CLIMB_UP_RIGHT :
				ani = SIMON_ANI_WHIP_CLIMPUP_RIGHT;
			
				break;
			 case SIMON_ANI_CLIMB_UP_LEFT :
				 ani = SIMON_ANI_WHIP_CLIMPUP_LEFT;
				 break;
			 case SIMON_ANI_CLIMB_DOWN_LEFT:
				 ani = SIMON_ANI_WHIP_CLIMPDOWN_LEFT;
				 break;
			 case SIMON_ANI_CLIMB_DOWN_RIGHT:
				 ani = SIMON_ANI_WHIP_CLIMPDOWN_RIGHT;
				 break;
			 case SIMON_ANI_CLIMP_STAND_RIGHT:
				 if (cauthang->type == STAIRS_L2R) {
					 ani = SIMON_ANI_WHIP_CLIMPUP_RIGHT;
				 }
				 if (cauthang->type == STAIRS_R2L) {
					 ani = SIMON_ANI_WHIP_CLIMPDOWN_RIGHT;
				 }
				 break;
			 case SIMON_ANI_CLIMP_STAND_LEFT :
				 if (cauthang->type == STAIRS_L2R) {
					 ani = SIMON_ANI_WHIP_CLIMPDOWN_LEFT;
				 }
				 if (cauthang->type == STAIRS_R2L) {
					 ani = SIMON_ANI_WHIP_CLIMPUP_LEFT;
				 }
				 break;
			default:
				
				break;
			}
		}
	}
	
	int alpha = 255;
	if (untouchable && state!=SIMON_STATE_DIE) {
		if (vx == 0)
		{
			if (nx > 0)
				ani = SIMON_ANI_DAMAGED_RIGHT;
			else ani = SIMON_ANI_DAMAGED_LEFT;
		}
		else if (vx > 0)
			ani = SIMON_ANI_DAMAGED_RIGHT;
		else ani = SIMON_ANI_DAMAGED_LEFT;
	}

	whip->x = x;
	whip->y = y;

	whip->Render();
	subweapon->Render();
	bool islastF = false;
	if (untouchable==1 && (GetTickCount() - untouchable_start)%2 == 0) {
		//Ko render
	}
	else {
		if (ani==-1) {
			state = SIMON_STATE_IDLE;
			status = SIMON_STA_NOR;
			vx = 0;
			vy = 0;
			ani = SIMON_ANI_IDLE_LEFT;
		}
		islastF = animation_set->at(ani)->Render(x, y, alpha);

	}

	if (islastF && status == SIMON_STA_ATK) {
		status = SIMON_STA_NOR;
	}
	if (islastF && state == SIMON_STATE_DIE) {

		int state = 0;
		int life = 0;
		PlayerStatus::getInstance()->getStateIndex(state);
		PlayerStatus::getInstance()->getPlayerLife(life);
		if (life!=0) {

			PlayerStatus::getInstance()->Reset();
			CGame::GetInstance()->SwitchScene(state);
		}
		else {
			CGame::GetInstance()->SwitchScene(10);

		}
	}
	  
	/*RenderBoundingBox();*/
}

void CSimon::SetState(int state)
{
	if (!untouchable) {
		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			if (this->state == SIMON_STATE_DUCK) {
				state = SIMON_STATE_DUCK;
				break;
			}
			if (this->state == SIMON_STATE_CLIMP) {
				state = SIMON_STATE_CLIMP;
				if (this->cauthang != NULL) {
					if (cauthang->type == STAIRS_R2L) {
						vy = 0.02f;
					}
					if (cauthang->type == STAIRS_L2R) {
						vy = -0.02f;
					}
				}
				break;
			}
			if (!whip->isAtk) {
				vx = SIMON_WALKING_SPEED;
				nx = 1;
			}

			break;
		case SIMON_STATE_WALKING_LEFT:
			if (this->state == SIMON_STATE_DUCK) {
				state = SIMON_STATE_DUCK;
				break;
			}
			if (this->state == SIMON_STATE_CLIMP) {
				state = SIMON_STATE_CLIMP;
				if (this->cauthang != NULL) {
					if (cauthang->type == STAIRS_L2R) {
						vy = 0.02f;
					}
					if (cauthang->type == STAIRS_R2L) {
						vy = -0.02f;
					}
				}
			}
			if (!whip->isAtk) {
				vx = -SIMON_WALKING_SPEED;
				nx = -1;
			}

			break;
		case SIMON_STATE_JUMP:
		{
			if (isJump == 0 && jumptimer > 500) {
				jumptimer = 0;
				vy = -SIMON_JUMP_SPEED_Y;
				isJump = 1;
				break;
			}
			else
				break;
		}

		case SIMON_STATE_CLIMP:
			//nếu có cầu thang
			if (!isJump) {
				if (this->cauthang != NULL) {
					vy = -0.02f;
				}
				else {
					//state = SIMON_STATE_IDLE;

				}
			}
			else
				state = SIMON_STATE_JUMP;
			break;
		case SIMON_STATE_IDLE:
			if (this->state == SIMON_STATE_CLIMP && this->cauthang != NULL) {
				this->vx = 0;
				this->vy = 0;
				state = SIMON_STATE_CLIMP;
			}
			vx = 0;
			break;
		case SIMON_STATE_DUCK:
			//vy = 0.02f;
			break;
		case SIMON_STATE_DIE:
			vy = 0;
			vx = 0;
			break;
		}
		CGameObject::SetState(state);

	}
	else {
		
	}

}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	
	if (state==SIMON_STATE_DUCK) {
		right = x + SIMON_SMALL_BBOX_WIDTH;
		bottom = y + SIMON_SMALL_BBOX_HEIGHT;
	}
	//if (status == SIMON_STA_ATK) {
	//	right = x + SIMON_BIG_ATK_BBOX_WIDTH;
	//	bottom = y + SIMON_BIG_ATK_BBOX_HEIGHT;
	//}
	else {
	
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
	
}

