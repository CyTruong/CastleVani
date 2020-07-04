#include "TimeStop.h"
#include "PlayerStatus.h"


TimeStop::TimeStop()
{
	timecount = 0;
	this->vx = 0;
	PlayerStatus::getInstance()->ZAWARUDO(false);
}

void TimeStop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

void TimeStop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vx != 0 ) {
		timecount += dt;
		PlayerStatus::getInstance()->ZAWARUDO(true);
		if (timecount> 3000) {
			PlayerStatus::getInstance()->ZAWARUDO(false);
			vx = 0;
			timecount = 0;
		}
	}
}

void TimeStop::Render()
{
}


TimeStop::~TimeStop()
{
}
