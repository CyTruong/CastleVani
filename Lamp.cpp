#include "Lamp.h"
#include "Textures.h"
#include "Sprites.h"

Lamp::Lamp()
{
	this->collision_able = false;

}


Lamp::~Lamp()
{
}

void Lamp::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	

}

void Lamp::Render() {
	if (state != LAMP_STATE_DESTROY) {
		animation_set->at(LAMP_ANI_IDLE)->Render(x, y);
		RenderBoundingBox();
	}

}

void  Lamp::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + LAMP_BBOX_WIDTH;
	bottom = y + LAMP_BBOX_HEIGHT;
}