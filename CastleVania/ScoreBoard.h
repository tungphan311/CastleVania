#pragma once
#include "GameObject.h"
#include "SubWeapon.h"
#include "Simon.h"
#include <string>
#include "Boss.h"

class ScoreBoard: public GameObject
{
public:
	ID3DXFont *font;
	RECT rect;
	int healBar;
	int playerHeal;
	int enemyHeal;
	int score;
	int time;
	int stage;
	int heart;
	int playerLife;
	int subWeapon;
	bool doubleShot;

	ScoreBoard();
	~ScoreBoard();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects = NULL, vector<LPGAMEOBJECT*> *coObjects = NULL) {}
	void Update(DWORD dt, Simon *simon, SubWeapon *subWeapon, Boss *boss);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
};

