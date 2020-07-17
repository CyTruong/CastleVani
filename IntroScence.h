#pragma once
#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Utils.h"

class IntroScence :
	public CScene
{
private :
	long timer;
protected:
	vector<LPGAMEOBJECT> objects;
protected:
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	IntroScence(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	friend class CSIntroScenceKeyHandler;

	~IntroScence();
};
class CSIntroScenceKeyHandler : public CScenceKeyHandler
{

public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSIntroScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

