#include "Monkey.h"
#include "PlayerStatus.h"


Monkey::Monkey()
{
	this->vx = 0;
	this->vy = 0;
	this->Hp = 1;
	start = false;
	collision_able = false;
	isJumping = false;
	dir = -1;
	state = MONKEY_STATE_IDLE;
	curspeed = MONKEY_SPEED;
	curhight = MONKEY_JUMP_SPEED;
	timer = 0;
	counter = 0;
	jumpstate = 1;
}

void Monkey::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MONKEY_BBOX_WIDTH;
	bottom = y + MONKEY_BBOX_HEIGHT;
}

void Monkey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!PlayerStatus::getInstance()->isZAWARUDO()) {

		if (abs(player->x - this->x) < 80 && !start) {
			start = true;
			state = MONKEY_STATE_JUMP;
			if (player->x < this->x) {
				dir = -1;
			}
			else {
				dir = 1;
			}
		}
		else {
			if (!start)
				state = MONKEY_STATE_IDLE;
		}


		if (start) {
			
			// Calculate dx, dy 
			CGameObject::Update(dt);
			// Simple fall down
			vy += MONKEY_GRAVITY * dt;

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			if (!isJumping) {
				counter++;			
				//DebugOut(L"JUMP type %d \n", jumpstate);

				if (counter % 2 == 0) {
					if (jumpstate == 1) {
						curhight = MONKEY_JUMP_SPEED2;
						curspeed = MONKEY_SPEED2;
						jumpstate = 2;
					}
					else {
						curhight = MONKEY_JUMP_SPEED;
						curspeed = MONKEY_SPEED;
						jumpstate = 1;
					}
				}
				isJumping = false;
			}

			// turn off collision when die 
			if (state != OBJ_DIE)
				CalcPotentialCollisions(coObjects, coEvents,true);

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				
			
			
				float min_tx, min_ty, nx = 0, ny;
				float rdx = 0;
				float rdy = 0;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		
				if (rdy > 0 || y > MAX_HIGHT) {

					state = MONKEY_STATE_IDLE;
					isJumping = false;
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
					
					if (abs(player->x - this->x) > 60) {
						if (player->x < this->x) {
							dir = -1;
						}
						else {
							dir = 1;
						}
					}

					timer += dt;
					if (timer > 100) {
						timer = 0;
						if (dir == -1) {
							this->vx = -curspeed;
						}
						else {
							this->vx = curspeed;
						}

						if (!isJumping) {
							vy = -curhight;
							state = MONKEY_STATE_JUMP;
						}

					}
					
				}
				else {
					x += vx * dt;
					y += vy * dt;
					DebugOut(L"    vx vy %f %f \n", vx, vy);
					DebugOut(L"    nx ny %f %f \n", nx, ny);
					DebugOut(L"    rx ry %f %f \n", rdx, rdy);
				}

			

				if (isJumping && nx !=0) {
					if (nx < 0) {
						dir = -1;
					}
					else {
						dir = 1;
					}
				}

			}
			//DebugOut(L"dis %f vx %f state %d  \n", abs(player->x - this->x), vx,state);

			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			//DebugOut(L"state %d \n",state);
		}
	}


	//DebugOut(L"Hight %f \n",y);

	if (this->state==OBJ_DIE) {
		start = false;
		dir = 0;
		curspeed = MONKEY_SPEED;
		curhight = MONKEY_JUMP_SPEED;
		isJumping = false;
		timer = 0;
		jumpstate = 1;
		counter =  0;
	}
}

void Monkey::Render()
{
	int ani = 0;
	if (dir < 0) {
		ani = MONKEY_ANI_LEFT;
	}
	else {
		ani = MONKEY_ANI_RIGHT;
	}
	animation_set->at(ani)->Render(x, y, 255, !PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Monkey::clone()
{
	return nullptr;
}


Monkey::~Monkey()
{
}
