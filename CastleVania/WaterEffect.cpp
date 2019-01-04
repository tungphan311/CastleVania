#include "WaterEffect.h"



WaterEffect::WaterEffect(int index): GameObject()
{
	AddAnimation(WATER_EFFECT_ANI);
	SetState(WATER_EFFECT);
	SetIndex(index);
}


WaterEffect::~WaterEffect()
{
}

void WaterEffect::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_WATER_EFFECT, WATER_EFFECT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWaterEffect = textures->Get(ID_TEX_WATER_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(WATER_EFFECT_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texWaterEffect);
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

void WaterEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += WATER_GRAVITY * dt;

	x += dx;
	y += dy;

	if (y >= 340)
	{
		isVisible = false;
	}

	DebugOut(L"Water Speed y: %f\n", vy);
}

void WaterEffect::Render()
{
	animations[state]->Render(-1, x, y);
}

void WaterEffect::SetIndex(int index)
{
	this->index = index;

	switch (index)
	{
	case 0:
		vx = -WATER_SPEED_X;
		vy = -WATER_SPEED_Y;
		break;

	case 1:
		vx = 0;
		vy = -WATER_SPEED_Y;
		break;

	case 2:
		vx = WATER_SPEED_X;
		vy = -WATER_SPEED_Y;
		break;

	default:
		break;
	}
}

WaterEffects::WaterEffects()
{
	for (int i = 0; i < 3; i++)
	{
		LPWATEREFFECT water_effect = new WaterEffect(i);
		effects.push_back(water_effect);
	}
	isDone = false;
}

void WaterEffects::Update(DWORD dt)
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
		if (effects[i]->isVisible == false)
			count++;
	}
	if (count == effects.size())
		isDone = true;
}

void WaterEffects::Render()
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->isVisible == false)
			continue;
		effects[i]->Render();
	}
}

void WaterEffects::SetPosition(float x, float y)
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->SetPosition(x + 6*i, y);
	}
}
