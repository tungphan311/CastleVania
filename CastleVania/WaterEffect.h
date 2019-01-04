#pragma once
#include "GameObject.h"

class WaterEffect: public GameObject
{
public:
	WaterEffect() {}
	WaterEffect(int index);
	~WaterEffect();

	int index;

	virtual void LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	void SetIndex(int index);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) {}
};

typedef WaterEffect *LPWATEREFFECT;

class WaterEffects
{
public:
	WaterEffects();
	~WaterEffects() {}

	vector<LPWATEREFFECT> effects;
	bool isDone;

	void Update(DWORD dt);
	void Render();
	void SetPosition(float x, float y);
};

typedef WaterEffects *LPWATEREFFECTS;

