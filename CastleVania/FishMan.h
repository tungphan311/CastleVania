#pragma once
#include "GameObject.h"
#include "FireBall.h"

class FishMan: public GameObject
{
	FireBall *fireball;
public:
	FishMan(): GameObject() {}
	FishMan(int nx);
	~FishMan();

	DWORD shotTimer;
	DWORD timer;
	bool checkCollision;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

