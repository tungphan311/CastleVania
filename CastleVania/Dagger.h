#pragma once
#include "SubWeapon.h"
#include "Textures.h"
#include "Sprites.h"

class Dagger: public SubWeapon
{
public:
	Dagger();
	
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) {};
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void SetDaggerPosition(D3DXVECTOR3 simonPos, bool isStand);
	bool CheckCollision(float left, float top, float right, float bottom);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

