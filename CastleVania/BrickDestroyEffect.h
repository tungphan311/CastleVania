#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Define.h"
#include "GameObject.h"

class BrickDestroyEffect: public GameObject
{
public:
	BrickDestroyEffect() {}
	BrickDestroyEffect(int index);
	~BrickDestroyEffect();
	int index;
	bool isDone;

	virtual void LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations);
	virtual void Update(DWORD dt,  vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	void SetIndex(int index);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) {}
};

typedef BrickDestroyEffect *LPBRICKDESTROYEFFECT;

class BrickEffects
{
public:
	BrickEffects();
	~BrickEffects() {}

	vector<LPBRICKDESTROYEFFECT> effects;
	bool isDone;

	void Update(DWORD dt);
	void Render();
	void SetPosition(float x, float y);
};
typedef BrickEffects *LPBRICKEFFECTS;

