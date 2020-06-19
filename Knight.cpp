#include "Knight.h"



Knight::Knight()
{
	this->vx = 0;
	this->vy = 0;
	start = false;
	collision_able = false;
	dir = -1;
	Hp = 4;
	state = KNIGHT_STATE_IDLE;
}

void Knight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + KNIGHT_BBOX_WIDTH;
	bottom = y + KNIGHT_BBOX_HEIGHT;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (abs(player->x - this->x) < 95 && !start) {
		start = true;
		state = KNIGHT_STATE_RUN;
		if (player->x < this->x) {
			dir = -1;
		}
		else {
			dir = 1;
		}
	}
	if (start) {
		if (abs(player->x - this->x) > 95 ) {
			if (player->x < this->x) {
				dir = -1;
			}
			else {
				dir = 1;
			}
		}
		if (dir == -1) {
			this->vx = -KNIGHT_SPEED;
		}
		else {
			this->vx = KNIGHT_SPEED;
		}

	}
	DebugOut(L"Knight dir %d \n",dir);

	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += KNIGHT_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != OBJ_DIE)
		CalcPotentialCollisions(coObjects, coEvents);



	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		state = KNIGHT_STATE_RUN;

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Knight::Render()
{
	int ani = 0;
	if (state == KNIGHT_STATE_IDLE) {

		if (nx > 0)
			ani = KNIGHT_ANI_IDLE_RIGHT;
		else ani = KNIGHT_ANI_IDLE_LEFT;

	}
	if (state == KNIGHT_STATE_RUN) {
		if (vx == 0)
		{
			if (nx > 0)
				ani = KNIGHT_ANI_RUN_RIGHT;
			else ani = KNIGHT_ANI_RUN_LEFT;
		}
		else if (vx > 0)
			ani = KNIGHT_ANI_RUN_RIGHT;
		else ani = KNIGHT_ANI_RUN_LEFT;
	}
	
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

Enemy * Knight::clone()
{
	return nullptr;
}


Knight::~Knight()
{
}
