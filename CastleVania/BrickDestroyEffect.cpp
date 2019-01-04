#include "BrickDestroyEffect.h"



BrickDestroyEffect::BrickDestroyEffect(int index): GameObject()
{
	timer = 0;
	isDone = false;
	AddAnimation(BRICK_DESTROY_EFFECT_ANI);
	SetState(BRICK_DESTROY_EFFECT);
	SetIndex(index);
}


BrickDestroyEffect::~BrickDestroyEffect()
{
}

void BrickDestroyEffect::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BRICK_DESTROY, BRICK_DESTROY_EFFECT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBrickDestroy = textures->Get(ID_TEX_BRICK_DESTROY);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(BRICK_DESTROY_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texBrickDestroy);
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

void BrickDestroyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	timer += dt;

	vy += EFFECT_GRAVITY * dt;

	x += dx;
	y += dy;

	if (timer > 300) {
		isVisible = false;
		isDone = true;
	}
}

void BrickDestroyEffect::Render()
{
	animations[state]->Render(nx, x, y);
}

void BrickDestroyEffect::SetIndex(int index)
{
	this->index = index;

	switch (index)
	{
	case 0:
		vx = -BRICK_DESTROY_X;
		vy = -BRICK_DESTROY_Y;
		break;

	case 1:
		vx = -BRICK_DESTROY_X / 4;
		vy = -BRICK_DESTROY_Y / 4;
		break;

	case 2:
		vx = BRICK_DESTROY_X / 4;
		vy = -BRICK_DESTROY_Y / 4;
		break;

	case 3:
		vx = BRICK_DESTROY_X;
		vy = -BRICK_DESTROY_Y;
		break;

	default:
		break;
	}
}

BrickEffects::BrickEffects()
{
	for (int i = 0; i < 4; i++)
	{
		LPBRICKDESTROYEFFECT brick_effect = new BrickDestroyEffect(i);
		effects.push_back(brick_effect);
	}
	isDone = false;
}

void BrickEffects::Update(DWORD dt)
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->isVisible == false)
			continue;
		effects[i]->Update(dt);
	}
	int count = 0;
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->isDone == true)
			count++;
	}
	if (count == effects.size())
		isDone = true;
}

void BrickEffects::Render()
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->isVisible == false)
			continue;
		effects[i]->Render();
	}
}

void BrickEffects::SetPosition(float x, float y)
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->SetPosition(x + 6 *i, y + 6*i);
	}
}
