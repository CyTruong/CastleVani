﻿	#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Grid.h"
#include "EnemySpawn.h"
#include "PlayerStatus.h"
#include "Lamp.h"
#include "Heart.h"
#include "Stairs.h"
#include "Candle.h"
#include "FloatingBrick.h"
#include "StairStep.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	isSimonOnstair = 0;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPSET 7
#define SCENE_SECTION_ENEMY 8
#define SCENE_SECTION_OBJECTS_GRID 9

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_LAMP	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_HEART	4
#define OBJECT_TYPE_WHIP_UPDATE 5
#define OBJECT_TYPE_STAIRS	6
#define OBJECT_TYPE_CANDLE	7
#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_FLOATINGBRICK 8
#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_Map(string line)
{
	vector<string> tokens = split(line);
	int id = atoi( tokens[0].c_str());
	int mapwidth = atoi(tokens[1].c_str());
	int mapheight = atoi(tokens[2].c_str());
	string mappath = tokens[3].c_str();
	int tilewidth = atoi(tokens[4].c_str());
	int tileheight = atoi(tokens[5].c_str());
	map = new TileMap(id,mapwidth, mapheight,mappath,tilewidth,tileheight);
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 8) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int ax = atoi(tokens[5].c_str());
	int ay = atoi(tokens[6].c_str());
	int texID = atoi(tokens[7].c_str());
	if (ax!=0) {
		DebugOut(L"");
	}
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b,ax,ay,tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
	DebugOut(L"Animation %d \n", ani_id);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
	DebugOut(L"Ani set %d \n", ani_set_id);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int gw = (int)(x / GRID_WIDTH);
	int gh = (int)(y / GRID_HEIGHT);
	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before! ");
			return;
		}
		obj = new CSimon(); 
		player = (CSimon*)obj;  
		DebugOut(L"%d\t%f\t%f\t%d\t%d\t%d\n", object_type,x,y,ani_set_id,gw,gh);
		break;
	case OBJECT_TYPE_LAMP:
		{	
			float item = atof(tokens[4].c_str());
			obj = new Lamp();
			obj->dropItem = item;
			DebugOut(L"%d\t%f\t%f\t%d\t%f\t%d\t%d\n", object_type, x, y, ani_set_id,item, gw, gh);

			break;
		}
	case OBJECT_TYPE_BRICK: {
		obj = new CBrick(); 
		DebugOut(L"%d\t%f\t%f\t%d\t%d\t%d\n", object_type, x, y, ani_set_id, gw, gh);
		break;
	}
	case OBJECT_TYPE_HEART: obj = new Heart(); break;
	case OBJECT_TYPE_CANDLE:
		{
			float item = atof(tokens[4].c_str());
			obj = new Candle();
			obj->dropItem = item;
			DebugOut(L"%d\t%f\t%f\t%d\t%f\t%d\t%d\n", object_type, x, y, ani_set_id, item, gw, gh);

			break;
		}
	case OBJECT_TYPE_STAIRS: {
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int t = atof(tokens[6].c_str());
			obj = new Stairs(x, y, r, b,t);
			DebugOut(L"%d\t%f\t%f\t%d\t%f\t%f\t%d\t%d\t%d\n", object_type, x, y, ani_set_id,r,b,t, gw, gh);

			break;
		}
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
			DebugOut(L"%d\t%f\t%f\t%d\t%f\t%f\t%d\t%d\t%d\n", object_type, x, y, ani_set_id, r, b, scene_id, gw, gh);

		}
		break;
	case OBJECT_TYPE_FLOATINGBRICK:
		{
			float from = atof(tokens[4].c_str());
			float to = atof(tokens[5].c_str());
			obj = new FloatingBrick(from, to);
			DebugOut(L"%d\t%f\t%f\t%d\t%f\t%f\t%d\t%d\n", object_type, x, y, ani_set_id, from, to, gw, gh);

			break;
		}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	if (!dynamic_cast<CSimon *>(obj)) {
		//là main r nên ko cần thêm vào list
		objects.push_back(obj);
	}
}

void CPlayScene::_ParseSection_Enemy(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int enemy_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	Enemy *enemy = NULL;
	enemy = EnemySpawn::getInstance()->getEnemy(enemy_type, x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	enemy->SetAnimationSet(ani_set);
	DebugOut(L"enemy spaw %f %f %d \n",x,y,ani_set_id);
}

void CPlayScene::_ParseSection_OBJECTS_GRID(string line)
{
	vector<string> tokens = split(line);
	wstring path = ToWSTR(tokens[0]);
	ifstream f;
	f.open(line);
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);
		vector<string> objectoken = split(line);

		if (objectoken.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

		int object_type = atoi(objectoken[0].c_str());
		float x = atof(objectoken[1].c_str());
		float y = atof(objectoken[2].c_str());
		int ani_set_id = atoi(objectoken[3].c_str());
		int gx = 0;
		int gy = 0;

		CAnimationSets * animation_sets = CAnimationSets::GetInstance();

		CGameObject *obj = NULL;

		switch (object_type)
		{
		case OBJECT_TYPE_SIMON:
			if (player != NULL)
			{
				return;
			}
			this->isSimonOnstair = atof(objectoken[4].c_str());
			obj = new CSimon();
			player = (CSimon*)obj;
			break;
		case OBJECT_TYPE_LAMP:
		{
			float item = atof(objectoken[4].c_str());
			gx = atof(objectoken[5].c_str());
			gy = atof(objectoken[6].c_str());

			obj = new Lamp();
			obj->dropItem = item;
			break;
		}
		case OBJECT_TYPE_BRICK: {
			obj = new CBrick();
			 gx = atof(objectoken[4].c_str());
			 gy = atof(objectoken[5].c_str());
			break;
		}
		case OBJECT_TYPE_HEART: obj = new Heart(); break;
		case OBJECT_TYPE_CANDLE:
		{
			float item = atof(objectoken[4].c_str());
			gx = atof(objectoken[5].c_str());
			gy = atof(objectoken[6].c_str());
			obj = new Candle();
			obj->dropItem = item;

			break;
		}
		case OBJECT_TYPE_STAIRS: {
			float r = atof(objectoken[4].c_str());
			float b = atof(objectoken[5].c_str());
			int t = atof(objectoken[6].c_str());
			gx = atof(objectoken[7].c_str());
			gy = atof(objectoken[8].c_str());
			obj = new Stairs(x, y, r, b, t);
			float haftW = 20;
			float hight = 20;
			if (t == STAIRS_L2R) {
				StairStep *step = new StairStep(x - haftW -5, b - hight, x + haftW -5, b);
				//StairStep *step2 = new StairStep(r - haftW, y - hight, r + haftW, y + 5);
				step->Stair = obj;
				//step2->Stair = obj;
				Grid::GetInstance()->InsertGridNode(step, gx, gy);
				//Grid::GetInstance()->InsertGridNode(step2, gx, gy);
				step->pos = 1;
				//step2->pos = 2;
			}
			if (t == STAIRS_R2L) {
				StairStep *step = new StairStep(r - haftW+5, b - hight, r + haftW +5, b);
				//StairStep *step2 = new StairStep(x- haftW, y -hight, x + haftW, y + 5);
				step->Stair = obj;
				//step2->Stair = obj;
				Grid::GetInstance()->InsertGridNode(step, gx, gy);
				//Grid::GetInstance()->InsertGridNode(step2, gx, gy);
			}
			
			if (this->isSimonOnstair == 1) {
				if (player->cauthang==NULL) {
					this->player->cauthang = dynamic_cast<Stairs*>(obj);
					player->SetState(SIMON_STATE_CLIMP);
				}
			}
			break;
		}
		case OBJECT_TYPE_PORTAL:
		{
			float r = atof(objectoken[4].c_str());
			float b = atof(objectoken[5].c_str());
			int scene_id = atoi(objectoken[6].c_str());
			gx = atof(objectoken[7].c_str());
			gy = atof(objectoken[8].c_str());
			obj = new CPortal(x, y, r, b, scene_id);

		}
		break;
		case OBJECT_TYPE_FLOATINGBRICK:
		{
			float from = atof(objectoken[4].c_str());
			float to = atof(objectoken[5].c_str()); 
			gx = atof(objectoken[6].c_str());
			gy = atof(objectoken[7].c_str());
			obj = new FloatingBrick(from, to);

			break;
		}
		default:
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			return;
		}

		// General object setup
		obj->SetPosition(x, y);

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		if (!dynamic_cast<CSimon *>(obj)) {
			Grid::GetInstance()->InsertGridNode(obj, gx, gy);
		}
	}
}

void CPlayScene::Load()
{
	//setup thông tim player trc
	int hp = 0;
	int mana = 0;
	PlayerStatus::getInstance()->getPlayerHp(hp);
	PlayerStatus::getInstance()->getPlayerMana(mana);

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	gametime = 0;
	Grid::GetInstance();
	EnemySpawn::getInstance();

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line =="[BACKGROUND]") { section = SCENE_SECTION_MAPSET; continue; }
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[ENEMY]") {
			EnemySpawn::getInstance()->Clear(player);
			section = SCENE_SECTION_ENEMY; continue;}
		if (line == "[OBJECT_GRID]") {
			section = SCENE_SECTION_OBJECTS_GRID; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_MAPSET: _ParseSection_Map(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_ENEMY: _ParseSection_Enemy(line); break;
			case SCENE_SECTION_OBJECTS_GRID: _ParseSection_OBJECTS_GRID(line); break;
		}
	}
	//Khởi tạo Ui

	ui = new UI(hp, mana, 3, 1);
	ui->Initialize();
	hiteff = new HitEffect();
	deseff = new DestroyEffect();
	map->LoadTileSet();
	Grid::GetInstance()->Push(objects);
	f.close();
	

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{

	gametime += dt;
	if (gametime >= 1000)
	{
		int subweapon = 0;
		player->getSubweapon(subweapon);
		int hp = 10; int  mana = 10; int sceneid = 0; int score = 0; int enemyHp = 16; int life = 3;
		PlayerStatus::getInstance()->getPlayerHp(hp);
		PlayerStatus::getInstance()->getPlayerMana(mana);
		PlayerStatus::getInstance()->getStateIndex(sceneid);
		PlayerStatus::getInstance()->getScore(score);
		PlayerStatus::getInstance()->getEnemyHp(enemyHp);
		PlayerStatus::getInstance()->getPlayerLife(life);
		ui->Update(300 - (int)gametime / 1000,hp, mana, life, sceneid, subweapon, score, enemyHp);
	}
	vector<LPGAMEOBJECT> objects = Grid::GetInstance()->Get();

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (!dynamic_cast<CSimon *>(objects[i])) {
			objects[i]->Update(dt, &coObjects);
		}
		
	}
	player->Update(dt, &coObjects);
	hiteff->Update(dt, &coObjects);
	deseff->Update(dt, &coObjects);
	EnemySpawn::getInstance()->Update(dt, &coObjects);

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	//CGame::GetInstance()->SetCamPos((int)cx,(int)cy-32);
	int mapwidth, mapheight;
	map->GetMapSize(mapwidth, mapheight);
	
	if(!PlayerStatus::getInstance()->isCamLocked()){
		CGame::GetInstance()->SetCamPos2((int)cx, (int)cy, mapwidth, mapheight);
	}


	//check player
	int hp = 0; 
	PlayerStatus::getInstance()->getPlayerHp(hp);
	if (player->y > mapheight || hp <= 0) {
		PlayerStatus::getInstance()->SetHp(0);
	}
}

void CPlayScene::Render()
{
	map->Render();
	EnemySpawn::getInstance()->Render();
	vector<LPGAMEOBJECT> objects = Grid::GetInstance()->Get();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();
	hiteff->Render();
	deseff->Render();
	ui->Render();

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	Grid::GetInstance()->clear();
	delete map;
	delete ui;
	player = NULL;
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CSimon *simon = ((CPlayScene*)scence)->player;
	switch (KeyCode)
	{
	case DIK_Z:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_M: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetStatus(SIMON_STA_NOR);
		simon->SetPosition(100.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_X:
		//simon->SetStatus(SIMON_STA_ATK); set ở trong hàm atk của simon
		if (CGame::GetInstance()->IsKeyDown(DIK_UP)) {
			simon->subatk();
		}else
			simon->atk();
		break;
	case DIK_C:
		simon->SetStatus(SIMON_STA_ATK);
		simon->subatk();
		break;
	case DIK_Q:
		simon->setSubweapon(1);
		break;
	case DIK_W:
		simon->setSubweapon(2);
		break;
	case DIK_E:
		simon->setSubweapon(3);
		break;
	case DIK_R:
		simon->setSubweapon(4);
		break;
	case DIK_T:
		simon->setSubweapon(5);
		break;
	case DIK_A:
		CGame::GetInstance()->SwitchScene(1);
		break;
	case DIK_S:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_D:
		CGame::GetInstance()->SwitchScene(3);
		break;
	case DIK_F:
		CGame::GetInstance()->SwitchScene(4);
		break;
	case DIK_G:
		CGame::GetInstance()->SwitchScene(5);
		break;
	case DIK_H:
		CGame::GetInstance()->SwitchScene(6);
		break;
	case DIK_SPACE:
		PlayerStatus::getInstance()->SetHp(16);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CSimon *simon = ((CPlayScene*)scence)->player;
	if (KeyCode==DIK_DOWN) {
		simon->SetStatus(SIMON_STA_STANDUP);
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->player;

	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_DUCK);
	else if (game->IsKeyDown(DIK_UP))
		simon->SetState(SIMON_STATE_CLIMP);
	else
		simon->SetState(SIMON_STATE_IDLE);
}