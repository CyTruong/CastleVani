#pragma once
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "Heart.h"
#include "Grid.h"
#include "WhipUpdate.h"
#include "Utils.h"
#define ITEM_HEART 0
#define ITEM_WHIP_UPDATE 1
#define ITEM_SUB_WEAPON_1 2
#define ITEM_COUNT 2 //sub wea chua có

class ItemSpaw
{
private: static  ItemSpaw* __instance;
public:
	static ItemSpaw* getInstance();
	ItemSpaw();
	LPGAMEOBJECT CreateObj(int x, int y);
	~ItemSpaw();
};

