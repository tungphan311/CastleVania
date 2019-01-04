#include "FireBall.h"



FireBall::FireBall()
{
	AddAnimation(FIREBALL_ANI);
	AddAnimation(FIREBALL_ANI_FREEZE);
	SetState(FIREBALL);
}


FireBall::~FireBall()
{
	
}

void FireBall::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_FIRE_BALL, FIREBALL_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texFireBall = textures->Get(ID_TEX_FIRE_BALL);
	LPANIMATION ani = new Animation(100);


	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(FIREBALL_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texFireBall);
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

void FireBall::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += dx;

	GameObject::Update(dt);
	
	if (isFreeze && !isVisible) {
		SetState(FIREBALL_FREEZE);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(currentState);
			isFreeze = false;
		}
	}
	
	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
	if (x > cam.x + SCREEN_WIDTH || x + FIREBALL_BBOX_WIDTH < cam.x)
	{
		isVisible = false;
	}
}

void FireBall::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case FIREBALL:
		if (nx < 0) vx = -FIREBALL_SPEED;
		else if (nx > 0) vx = FIREBALL_SPEED;
		//vy = 0;
		break;

	case FIREBALL_FREEZE:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void FireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}
