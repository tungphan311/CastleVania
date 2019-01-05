#include "Whip.h"
#include "Candle.h"
#include "Item.h"
#include "Zombie.h"
#include "Leopard.h"
#include "Bat.h"

Whip::Whip(): GameObject()
{
	AddAnimation(NORMAL_WHIP_ANI);
	AddAnimation(SHORT_CHAIN_ANI);
	AddAnimation(LONG_CHAIN_ANI);

	SetState(NORMAL_WHIP);
}

void Whip::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_WHIP, WHIP_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(WHIP_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texWhip);
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

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Whip::Render()
{
	animations[state]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Whip::SetWhipPosition(D3DXVECTOR3 simonPos, bool isStand)
{
	simonPos.x -= 90.0f;
	if (isStand == false)
		simonPos.y += 11.0f;
	else
		simonPos.y -= 2.0f;

	SetPosition(simonPos.x, simonPos.y);
}

bool Whip::CheckCollision(float left, float top, float right, float bottom)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	return GameObject::SweptAABBExtend(l, t, r, b, left, top, right, bottom);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y + 16;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (state == NORMAL_WHIP || state == SHORT_CHAIN) {
		if (nx < 0)
		{
			left = x + 38;
			right = left + WHIP_BBOX_WIDTH;
		}
		else if (nx > 0)
		{
			left = 202 - WHIP_BBOX_WIDTH + x;
			right = left + WHIP_BBOX_WIDTH;
		}
	}

	else if (state == LONG_CHAIN) {
		if (nx < 0) {
			left = x + 6;
			right = left + LONG_CHAIN_BBOX_WIDTH;
		}
		else if (nx > 0) {
			left = 234 - LONG_CHAIN_BBOX_WIDTH + x;
			right = left + LONG_CHAIN_BBOX_WIDTH;
		}
	}
}



