#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Candle: public GameObject
{
public:
	Candle() : GameObject() {}
	Candle(int _state);


	int item;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

