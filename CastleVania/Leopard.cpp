#include "Leopard.h"
#include "Ground.h"
#include "SceneManager.h"

Leopard::Leopard(int order): GameObject()
{
	this->order = order;
	isJump = false;
	allowJump = false;
	checkCollision = true;

	AddAnimation(LEOPARD_ANI_SLEEP);
	AddAnimation(LEOPARD_ANI_JUMP);
	AddAnimation(LEOPARD_ANI_DESTROY);
	AddAnimation(LEOPARD_ANI_RUN);
	AddAnimation(LEOPARD_ANI_FREEZE_JUMP);
	AddAnimation(LEOPARD_ANI_FREEZE_RUN);
	AddAnimation(LEOPARD_ANI_INACTIVE);

	SetState(LEOPARD_SLEEP);
}


Leopard::~Leopard()
{
}

void Leopard::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_LEOPARD, LEOPARD_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texLeopard = textures->Get(ID_TEX_LEOPARD);
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(LEOPARD_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == (SPRITES + 3))
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texLeopard);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texEffect);
		}
		else if (resources[i][0] == (ANIMATION + 3))
		{
			ani = new Animation(100);
			for (int j = 2; j < resources[i].size(); j++)
				ani->Add(resources[i][j]);
			animations->Add(resources[i][1], ani);
		}
	}
}

void Leopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();

	if (state == LEOPARD_SLEEP)
		vy = 0;
	else
		vy += LEOPARD_GRAVITY * dt;

	if (order == 1)
	{
		if (direction == -1)
		{
			if (allowJump == true && isJump == false)
			{
				SetState(LEOPARD_JUMP);
				vy += LEOPARD_GRAVITY * dt;
			}
		}
		else if (direction == 1)
		{
			if (cam.x <= 1275 && state == LEOPARD_SLEEP)
			{
				SetState(LEOPARD_RUN);
			}
			if (state == LEOPARD_RUN && (x + LEOPARD_BBOX_WIDTH >= 1472) && isJump == false)
			{
				checkCollision = false;
				SetState(LEOPARD_JUMP);
			}
			if (y > posY + 10)
				checkCollision = true;
		}
	}
	else if (order == 2)
	{
		if (direction == -1)
		{
			if (cam.x >= 1392)
				SetState(LEOPARD_RUN);
			if (state == LEOPARD_RUN && x <= 1494 && isJump == false)
			{
				checkCollision = false;
				SetState(LEOPARD_JUMP);
			}

			if (y > posY + 10)
				checkCollision = true;
		}
		else if (direction == 1)
		{
			if (cam.x <= 1660 && state == LEOPARD_SLEEP)
				SetState(LEOPARD_JUMP);
			if (state == LEOPARD_RUN)
				isJump = false;
			if (x <= 1856 && isJump == false && state == LEOPARD_RUN)
			{
				checkCollision = false;
				SetState(LEOPARD_JUMP);
			}
		}
	}
	else if (order == 3) {
		if (direction == -1)
		{
			if (cam.x >= 1536 && isJump == false) {
				SetState(LEOPARD_JUMP);
			}
		}
		else if (direction == 1)
		{
			if (cam.x <= 1760 && state == LEOPARD_SLEEP)
				SetState(LEOPARD_RUN);
			if (state == LEOPARD_RUN && (x + LEOPARD_BBOX_WIDTH >= 2048) && isJump == false)
			{
				checkCollision = false;
				SetState(LEOPARD_JUMP);
			}
			if (y > posY + 10)
				checkCollision = true;
		}
	}

	if (isFreeze && state != LEOPARD_DESTROY) {
		if (currentState == LEOPARD_JUMP)
			SetState(LEOPARD_FREEZE_JUMP);
		else if (currentState == LEOPARD_RUN)
			SetState(LEOPARD_FREEZE_RUN);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(currentState);
			isFreeze = false;
		}
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

		x += dx;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i]; 

			if (dynamic_cast<Ground*> (e->obj))
			{
				if (nx != 0) x += dx;
				if (state == LEOPARD_JUMP && y > posY)
				{
					SetState(LEOPARD_RUN);
					//isJump = false;
				}
				if (ny != 0) vy = 0;					
			}
			else {
				x += dx;	
				y += min_ty * dy + ny * 0.4f;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == LEOPARD_DESTROY && GetTickCount() - timer > 300)
	{
		SetState(LEOPARD_INACTIVE);
		destroy = false;
	}
	
	if ((x < cam.x || x + LEOPARD_BBOX_WIDTH > cam.x + SCREEN_WIDTH) && (state == LEOPARD_JUMP || state == LEOPARD_RUN))
		isVisible = false;
}

void Leopard::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void Leopard::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case LEOPARD_SLEEP:
		vy = 0;
		vx = 0;
		break;

	case LEOPARD_JUMP:
		if (nx > 0) {
			vx = LEOPARD_JUMP_SPEED*0.8;
			vy = -LEOPARD_JUMP_SPEED;
		}
		else if (nx < 0) {
			vx = -LEOPARD_JUMP_SPEED*0.8;
			vy = -LEOPARD_JUMP_SPEED;
		}
		isJump = true;
		break;

	case LEOPARD_RUN:
		if (isJump) {
			nx = -nx;
		}
		if (nx > 0) {
			vx = LEOPARD_RUN_SPEED;
		}
		else if (nx < 0)
			vx = -LEOPARD_RUN_SPEED;
		vy = 0;
		
		break;

	case LEOPARD_FREEZE_JUMP:
	case LEOPARD_FREEZE_RUN:
		vx = 0;
		vy = 0;
		break;

	case LEOPARD_DESTROY:
		vx = 0;
		vy = 0;
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case LEOPARD_INACTIVE:
		isVisible = false;
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void Leopard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == LEOPARD_INACTIVE)
	{
		right = left;
		bottom = top;
	}
	else
	{
		right = x + LEOPARD_BBOX_WIDTH;
		bottom = y + LEOPARD_BBOX_HEIGHT;
	}
}
