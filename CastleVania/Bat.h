#pragma once
#include "GameObject.h"

class Bat: public GameObject
{
public:
	Bat();
	Bat(int nx, float y);
	~Bat();

	float posY;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

