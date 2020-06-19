#include "Zombie.h"
#include "Sprites.h"
#include "Textures.h"


Zombie::Zombie()
{
	
	
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

	
	x += dx;
	y += dy;
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
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
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

Enemy * Zombie::clone()
{
	return new Zombie(*this);
}

Zombie::~Zombie()
{
}
