#include "Woft.h"
#include "PlayerStatus.h"


Woft::Woft()
{
	this->vx = 0;
	this->vy = 0;
	this->Hp =1;
	start = false;
	collision_able = false;
	isJumped = false;
	dir = -1;
	state = WOFT_STATE_RUN;
}

void Woft::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WOFT_BBOX_WIDTH;
	bottom = y + WOFT_BBOX_HEIGHT;
}

void Woft::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {

		if (abs(player->x - this->x) < 95 && !start) {
			start = true;
			state = WOFT_STATE_RUN;
			if (player->x < this->x) {
				dir = -1;
			}
			else {
				dir = 1;
			}
		}
		if (start) {
			int ran = rand() % 10 + 1;
			if (abs(player->x - this->x) > 95 + ran) {
				isJumped = false;
				if (player->x < this->x) {
					dir = -1;
				}
				else {
					dir = 1;
				}
			}
			if (dir == -1) {
				this->vx = -WOFT_SPEED;
			}
			else {
				this->vx = WOFT_SPEED;
			}

			if ((abs(player->x - this->x) < 60) && !isJumped) {
				vy = -WOFT_JUMP_SPEED;
				state = WOFT_STATE_JUMP;
				isJumped = true;
			}

		}


		// Calculate dx, dy 
		CGameObject::Update(dt);
		// Simple fall down
		vy += WOFT_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != OBJ_DIE)
			CalcPotentialCollisions(coObjects, coEvents);



		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			state = WOFT_STATE_RUN;

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;


		}
		//DebugOut(L"dis %f vx %f state %d  \n", abs(player->x - this->x), vx,state);

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}

void Woft::Render()
{
	int ani = 0;
	if (state==WOFT_STATE_IDLE) {
		
			if (nx > 0)
				ani = WOFT_ANI_IDLE_RIGHT;
			else ani = WOFT_ANI_IDLE_LEFT;
	
	}
	if (state == WOFT_STATE_RUN) {
		if (vx == 0)
		{
			if (nx > 0)
				ani = WOFT_ANI_RUN_RIGHT;
			else ani = WOFT_ANI_RUN_LEFT;
		}
		else if (vx > 0)
			ani = WOFT_ANI_RUN_RIGHT;
		else ani = WOFT_ANI_RUN_LEFT;
	}
	if (state == WOFT_STATE_JUMP) {
		if (vx == 0)
		{
			if (nx > 0)
				ani = WOFT_ANI_JUMP_RIGHT;
			else ani = WOFT_ANI_JUMP_LEFT;
		}
		else if (vx > 0)
			ani = WOFT_ANI_JUMP_RIGHT;
		else ani = WOFT_ANI_JUMP_LEFT;
	}
	animation_set->at(ani)->Render(x, y,255,!PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Woft::clone()
{
	return nullptr;
}


Woft::~Woft()
{
}
