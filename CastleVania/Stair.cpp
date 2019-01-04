#include "Stair.h"



Stair::Stair(int state, int nx)
{
	SetState(state);
	this->nx = nx;	// -1: left || 1: right
}

void Stair::Render()
{
	//animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void Stair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == UP_STAIR) {
		right = left + STAIR_BBOX_WIDTH;
		bottom = top + STAIR_BBOX_HEIGHT/4;
	}
	if (state == DOWN_STAIR) {
		right = left + STAIR_BBOX_WIDTH;
		bottom = top + STAIR_BBOX_HEIGHT;
	}
}

