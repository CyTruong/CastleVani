#include "EmptyObj.h"



EmptyObj::EmptyObj()
{
}

void EmptyObj::Render()
{	
	animation_set->at(0)->Render(x, y);
}

void EmptyObj::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


EmptyObj::~EmptyObj()
{
}
