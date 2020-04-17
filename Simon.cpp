#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"

#include "Goomba.h"
#include "Heart.h"
#include "WhipUpdate.h"
#include "Item.h"
#include "Portal.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
		
	// Calculate dx, dy 
	CGameObject::Update(dt);

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


	if (state == SIMON_STATE_DUCK && cauthang != NULL) {
		this->state = SIMON_STATE_CLIMP;
	}



	if (cauthang != NULL) {
		if (cauthang->type == STAIRS_L2R) { // trái lên phải
			if (state != SIMON_STATE_CLIMP) {  
				if (((x > cauthang->x + STAIRS_BBOX_WIDTH  ) || (x+ SIMON_BIG_BBOX_WIDTH < cauthang->x))  && y > cauthang->y  ) { //ra khỏi chân cầu
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 1\n");
				}
				 
			}
			else
			{	//ra khỏi cầu thang
				if (y + SIMON_BIG_BBOX_HEIGHT < cauthang->y ) {
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 2\n");

				}else
				if (y+ SIMON_BIG_BBOX_HEIGHT > cauthang->y + cauthang->height) {
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 2\n");
				}
			}
		}else
		if (cauthang->type == STAIRS_R2L) {
			if (state != SIMON_STATE_CLIMP) {
				if (((x > (cauthang->x + cauthang->width+STAIRS_BBOX_WIDTH) ) || (x+ SIMON_BIG_BBOX_WIDTH  < (cauthang->x + cauthang->width))) && y > cauthang->y) { //ra khỏi chân cầu
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 11\n");
				}

			}
			else
			{	//ra khỏi cầu thang
				if (y + SIMON_BIG_BBOX_HEIGHT < cauthang->y) {
					cauthang = NULL;
					vy = 0;
					DebugOut(L"Ra khỏi cầu thang 21\n");

				}
				else
					if (y + SIMON_BIG_BBOX_HEIGHT > cauthang->y + cauthang->height) {
						cauthang = NULL;
						vy = 0;
						DebugOut(L"Ra khỏi cầu thang 21\n");
					}
			}
		}
	}
	if (state == SIMON_STATE_CLIMP && cauthang!=NULL) {

		float fx, fy;
		cauthang->GetStaireVector(vy, fx, fy);
		DebugOut(L"simon stte %d v %f fx %f fy %f \n", state, this->vy,fx,fy);

		this->dx = fx*dt;
		this->dy = fy*dt;
	}


	if (status == SIMON_STA_ATK) {	
		whip->Update(dt, coObjects);
	}
	subweapon->Update(dt,coObjects);

	if (status == SIMON_STA_STANDUP && state!=SIMON_STATE_CLIMP) {
		DebugOut(L"Stand up \n");
		y = y - (SIMON_BIG_BBOX_HEIGHT - 0.8*SIMON_SMALL_BBOX_HEIGHT) -10; //0.8 là giảm số khi đứng dậy ko bị rớt khỏi map 
		status = SIMON_STA_NOR;
	}

	// No collision occured, proceed normally
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
				}
			}else
			if (dynamic_cast<Stairs *>(e->obj)) // if e->obj is Goomba 
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
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				DebugOut(L"[INFO] Switching to scene %d", p->GetSceneId());
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::atk() {
	if (vx==0) {
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
}

void CSimon::subatk()
{
	if (vx == 0) {
		if (nx > 0) {
			subweapon->Atk(this->x, this->y, 1);
		}
		else
		{
			subweapon->Atk(this->x, this->y,-1);
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

void CSimon::Render()
{
	int ani;
	if (state == SIMON_STATE_DIE)
		ani =	SIMON_ANI_DIE;
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
				ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
		}
			
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
	
	int alpha = 255;
	if (untouchable) alpha = 128;
	whip->x = x;
	whip->y = y;

	whip->Render();
	subweapon->Render();
	bool islastF = animation_set->at(ani)->Render(x, y, alpha);
	if (islastF && status == SIMON_STA_ATK) {
		status = SIMON_STA_NOR;
	}
	  
	/*RenderBoundingBox();*/
}

void CSimon::SetState(int state)
{

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		isJump = 1;
		break;
	case SIMON_STATE_CLIMP:
		if (this->cauthang != NULL) {
			vy = -0.02f;
		}		
		break;
	case SIMON_STATE_IDLE:
		if (this->state== SIMON_STATE_CLIMP) {
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
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
	CGameObject::SetState(state);

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

