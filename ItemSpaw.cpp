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
	return NULL;


}


ItemSpaw::~ItemSpaw()
{
}
