#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Define.h"

class Item: public GameObject
{
	DWORD timeAppear;
public:
	Item();
	
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void SetItem();
	void SetItemOnEnemy();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

