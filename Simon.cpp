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
	vy += SIMON_GRAVITY * dt;

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

	if (status == SIMON_STA_ATK) {	
		whip->Update(dt, coObjects);
	}
	subweapon->Update(dt,coObjects);

	if (status == SIMON_STA_STANDUP) {
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
				this->whip->Update();
			}else
			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							//xét dame chết hay ko ở đây
						
								StartUntouchable();
						
						}
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
		DebugOut(L"duck nx %d \n", nx);
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
	CGameObject::SetState(state);

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
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DUCK:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
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

