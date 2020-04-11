#pragma once
#include "Game.h"
#include "GameObject.h"

#define GRID_WIDTH 160
#define GRID_HEIGHT 120
class  GridNode
{
public:
	vector<LPGAMEOBJECT> arrObj;
};

class Grid
{
	static Grid * __instance;
private:
	int nodeWidth, nodeHeight;
	int gameWidth, gameHeight;
	int Row, Col;
	GridNode** Nodes;
public:
	static Grid* GetInstance();
	Grid();
	void Insert(LPGAMEOBJECT gobj);
	void Push(vector<LPGAMEOBJECT> gobjs);
	vector<LPGAMEOBJECT> Get();
	void clear();
	~Grid();
};

