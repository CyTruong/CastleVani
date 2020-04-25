#include "UI.h"
#include <string>


UI::UI(int _simonHP, int _simonEnergy, int _simonLife, int _stage)
{
	simonHP = _simonHP;
	simonEnergy = _simonEnergy;
	simonLife = _simonLife;
	stage = _stage;

	enemyHP = 16;
	LoadResource();
}

UI::~UI()
{
}

bool UI::Initialize()
{
	font = NULL;
	AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		CGame::GetInstance()->GetDirect3DDevice(), 8, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);

	if (!SUCCEEDED(result))
	{
		return false;
	}


	//SetRect(&rect, 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT);
	info = "SCORE-000000 TIME 0300 STAGE 01\n";
	info += "PLAYER                 =05\n";
	info += "ENEMY                 P=3\n";
}

void UI::Update(int time, int _simonHP, int _simonEnergy, int _simonLife, int _stage)
{
	simonHP = _simonHP;
	simonEnergy = _simonEnergy;
	simonLife = _simonLife;
	stage = _stage;

	string timeString = to_string(time);
	switch (timeString.length())
	{
	case 3:
		timeString = "0" + timeString;
		break;
	case 2:
		timeString = "00" + timeString;
		break;
	case 1:
		timeString = "0000" + timeString;
		break;
	}

	string stageString = to_string(stage);
	if (stageString.length() <= 1)
	{
		stageString = "0" + stageString;
	}

	string simonLifeString = to_string(simonLife);

	string simonEnergyString = to_string(simonEnergy);
	if (simonEnergyString.length() <= 1)
	{
		simonEnergyString = "0" + simonEnergyString;
	}

	info = "SCORE-000000 TIME " + timeString + " STAGE " + stageString + "\n";
	info += "PLAYER                 =" + simonEnergyString + "\n";
	info += "ENEMY                 P=" + simonLifeString + "\n";

}

void UI::Render()	
{
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX,camY);
	//set UI theo cam

	RECT rect;
	SetRect(&rect, 0, 8, SCREEN_WIDTH, SCREEN_HEIGHT);
	//sprite heart
	CSprites::GetInstance()->Get(3000)->Draw(camX+ 176,camY+ 16);
	//Simon HP
	float simonHPx = 56;
	float simonHPy = 17;
	for (int i = 0; i < simonHP; i++)
	{
		CSprites::GetInstance()->Get(3001)->Draw(camX+simonHPx, camY+ simonHPy);
		simonHPx += 5;
	}
	for (int i = 0; i < 16 - simonHP; i++)
	{
		CSprites::GetInstance()->Get(3003)->Draw(camX+simonHPx,camY+ simonHPy);
		simonHPx += 5;
	}
	//Ememy HP
	float ememyHPx = 56;
	float enemyHPy = 25;
	for (int i = 0; i < enemyHP; i++)
	{
		CSprites::GetInstance()->Get(3002)->Draw(camX + ememyHPx, camY + enemyHPy);
		ememyHPx += 5;
	}
	for (int i = 0; i < 16 - enemyHP; i++)
	{
		CSprites::GetInstance()->Get(3003)->Draw(camX + ememyHPx, camY + enemyHPy);
		ememyHPx += 5;
	}
	//Font information
	if (font)
	{
		font->DrawTextA(NULL, info.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
	//Square
	CSprites::GetInstance()->Get(3004)->Draw(camX + 140, camY + 16);
}

void UI::LoadResource()
{
}
