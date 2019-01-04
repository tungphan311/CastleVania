#pragma once
#include "GameObject.h"
#include "Simon.h"

class Zombie: public GameObject
{

public:
	DWORD setSpawnLeftTime;
	DWORD setSpawnRightTime;
	bool isSpawnLeft;
	bool isSpawnRight;
	//bool destroy;

	Zombie(): GameObject() {}
	Zombie(int nx);

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

