#pragma once
#include "GameObject.h"

class Gate: public GameObject
{
public:
	int type;

	Gate(): GameObject() {}
 	Gate(int type);
	~Gate();

	virtual void LoadResources(Textures* &textures, Sprites* &sprites, Animations* &animations);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

