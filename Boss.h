#include "Enemy.h"
#define BOSS_SPEED 0.04f
#define BOSS_BBOX_WIDTH 48
#define BOSS_BBOX_HEIGHT 22
#define BOSS_ANI_IDLE 0
#define BOSS_ANI_FLY 1

#define BOSS_PHARSE_1 1
#define BOSS_PHARSE_2 2

class Boss : public Enemy
{
private:
	bool start,canchangepharse;
	float dirX, dirY;
	float LastPx, LastPy;
	float StartX, StartY;
	int pharse;
	
public:
	Boss();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	bool minusHp(int dam);
	virtual Enemy* clone();
	~Boss();
};

