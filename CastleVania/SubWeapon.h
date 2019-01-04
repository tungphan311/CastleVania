#pragma once
#include "GameObject.h"

class SubWeapon: public GameObject
{
	SubWeapon *currentSubWeapon;
	static SubWeapon *_instance;
public:
	SubWeapon();
	SubWeapon(int state);
	~SubWeapon();

	void replaceSubWeapon(int state);
	static SubWeapon *GetInstance();
	SubWeapon *GetCurrentSubWeapon() { return this->currentSubWeapon; }

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) {};
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects = NULL, vector<LPGAMEOBJECT*>* coObjects = NULL);

	void SetState(int state);
	int GetState() { return this->state; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

