#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

#include "Define.h"
#include "debug.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;

struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
public:
	int id;
	float x, y;		// position

	float dx;		// dx = vx*dt
	float dy;		// dy = vy*dt

	float vx;	
	float vy;

	int nx;			// -1: left | 1: right

	int bbox_width;
	int bbox_height;

	int state;		
	int currentState;

	bool isVisible;
	bool isFreeze;
	DWORD freeze_start;

	DWORD dt;
	DWORD timer;
	int itemInside;
	bool destroy;

	vector<vector<int>> position;
	vector<LPANIMATION> animations;

	GameObject();
	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations) = 0;

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(this->x, this->y); }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	float GetVx() { return this->vx; }
	void SetVx(float vx) { this->vx = vx; }
	float GetVy() { return this->vy; }

	int GetState() { return this->state; }
	int GetOrientation() { return nx; }
	void SetOrientation(int nx) { this->nx = nx; }

	void RenderBoundingBox();

	bool SweptAABBExtend(
		float aLeft, float aTop, float aRight, float aBot,
		float bLeft, float bTop, float bRight, float bBot
	);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniId);

	~GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
};

