#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Utils.h"
#include "UI.h"


class EndScene :
	public CScene
{
protected:
	vector<LPGAMEOBJECT> objects;
	LPGAMEOBJECT cursor;
	int section;
	UI* ui; 
protected:
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	EndScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	friend class CEndScenceKeyHandler;
	~EndScene();
};

class CEndScenceKeyHandler : public CScenceKeyHandler
{

public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CEndScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};