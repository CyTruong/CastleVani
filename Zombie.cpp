#include "Zombie.h"
#include "Sprites.h"
#include "Textures.h"


Zombie::Zombie()
{
	//CTextures * textures = CTextures::GetInstance();
	//CSprites * sprites = CSprites::GetInstance();
	//CAnimations * animations = CAnimations::GetInstance();
	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(CTextures::ENEMY);
	//sprites->Add(43011, 1, 28, 16, 59, texEnemy);
	//sprites->Add(43021, 18, 28, 33, 59, texEnemy);
	//sprites->Add(43012,	931, 28, 946, 59, texEnemy);
	//sprites->Add(43022, 914, 28, 929, 59, texEnemy);
	//LPANIMATION ani = new CAnimation(100);
	//ani->Add(43011);	//left
	//ani->Add(43021);
	//animations->Add(900, ani);
	//this->AddAnimation(900);

	//ani = new CAnimation(100);
	//ani->Add(43012);	//right
	//ani->Add(43022);
	//animations->Add(901, ani);
	//this->AddAnimation(901);

	this->vx = -ZOMBIE_SPEED;

}

void Zombie::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = x + ZOMBIE_BBOX_HEIGHT;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);

	
	x += dx;
	y += dy;
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	
}

void Zombie::Render() {
	int ani = 0 ;

	if (vx < 0) {
		ani = ZOMBIE_ANI_RUN_LEFT;
	}
	else
	{
		ani = ZOMBIE_ANI_RUN_R;
	}
	
	//animations[ani]->Render(x, y);
}

Enemy * Zombie::clone()
{
	return new Zombie(*this);
}

Zombie::~Zombie()
{
}
