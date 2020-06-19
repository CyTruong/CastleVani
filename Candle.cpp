#include "Candle.h"



Candle::Candle()
{
	this->collision_able = false;
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Candle::Render()
{
	if (state != CANDLE_STATE_DESTROY)
		animation_set->at(CANDLE_ANI_IDLE)->Render(x, y);
}


Candle::~Candle()
{
}
