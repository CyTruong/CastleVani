﻿#include "EndScene.h"
#include <iostream>
#include <fstream>
#include "EmptyObj.h"
#include "PlayerStatus.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPSET 7
#define SCENE_SECTION_ENEMY 8

#define MAX_SCENE_LINE 1024

#define OBJ_BACKGROUND 1 

void EndScene::_ParseSection_TEXTURES(string line)
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

void EndScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() <8) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int ax = atoi(tokens[5].c_str());
	int ay = atoi(tokens[6].c_str());
	int texID = atoi(tokens[7].c_str());
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, ax, ay, tex);
}

void EndScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void EndScene::_ParseSection_ANIMATION_SETS(string line)
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
}

void EndScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = new EmptyObj();
	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);

}

EndScene::EndScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CEndScenceKeyHandler(this);
	section = 1;
}

void EndScene::Load()
{
	//setup thông tim player trc
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	gametime = 0;
	section = 1;
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_MAPSET; continue; }
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[ENEMY]") {
			section = SCENE_SECTION_ENEMY; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}
	int hp = 0;
	int mana = 0;
	PlayerStatus::getInstance()->getPlayerHp(hp);
	PlayerStatus::getInstance()->getPlayerMana(mana);
	//Khởi tạo Ui
	ui = new UI(hp, mana, 3, 1);
	ui->Initialize();

	f.close();


	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	CGame::GetInstance()->SetCamPos2(0, 0, 256, 256);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void EndScene::Update(DWORD dt)
{
	gametime += dt;
	if (gametime >= 1000)
	{
		int subweapon = 0;
		int hp = 10; int  mana = 10; int sceneid = 0; int score = 0; int enemyHp = 16; int life = 3;
		PlayerStatus::getInstance()->getPlayerHp(hp);
		PlayerStatus::getInstance()->getPlayerMana(mana);
		PlayerStatus::getInstance()->getStateIndex(sceneid);
		PlayerStatus::getInstance()->getScore(score);
		PlayerStatus::getInstance()->getEnemyHp(enemyHp);
		PlayerStatus::getInstance()->getPlayerLife(life);
		ui->Update(300 - (int)gametime / 1000, hp, mana, life, sceneid, subweapon, score, enemyHp);
	}
}

void EndScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	ui->Render();
}

void EndScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	delete ui;

}


EndScene::~EndScene()
{
}

void CEndScenceKeyHandler::KeyState(BYTE * states)
{
}

void CEndScenceKeyHandler::OnKeyDown(int KeyCode)
{
	LPGAMEOBJECT cursor = ((EndScene*)scence)->objects.at(1);
	int option = ((EndScene*)scence)->section;
	switch (KeyCode)
	{
	case DIK_UP:
		cursor->SetPosition(58, 122);
		((EndScene*)scence)->section = 1;
		break;
	case DIK_DOWN:
		 cursor = ((EndScene*)scence)->objects.at(1);
		cursor->SetPosition(58, 148);
		((EndScene*)scence)->section = 2;
		break;
	case DIK_X:
		if (option==1) {
			int scene;
			PlayerStatus::getInstance()->getStateIndex(scene);
			PlayerStatus::getInstance()->Renew();
			CGame::GetInstance()->SwitchScene(1,true);

		}
		else {
			CGame::GetInstance()->SwitchScene(0,true);
			PlayerStatus::getInstance()->Renew();
		}
		break;
	default:
		break;
	}
}

void CEndScenceKeyHandler::OnKeyUp(int KeyCode)
{
}
