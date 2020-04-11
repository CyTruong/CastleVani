#pragma once
#include <Windows.h>
#include "Heart.h"
#include "Grid.h"
#include	"WhipUpdate.h"
#define ITEM_HEART_ID 1
#define ITEM_WHIP_UPDATE 2
#define ITEM_SUB_WEAPON_1 3

class ItemSpaw
{
private: static  ItemSpaw* __instance;
public:
	static ItemSpaw* getInstance();
	ItemSpaw();
	LPGAMEOBJECT CreateObj(int x, int y);
	~ItemSpaw();
};

