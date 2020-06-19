#pragma once
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "Heart.h"
#include "Grid.h"
#include "WhipUpdate.h"
#include "Utils.h"
#include "DaggerPicker.h"
#include "HolyPicker.h"
#include "AxePicker.h"
#include "BoomerangPicker.h"

#define ITEM_HEART 0
#define ITEM_WHIP_UPDATE 1
#define ITEM_SUB_WEAPON_1 2 //dagger
#define ITEM_SUB_WEAPON_2 3 //holy
#define ITEM_SUB_WEAPON_3 4 //axe
#define ITEM_SUB_WEAPON_4 5 // bmr
#define ITEM_COUNT 5

class ItemSpaw
{
private: static  ItemSpaw* __instance;
public:
	static ItemSpaw* getInstance();
	ItemSpaw();
	LPGAMEOBJECT CreateObj(int x, int y);
	~ItemSpaw();
};

