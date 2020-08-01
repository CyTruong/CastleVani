#include "Effect.h"
#include "debug.h"
#include "Game.h"

Effect* Effect::__instance = NULL;


Effect::Effect()
{
	isHitEffect = false;
	HitEffectX = 0;
	HitEffectY = 300;
}

Effect * Effect::getInstance()
{
	if (__instance == NULL)
		__instance = new Effect();
	return __instance;
}


Effect::~Effect()
{
}
