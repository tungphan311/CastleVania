#include "FishMan.h"
#include "Ground.h"


FishMan::FishMan(int nx)
{
	this->nx = nx;
	AddAnimation(FISHMAN_ANI_MOVE);
	AddAnimation(FISHMAN_ANI_SHOT);
	AddAnimation(FISHMAN_ANI_FREEZE);
	AddAnimation(FISHMAN_ANI_JUMP);
	AddAnimation(FISHMAN_ANI_DESTROY);
	AddAnimation(FISHMAN_ANI_INACTIVE);

	SetState(FISHMAN_JUMP);

	fireball = new FireBall();
}


FishMan::~FishMan()
{
}

void FishMan::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_FISH_MAN, FISHMAN_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texFishMan = textures->Get(ID_TEX_FISH_MAN);
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(FISHMAN_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texFishMan);
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

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state == FISHMAN_JUMP)
		checkCollision = false;
	else
		checkCollision = true;

	if (y <= 50 + 80) {
		SetState(FISHMAN_FREEZE);
		vy += FISHMAN_GRAVITY * dt;
	}

	if (isFreeze && state != FISHMAN_DESTROY) {
		SetState(FISHMAN_FREEZE);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(currentState);
			isFreeze = false;
		}
	}

	if (state == FISHMAN_MOVE && GetTickCount() - shotTimer > 3000)
	{
		SetState(FISHMAN_SHOT);
		shotTimer = GetTickCount();
	}
	if (GetTickCount() - shotTimer > 500 && state == FISHMAN_SHOT)
	{
		nx = -nx;
		SetState(FISHMAN_MOVE);
	}

	if (nx > 0 && state == FISHMAN_MOVE)
	{
		if ((x > 6076 && x + FISHMAN_BBOX_WIDTH < 6140) || (x > 6204 && x + FISHMAN_BBOX_WIDTH < 6268))
			vy += FISHMAN_GRAVITY * dt;
	}
	else if (nx < 0 && state == FISHMAN_MOVE)
	{
		if ((x + FISHMAN_BBOX_WIDTH < 6140 && x > 6076) || (x + FISHMAN_BBOX_WIDTH < 6268 && x > 6204))
			vy += FISHMAN_GRAVITY * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (checkCollision)
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

		x += dx;
		y += dy;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*> (e->obj))
			{
				if (ny != 0) vy = 0;
				
				if (state == FISHMAN_FREEZE)
				{
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.46f;

					SetState(FISHMAN_MOVE);
					shotTimer = GetTickCount();
				}
				
				if (e->nx != 0) x += dx;
			}
			else {
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.46f;
			}		
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == FISHMAN_DESTROY && GetTickCount() - timer > 300)
	{
		SetState(FISHMAN_INACTIVE);
		destroy = false;
	}

	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
	if (x > cam.x + SCREEN_WIDTH || x + FISHMAN_BBOX_WIDTH < cam.x || y > 390)
	{
		isVisible = false;
	}
}

void FishMan::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void FishMan::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case FISHMAN_MOVE:
		if (nx > 0) {
			vx = FISHMAN_SPEED;
		}
		else if (nx < 0) {
			vx = -FISHMAN_SPEED;
		}
		break;

	case FISHMAN_SHOT:
		vx = 0;
		vy = 0;
		timer = GetTickCount();
		break;

	case FISHMAN_FREEZE:
		vx = 0;
		vy = 0;
		break;

	case FISHMAN_JUMP:
		vx = 0;
		vy = -FISHMAN_JUMP_SPEED;
		break;

	case FISHMAN_DESTROY:
		vx = 0;
		vy = 0;
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case FISHMAN_INACTIVE:
		isVisible = false;
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void FishMan::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == FISHMAN_INACTIVE)
	{
		right = left;
		bottom = top;
	}
	right = left + FISHMAN_BBOX_WIDTH;
	bottom = top + FISHMAN_BBOX_HEIGHT;
}
