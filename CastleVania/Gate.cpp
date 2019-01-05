#include "Gate.h"



Gate::Gate(int type): GameObject()
{
	this->type = type; 

	if (this->type == GATE_2)
	{
		AddAnimation(GATE_ANI_CLOSE);
		AddAnimation(GATE_ANI_OPENING);
		AddAnimation(GATE_ANI_OPENED);
		AddAnimation(GATE_ANI_INACTIVE);

		SetState(GATE_INACTIVE);
	}	
}

Gate::~Gate()
{
}

void Gate::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_GATE, GATE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texGate = textures->Get(ID_TEX_GATE);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(GATE_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == (SPRITES + 1))
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texGate);
		}
		else if (resources[i][0] == (ANIMATION + 1))
		{
			ani = new Animation(100);
			for (int j = 2; j < resources[i].size(); j++)
				ani->Add(resources[i][j]);
			animations->Add(resources[i][1], ani);
		}
	}
}

void Gate::Render()
{
	if (type == GATE_2)
		animations[state]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Gate::SetState(int state)
{
	GameObject::SetState(state);

	if (state == GATE_OPENING)
	{
		animations[state]->ResetAnimation();
	}
}

void Gate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	right = x + 3;
	top = y + 60;
	left = right - GATE_BBOX_WIDTH;
	bottom = top + GATE_BBOX_HEIGHT;
}

