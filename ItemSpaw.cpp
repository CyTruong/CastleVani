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
	//Heart* heart = new Heart();
	//heart->SetPosition(x,y + 5);
	//Grid::GetInstance()->Insert(heart);
	//return heart;

	WhipUpdate* update = new WhipUpdate();
	update->SetPosition(x, y + 5);
	Grid::GetInstance()->Insert(update);
	return update;
}


ItemSpaw::~ItemSpaw()
{
}
