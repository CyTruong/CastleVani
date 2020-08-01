#include "Knight.h"
#include "PlayerStatus.h"


Knight::Knight()
{
	this->vx = 0;
	this->vy = 0;
	start = false;
	collision_able = false;
	dir = -1;
	Hp = KNIGHT_HP;
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
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {
		if (abs(player->x - this->x) < 150 && !start) {
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
			if (abs(player->x - this->x) > 40) {
				if (abs(player->y - this->y) < 15) {
					if (player->x +5 < (this->x + KNIGHT_BBOX_WIDTH)) {
						dir = -1;
					}
					else {
						dir = 1;
					}
				}
				
			}
			if (dir == -1) {
				this->vx = -KNIGHT_SPEED;
			}
			else {
				this->vx = KNIGHT_SPEED;
			}

			//DebugOut(L"Knight dir %d \n",dir);

		// Calculate dx, dy 
			CGameObject::Update(dt);
			// Simple fall down
			vy += KNIGHT_GRAVITY * dt;

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			if (state != OBJ_DIE)
				CalcPotentialCollisions(coObjects, coEvents,true,true);



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

				if (nx != 0) {
					vx = 0;
					/*dir = -dir;*/
				}
				if (ny != 0) vy = 0;


			}
			
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			//Chống lọt hố
			float pointX = 0;
			float pointY = y + KNIGHT_BBOX_HEIGHT + 5;
			if (vx < 0) {
				pointX = this->x - 5;
			}else
			if ( vx >= 0) {
				pointX = this->x + KNIGHT_BBOX_WIDTH + 5;
			}
			bool havebrick = false;
			bool isblocked = false;
			for (int i = 0; i < coObjects->size();i ++) {
				LPGAMEOBJECT obj = coObjects->at(i);
				if (obj->x < pointX && pointX < obj->x+16) {
					if (obj->y < pointY && pointY < obj->y + 16) {
						havebrick = true;
						break;
					}
				}
		
			}

			//Chống stuck
			 pointY = y + KNIGHT_BBOX_HEIGHT -5 ;
			 isblocked = false;
			for (int i = 0; i < coObjects->size(); i++) {
				LPGAMEOBJECT obj = coObjects->at(i);
				if (obj->x < pointX && pointX < obj->x + 16) {
					if (obj->y < pointY && pointY < obj->y + 16) {
						isblocked = true;
						break;
					}
				}

			}

			if (!havebrick || isblocked) {
				DebugOut(L"Chống lọt hố quay xe %d %d \n",dir,dt);
				dir = -dir;
			}
			//DebugOut(L"Knight speed %f \n", vx);


		}
		
	}

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
	
	animation_set->at(ani)->Render(x, y,255,!PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Knight::clone()
{
	return nullptr;
}


Knight::~Knight()
{
}
