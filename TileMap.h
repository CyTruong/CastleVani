#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "debug.h"
#include "Game.h"

#define ID_TEX_MAP1 1000

#define MAP_TILE_WIDTH 16
#define MAP_TITE_HEIGHT 16
#define TEXTTURE_START 99000
class TileMap
{
private :
	int** mapMatrix;
	int mapRow;
	int mapCollum;
	string mapFile;
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	int titlesetId;
public:
	TileMap(int id, int mapwidth, int mapheight, string mapfile, int texturewidth, int textureHeight);
	void GetMapSize(int& width , int& height);
	void LoadTileSet();
	void Update();
	void Render();
	~TileMap();
};

