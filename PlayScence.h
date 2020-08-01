#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "TileMap.h"
#include "Simon.h"
#include "UI.h"
#include "HitEffect.h"
#include "DestroyEffect.h"
class CPlayScene: public CScene
{
private :
	int isSimonOnstair;
protected: 
	CSimon *player;					
	TileMap *map;
	vector<LPGAMEOBJECT> objects;
	HitEffect* hiteff;
	DestroyEffect* deseff;
	UI* ui;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_Map(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_Enemy(string line);
	void _ParseSection_OBJECTS_GRID(string line);
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

