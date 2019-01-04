#pragma once
#include "GameObject.h"
#include "Simon.h"

class Boss: public GameObject
{
public:
	Boss();
	~Boss();
	int HP;
	bool isChangeDirection;
	bool active;
	bool isAttack;
	float posY;
	bool isStop;
	DWORD stopTimer;
	DWORD attackTimer;
	int ny;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	void Update(DWORD dt, Simon *simon);
	virtual void Render();

	void SetState(int state, float a = 0);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

