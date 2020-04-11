#include "TileMap.h"


TileMap::TileMap(int id, int mapwidth, int mapheight, string mapfile, int texturewidth, int textureHeight)
{
	this->titlesetId = id;
	this->mapWidth = mapwidth;
	this->mapHeight = mapheight;
	this->mapFile = mapfile;
	this->tileWidth = texturewidth;
	this->tileHeight = textureHeight;

	mapRow = 0;
	mapCollum = 0;
	mapMatrix = new int *[this->mapHeight];
	for (int i = 0; i <= 37; i++)
	{
		mapMatrix[i] = new int[this->mapWidth];
	}
}


void TileMap::LoadTileSet() {
	CTextures * ctexture = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texTileMap = ctexture->Get(40); //map 1 : 40

	CSprites * sprites = CSprites::GetInstance();
	for (int j = 0; j < this->tileHeight; j++) {
		for (int i = 0; i < this->tileWidth; i++) {
			int num = TEXTTURE_START + j * 16 + i;
			sprites->Add(num, i * 16, j * 16, (i + 1) * 16,(j + 1) * 16, texTileMap);
			DebugOut(L"id %d left %d top %d right %d bottom %d \n", num, i * 16, j * 16, (i + 1) * 16, (j + 1) * 16);
		}
	}

	FILE *filemap;
	char output[400];
	filemap = fopen(this->mapFile.c_str(), "r");
	int j = 0;
	int i = 0;
	for ( j = 0; fgets(output, sizeof(output), filemap) != NULL; j++) {
		char * pch = strtok(output, " ");
		i= 0;
		while (pch != NULL)
		{
			mapMatrix[j][i] = atoi(pch);
			DebugOut(L"%d ", mapMatrix[j][i]);
			i++;
			pch = strtok(NULL, " ");
		}
		DebugOut(L"\n");
	}
	mapRow = j;
	mapCollum = i;
	

}

void TileMap::Render() {
	CSprites * sprites = CSprites::GetInstance();
	//float camposX;
	//float camposY;
	//CGame::GetInstance()->GetCamPos(camposX,camposY);
	//for (int i = floor(camposY); i < floor(camposY + SCREEN_HEIGHT) - 1; i++) {
	//	for (int j = floor(camposX); j < floor(camposX + SCREEN_WIDTH) - 1; j++) {
	for (int i = 0; i < mapRow-1; i++) {
		for (int j = 0; j < mapCollum-1; j++){
			sprites->Get(TEXTTURE_START + mapMatrix[i][j])->Draw(j * 16, i * 16);
		}
	}
}

void TileMap::GetMapSize(int& width,int& height) {
	width = mapCollum * MAP_TILE_WIDTH;
	height = mapRow * MAP_TITE_HEIGHT;
}

void TileMap::Update() {

}

TileMap::~TileMap()
{
}
