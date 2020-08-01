#include "StairStep.h"
#include "Utils.h"



StairStep::StairStep(float l, float t, float r, float b)
{
	this->x = l;
	this->y = t;
	this->width = r - l + 1;
	this->height = b - t + 1;
	collision_able = false;
	atk_able = false;
	this->Stair = NULL;
	this->SetPosition(x, y);
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(22);

	this->SetAnimationSet(ani_set);
}



void StairStep::Render()
{
	RenderBoundingBox();
}



void StairStep::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;

}

bool StairStep::GetSimonVertex(float simonX, float simonY, float & vx, float & vy)
{
	//DebugOut(L"simon vs stair %f \n", abs(x + 10 + SIMON_HAFT_BBOX_WIDTH - simonX));
		DebugOut(L"simon vs stair %f \n", abs(x + width / 2 - simonX + SIMON_HAFT_BBOX_WIDTH));

	if ((simonX + SIMON_HAFT_BBOX_WIDTH) <= (x + width / 2)) {
		vx = 0.05f; //0.05 * cos 45 = 0.035
	}
	if ((simonX + SIMON_HAFT_BBOX_WIDTH ) > (x + width/2)) {
		vx = -0.05f;
	}
	/*if (abs(x+10+ SIMON_HAFT_BBOX_WIDTH - simonX) < 2) {
		return true;
	}*/
	if (abs(x+ width /2   -    simonX+ SIMON_HAFT_BBOX_WIDTH)<2) {
		return true;
	}
	Stairs* stair = dynamic_cast<Stairs*>(this->Stair);
	if (abs(x + width / 2 - simonX + SIMON_HAFT_BBOX_WIDTH) < 19  && stair->type == STAIRS_R2L ) {
		return true;
	}
	return false;
}


StairStep::~StairStep()
{
}
