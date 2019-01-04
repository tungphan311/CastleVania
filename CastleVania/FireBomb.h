#pragma once
#include "SubWeapon.h"

class FireBomb: public SubWeapon
{
public:
	FireBomb();
	~FireBomb();

	DWORD burn_time;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetState(int state);
	bool CheckCollision(float left, float top, float right, float bottom);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

