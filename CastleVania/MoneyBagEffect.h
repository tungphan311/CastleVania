#pragma once
#include "GameObject.h"

class MoneyBagEffect: public GameObject
{
public:
	MoneyBagEffect();
	~MoneyBagEffect();

	virtual void LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) {}
};

