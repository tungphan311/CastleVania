#pragma once
#include "SubWeapon.h"

class Boomerang: public SubWeapon
{
public:
	Boomerang();
	~Boomerang();

	float posX;
	bool isChangeDirection;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetState(int state);
	bool CheckCollision(float left, float top, float right, float bottom);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

