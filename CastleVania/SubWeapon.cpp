#include "SubWeapon.h"
#include "Dagger.h"
#include "Axe.h"
#include "FireBomb.h"
#include "Watch.h"
#include "Boomerang.h"

SubWeapon *SubWeapon::_instance = NULL;

SubWeapon::SubWeapon()
{

}

SubWeapon::SubWeapon(int state): GameObject()
{
	
}

SubWeapon::~SubWeapon()
{
}

void SubWeapon::replaceSubWeapon(int state)
{
	delete currentSubWeapon;
	
	SetState(state);
	//if (state == DAGGER)
	//	currentSubWeapon = new Dagger();
	//else if (state == AXE)
	//	currentSubWeapon = new Axe();
	//else if (state == FIRE_BOMB)
	//	currentSubWeapon = new FireBomb();
	//else if (state == WATCH)
	//	currentSubWeapon = new Watch();
	//else if (state == BOOMERANG)
	//	currentSubWeapon = new Boomerang();
}

SubWeapon * SubWeapon::GetInstance()
{
	if (_instance == NULL) _instance = new SubWeapon();
	return _instance;
}

void SubWeapon::Render()
{
	currentSubWeapon->Render();
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* objects, vector<LPGAMEOBJECT*>* coObjects)
{
	currentSubWeapon->Update(dt, objects, coObjects);
}

void SubWeapon::SetState(int state)
{
	GameObject::SetState(state);
}

void SubWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	currentSubWeapon->GetBoundingBox(left, top, right, bottom);
}

