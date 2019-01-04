#pragma once
#include "GameObject.h"
#include "Item.h"

class Effect: public GameObject
{
public:
	Effect();
	~Effect();
	Item *item;
	DWORD timer;
	bool turnon;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects = NULL, vector<LPGAMEOBJECT*> *coObjects = NULL);
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

