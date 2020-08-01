#include "Zombie.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayerStatus.h"

Zombie::Zombie()
{
	
	start = false;
	this->vx = -ZOMBIE_SPEED;

}

void Zombie::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);

	if (!PlayerStatus::getInstance()->isZAWARUDO()) {

		if (!start) {
			if (abs(player->x - this->x) < 120 ) {
				start = true;
			}
			else {
			
			}
		}
		if (start) {
			// Calculate dx, dy 
			CGameObject::Update(dt);
			// Simple fall down
			vy += ZOMBIE_GRAVITY * dt;
			this->vx = -ZOMBIE_SPEED;

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			// turn off collision when die 
			if (state != OBJ_DIE)
				CalcPotentialCollisions(coObjects, coEvents, true, true);



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

				// TODO: This is a very ugly designed function!!!!
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;


			}
			//DebugOut(L"dis %f vx %f state %d  \n", abs(player->x - this->x), vx,state);


			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			if (this->x < 0 || this->y > 1000) {
				this->state = OBJ_DIE;
				start = false;
			}
		}
		
	}
	
	
}

void Zombie::Render() {
	int ani = 0 ;

	if (vx < 0) {
		ani = ZOMBIE_ANI_RUN_LEFT;
	}
	else
	{
		ani = ZOMBIE_ANI_RUN_R;
	}
	animation_set->at(ani)->Render(x, y,255, !PlayerStatus::getInstance()->isZAWARUDO());
	RenderBoundingBox();
}

Enemy * Zombie::clone()
{
	return new Zombie(*this);
}

Zombie::~Zombie()
{
}
