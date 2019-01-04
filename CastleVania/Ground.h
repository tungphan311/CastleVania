#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Ground: public GameObject
{
public:
	Ground() { }
	Ground(int state, int bbox_width = 32);

	int what;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

