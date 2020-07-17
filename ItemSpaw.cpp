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

LPGAMEOBJECT ItemSpaw::CreateObj(int x, int y,int itemindex)
{
	if (itemindex==-1) {
		srand(time(NULL));   // Initialization, should only be called once.
		itemindex = rand() % ITEM_COUNT;
	}
	DebugOut(L"Get item %d \n", itemindex);
	if (itemindex == ITEM_HEART) {
		Heart* heart = new Heart();
		heart->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(heart);
		return heart;
	}
	if (itemindex == ITEM_WHIP_UPDATE) {
		WhipUpdate* update = new WhipUpdate();
		update->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(update);
		return update;
	}
	if (itemindex ==ITEM_SUB_WEAPON_1) {
		DaggerPicker* daggerpk = new DaggerPicker();
		daggerpk->SetPosition(x,y+5);
		Grid::GetInstance()->Insert(daggerpk);
		return daggerpk;
	}
	if (itemindex == ITEM_SUB_WEAPON_2) {
		HolyPicker* holypk = new HolyPicker();
		holypk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(holypk);
		return	holypk;
	}
	if (itemindex == ITEM_SUB_WEAPON_3) {
		AxePicker* axepk = new AxePicker();
		axepk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(axepk);
		return axepk;
	}
	if (itemindex == ITEM_SUB_WEAPON_4) {
		BoomerangPicker * bmrpk = new BoomerangPicker();
		bmrpk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(bmrpk);
		return bmrpk;
	}
	if (itemindex == ITEM_SUB_WEAPON_5) {
		TimestopPicker *tspk = new TimestopPicker();
		tspk->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(tspk);
		return tspk;
	}
	if (itemindex == ITEM_HEART_MINI) {
		HeartMini *heartmin = new HeartMini();
		heartmin->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(heartmin);
		return heartmin;
	}
	if (itemindex == ITEM_BOSS_ORB) {
		BossOrb *orb = new BossOrb();
		orb->SetPosition(x, y + 5);
		Grid::GetInstance()->Insert(orb);
		return orb;
	}
	return NULL;
}


ItemSpaw::~ItemSpaw()
{
}
