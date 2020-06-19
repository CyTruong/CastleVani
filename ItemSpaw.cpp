#include "ItemSpaw.h"

ItemSpaw*  ItemSpaw::__instance = NULL;

ItemSpaw * ItemSpaw::getInstance()
{
	if (__instance == NULL) {
		__instance = new ItemSpaw();
	}
	return __instance;
}

ItemSpaw::ItemSpaw()
{
}

LPGAMEOBJECT ItemSpaw::CreateObj(int x, int y)
{
	srand(time(NULL));   // Initialization, should only be called once.
	int r = rand() % ITEM_COUNT;
	//int r = 1;

	DebugOut(L"Get item %d \n",r);
	if (r == ITEM_HEART) {
		Heart* heart = new Heart();
		heart->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(heart);
		return heart;
	}
	if (r== ITEM_WHIP_UPDATE) {
		WhipUpdate* update = new WhipUpdate();
		update->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(update);
		return update;
	}
	if (r==ITEM_SUB_WEAPON_1) {
		DaggerPicker* daggerpk = new DaggerPicker();
		daggerpk->SetPosition(x,y+5);
		Grid::GetInstance()->Insert(daggerpk);
		return daggerpk;
	}
	if (r == ITEM_SUB_WEAPON_2) {
		HolyPicker* holypk = new HolyPicker();
		holypk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(holypk);
		return	holypk;
	}
	if (r == ITEM_SUB_WEAPON_3) {
		AxePicker* axepk = new AxePicker();
		axepk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(axepk);
		return axepk;
	}
	if (r== ITEM_SUB_WEAPON_4) {
		BoomerangPicker * bmrpk = new BoomerangPicker();
		bmrpk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(bmrpk);
		return bmrpk;
	}
	return NULL;
}


ItemSpaw::~ItemSpaw()
{
}
