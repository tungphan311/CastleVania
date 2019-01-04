#pragma once
#include "GameObject.h" 
#include "Textures.h"
#include "Define.h"

class Whip: public GameObject
{
public:
	Whip();
	bool allowCollision;
	bool loseHP;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	
	void SetWhipPosition(D3DXVECTOR3 simonPos, bool isStand);
	bool CheckCollision(float left, float top, float right, float bottom);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

