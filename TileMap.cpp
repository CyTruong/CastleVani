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
	/*mapMatrix = new int *[this->mapHeight];
	for (int i = 0; i <= 37; i++)
	{
		mapMatrix[i] = new int[this->mapWidth];
	}*/
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
			mapMat[j * 100 + i] = atoi(pch);
			//mapMatrix[j][i] = atoi(pch);
			DebugOut(L"%d ", atoi(pch));
		/*	if (mapMatrix[j][i] == 70 || mapMatrix[j][i] == 40) {
				DebugOut(L"1	%d	%d	22\n", i * 16, j * 16);
			}*/
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
	float camposX;
	float camposY;
	CGame::GetInstance()->GetCamPos(camposX,camposY);
	camposX = camposX / 16;
	camposY = camposY / 16;
	float camposX2 = camposX + (SCREEN_WIDTH / 16);
	float camposY2 = camposY + (SCREEN_HEIGHT / 16) ;
	if (camposX  < 0) {
		camposX = 0;
	}
	if (camposY < 0) {
		camposY = 0;
	}
	
	//DebugOut(L"campos lt(%f,%f) rb(%f,%f) \n", floorf(camposX), floorf(camposY), ceil(camposX2) - 1, ceil(camposY2) - 1);
	for (int i = ceil(camposY) + 2; i < ceil(camposY2) - 1; i++) {
		for (int j = floorf(camposX); j < ceil(camposX2) - 1; j++) {
			sprites->Get(TEXTTURE_START + mapMat[i*100+j])->Draw(j * 16, i * 16);

			//sprites->Get(TEXTTURE_START + mapMatrix[i][j])->Draw(j * 16, i * 16);
		}
	}
}

void TileMap::Unload()
{
	
}

void TileMap::GetMapSize(int& width,int& height) {
	width = mapCollum * MAP_TILE_WIDTH;
	height = mapRow * MAP_TITE_HEIGHT;
}

void TileMap::Update() {

}

TileMap::~TileMap()
{
	/*mapMatrix = NULL;*/
}
