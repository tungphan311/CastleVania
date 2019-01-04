#include "Zombie.h"
#include "Ground.h"
#include "Whip.h"


Zombie::Zombie(int nx): GameObject()
{
	this->nx = nx;
	//destroy = false;

	AddAnimation(ZOMBIE_ANI_MOVING);
	AddAnimation(ZOMBIE_ANI_FREEZE);
	AddAnimation(ZOMBIE_ANI_DESTROY);
	AddAnimation(ZOMBIE_ANI_INACTIVE);

	SetState(ZOMBIE_MOVE);
}

void Zombie::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_ZOMBIE, ZOMBIE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texZombie = textures->Get(ID_TEX_ZOMBIE);
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(ZOMBIE_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texZombie);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texEffect);
		}
		else if (resources[i][0] == ANIMATION)
		{
			ani = new Animation(100);
			for (int j = 2; j < resources[i].size(); j++)
				ani->Add(resources[i][j]);
			animations->Add(resources[i][1], ani);
		}
	}
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (isFreeze == false)
		vy += SIMON_GRAVITY * dt;

	if (isFreeze && state != ZOMBIE_DESTROY) {
		SetState(ZOMBIE_FREEZE);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(ZOMBIE_MOVE);
			isFreeze = false;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*> (e->obj))
			{				
				y += min_ty * dy + ny * 0.4f;
				x += min_tx * dx + nx * 0.4f;

				if (ny != 0) vy = 0;
			}
		}	
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == ZOMBIE_DESTROY && GetTickCount() - timer > 300)
	{
		SetState(ZOMBIE_INACTIVE);
		destroy = false;
	}

	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();

	if (x < cam.x || x > cam.x + SCREEN_WIDTH + 160)
		isVisible = false;
}

void Zombie::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void Zombie::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case ZOMBIE_MOVE:
		if (nx == 1) {
			vx = ZOMBIE_MOVE_SPEED_X;
		}
		else if (nx == -1) {
			vx = -ZOMBIE_MOVE_SPEED_X;
		}		
		break;

	case ZOMBIE_FREEZE:
		vx = 0;
		break;

	case ZOMBIE_DESTROY:
		vx = 0;
		vy = 0;
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case ZOMBIE_INACTIVE:
		isVisible = false;
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 4;
	top = y;
	if (state == ZOMBIE_INACTIVE)
	{
		right = left;
		bottom = top;
	}
	else
	{
		right = x + ZOMBIE_BBOX_WIDTH;
		bottom = y + ZOMBIE_BBOX_HEIGHT;
	}	
}


