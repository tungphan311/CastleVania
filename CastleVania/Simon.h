#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Sprites.h"
#include "Textures.h"
#include "Whip.h"
#include "Dagger.h"
#include "Zombie.h"
#include "SubWeapon.h"
#include "FireBomb.h"

class Simon: public GameObject
{
	bool isStand;
	Whip *whip;
	Dagger *dagger;
	SubWeapon *subWeapon;
	FireBomb *firebomb;

public:
	bool powerUp = false; // dùng để check xem Simon đã nhặt được item chưa
	DWORD effectTimer;
	bool isOnStair;
	bool isUpOrDown;	// true: go up stair || false: go down stair
	bool isHitGate;
	bool allowUseSubWeapon;
	bool isHitCross;
	bool loseHP;
	bool doubleShot;
	bool win;

	int whipState;
	int HP;
	int heart;
	int life;
	int point;

	bool untouchable;
	DWORD untouchable_start;
	void StartUntouchable() { untouchable_start = GetTickCount(); untouchable = TRUE; }

	Simon();
	
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	void SetState(int state);

	bool IsStand() { return this->isStand; }
	void SetStand(bool flag) { this->isStand = flag; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

