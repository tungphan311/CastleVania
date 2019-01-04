#include "Ground.h"

Ground::Ground(int state, int bbox_width)
{
	this->bbox_height = 32;
	this->bbox_width = bbox_width;
	AddAnimation(GROUND_ANI);
	AddAnimation(GROUND_2_ANI);
	AddAnimation(GROUND_3_ANI);
	AddAnimation(GROUND_4_ANI);	
	AddAnimation(GROUND_DESTROY_ANI);

	SetState(state);
}

void Ground::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_GROUND_2, GROUND_2_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND_3, GROUND_3_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND_4, GROUND_4_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texGround2 = textures->Get(ID_TEX_GROUND_2);
	LPDIRECT3DTEXTURE9 texGround3 = textures->Get(ID_TEX_GROUND_3);
	LPDIRECT3DTEXTURE9 texGround4 = textures->Get(ID_TEX_GROUND_4);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(GROUND_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == (SPRITES + 2))
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texGround2);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texGround3);
			else if (resources[i][1] == 3)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texGround4);
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

void Ground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state == GROUND_DESTROY && GetTickCount() - timer > 300)
	{
		isVisible = false;
		destroy = false;
	}
}

void Ground::Render()
{
	animations[state]->Render(-1, x, y);
	RenderBoundingBox();
}

void Ground::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case GROUND_DESTROY:
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	default:
		break;
	}
}

void Ground::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + bbox_width;
	bottom = top + bbox_height;
}
