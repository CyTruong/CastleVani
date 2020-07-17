#include "Grid.h"
#include "TileMap.h"
#include "debug.h"
#include "Game.h"

Grid* Grid::__instance = NULL;

Grid::Grid()
{
	int width = 1552;
	int height = 400;
	height = ( height /  GRID_HEIGHT ) +1;
	width = ( width / GRID_WIDTH ) +1;
	Nodes = new GridNode*[height+1];
	for (int i = 0; i <= height; i++) {
		Nodes[i] = new GridNode[width+1];
	}
	Row = height;
	Col = width;
}

void Grid::InsertGridNode(LPGAMEOBJECT gobj, int w, int h)
{
	Nodes[h][w].arrObj.push_back(gobj);

}

void Grid::Insert(LPGAMEOBJECT gobjs) {
	int w = (int)(gobjs->x / GRID_WIDTH);
	int h = (int)(gobjs->y / GRID_HEIGHT);
	Nodes[h][w].arrObj.push_back(gobjs);
}

void Grid::Push(vector<LPGAMEOBJECT> gobjs) {
	for each (LPGAMEOBJECT obj in gobjs)
	{
		int w = (int) ( obj->x / GRID_WIDTH ); 
		int h = (int) ( obj->y / GRID_HEIGHT );
		Nodes[h][w].arrObj.push_back(obj);

	}
}

vector<LPGAMEOBJECT> Grid::Get() {
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX,camY);
	int GridX1 =(int) camX / GRID_WIDTH;
	int GridY1 = (int) camY / GRID_HEIGHT;
	GridX1 = GridX1 > 0 ? GridX1 : 0;
	GridY1 = GridY1 > 0 ? GridY1 : 0;
	
	int GridX2 = (int)((camX+ SCREEN_WIDTH) / GRID_WIDTH);
	int GridY2 = (int)((camY+ SCREEN_HEIGHT) / GRID_HEIGHT);
	GridX2 = GridX2 > Col ? Col : GridX2;
	GridY2 = GridY2 > Row ? Row : GridY2;

	////thực chất cái này cho sure
	//if (GridX1 > GridX2) {
	//	int tem = GridX1;
	//	GridX1 = GridX2;
	//	GridX2 = tem;
	//}
	//if (GridY1 > GridY2) {
	//	int tem = GridY1;
	//	GridY1 = GridY2;
	//	GridY2 = tem;
	//}
	vector<LPGAMEOBJECT> Result;

	for (int j = GridY1; j <= GridY2; j++) {
		for (int i = GridX1; i <= GridX2; i++) {
			Result.insert(Result.end(),Nodes[j][i].arrObj.begin(), Nodes[j][i].arrObj.end());
		}
	}
	//DebugOut(L"PHKG (%d,%d)->(%d,%d) size : %d \n", GridY1, GridX1, GridY2, GridX2,Result.size());
	return Result;
}

void Grid::clear()
{
	free(Nodes);
	__instance = NULL;
}

Grid* Grid::GetInstance() {
	if (__instance == NULL) __instance = new Grid();
	return __instance;
}

Grid::~Grid()
{
}
