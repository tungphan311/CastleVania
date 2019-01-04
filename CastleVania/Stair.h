#pragma once
#include "GameObject.h"

class Stair: public GameObject
{
public:
	Stair(): GameObject() {}
 	Stair(int state, int nx);
	
	virtual void LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations) {}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

