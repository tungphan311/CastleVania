#include "Candle.h"

Candle::Candle(int _state): GameObject()
{
	nx = -1;
	//destroy = false;
	//itemInside = 0;
	AddAnimation(BIG_CANDLE_ANI);
	AddAnimation(SMALL_CANDLE_ANI);
	AddAnimation(CANDLE_DESTROY_ANI);
	AddAnimation(SMALL_CANDLE_FREEZE_ANI);
	AddAnimation(CANDLE_INACTIVE_ANI);

	SetState(_state);
}

void Candle::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_CANDLE, BIG_CANDLE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SMALL_CANDLE, SMALL_CANDLE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_EFFECT, EFFECT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);
	LPDIRECT3DTEXTURE9 texSmallCandle = textures->Get(ID_TEX_SMALL_CANDLE);
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(CANDLE_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == (SPRITES + 2))
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texCandle);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texSmallCandle);
			else if (resources[i][1] == 3)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texEffect);
		}
		else if (resources[i][0] == (ANIMATION + 2))
		{
			ani = new Animation(100);
			for (int j = 2; j < resources[i].size(); j++)
				ani->Add(resources[i][j]);
			animations->Add(resources[i][1], ani);
		}
	}
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (isFreeze && state != CANDLE_DESTROY)
	{
		if (state == SMALL_CANDLE)
			SetState(SMALL_CANDLE_FREEZE);
	}

	if (GetTickCount() - freeze_start > ENEMY_FREE_TIME && state == SMALL_CANDLE_FREEZE)
	{
		SetState(SMALL_CANDLE);
		isFreeze = false;
	}

	if (state == CANDLE_DESTROY && GetTickCount() - timer > 300)
	{
		SetState(CANDLE_INACTIVE);
		destroy = false;
	}
}

void Candle::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
}

void Candle::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case CANDLE_DESTROY:
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case CANDLE_INACTIVE:
		isVisible = false;
		break;

	default:
		break;
	}
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == BIG_CANDLE) {
		right = x + BIG_CANDLE_BBOX_WIDTH;
		bottom = y + BIG_CANDLE_BBOX_HEIGHT;
	}
	else if (state == CANDLE_DESTROY || state == CANDLE_INACTIVE) 
	{
		right = left;
		bottom = top;
	}
	else if (state == SMALL_CANDLE || state == SMALL_CANDLE_FREEZE)
	{
		right = x + SMALL_CANLDE_BBOX_WIDTH;
		bottom = y + SMALL_CANDLE_BBOX_HEIGHT;
	}
}
