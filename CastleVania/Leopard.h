#pragma once
#include "GameObject.h"

class Leopard: public GameObject
{
public:
	Leopard() : GameObject() {}
	Leopard(int order);
	~Leopard();

	int direction;
	float posY;
	int order;	// dung de xet vi tri cua Leopard
	bool isJump; 
	bool allowJump;
	bool checkCollision;

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};


