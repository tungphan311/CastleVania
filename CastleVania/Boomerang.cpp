#include "Boomerang.h"
#include "Simon.h"
#include "Zombie.h"
#include "Candle.h"
#include "Leopard.h"
#include "Bat.h"
#include "Item.h"
#include "Boss.h"
#include "FishMan.h"

Boomerang::Boomerang(): SubWeapon()
{
	isChangeDirection = false;

	AddAnimation(BOOMERANG_ANI_THROW);
	AddAnimation(BOOMERANG_ANI_INACTIVE);

	SetState(BOOMERANG_INACTIVE);
}


Boomerang::~Boomerang()
{
}

void Boomerang::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BOOMERANG, BOOMERANG_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBoomerang = textures->Get(ID_TEX_BOOMERANG);
	LPANIMATION ani;	

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(BOOMERANG_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texBoomerang);
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

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	x += dx;

	if (vx > 0 && x > posX + 300 && !isChangeDirection) {
		vx = -vx;
		isChangeDirection = true;
	}
		
	if (vx < 0 && x < posX - 300 && !isChangeDirection) {
		vx = -vx;
		isChangeDirection = true;
	}

	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);

		if (dynamic_cast<Simon*> (obj))
		{
			Simon *e = dynamic_cast<Simon*> (obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
				if (isChangeDirection) {
					//SetState(BOOMERANG_INACTIVE);
					isVisible = false;
				}


		}
		if (dynamic_cast<Zombie*> (obj))
		{
			Zombie *e = dynamic_cast<Zombie*> (obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				e->SetState(ZOMBIE_DESTROY);
			}
		}
		else if (dynamic_cast<Leopard*> (obj))
		{
			Leopard *e = dynamic_cast<Leopard*> (obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				e->SetState(LEOPARD_DESTROY);
			}
		}
		else if (dynamic_cast<Bat*> (obj))
		{
			Bat *e = dynamic_cast<Bat*> (obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				e->SetState(BAT_DESTROY);
			}
		}
		else if (dynamic_cast<Candle*> (obj))
		{
			Candle *e = dynamic_cast<Candle*> (obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				e->SetState(CANDLE_DESTROY);
			}
		}
		else if (dynamic_cast<FishMan*>(obj))
		{
			FishMan *e = dynamic_cast<FishMan*>(obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				e->SetState(FISHMAN_DESTROY);
			}
		}
		else if (dynamic_cast<Boss*>(obj))
		{
			Boss *e = dynamic_cast<Boss*>(obj);

			float l, t, r, b;
			e->GetBoundingBox(l, t, r, b);

			if (CheckCollision(l, t, r, b) == true)
			{
				if (e->HP > 0)
				{
					e->HP -= 2;
				}
				else
					e->SetState(BOSS_DIE);
			}
		}
	}
}

void Boomerang::Render()
{
	animations[state]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Boomerang::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case BOOMERANG_THROW:
		if (nx > 0)
			vx = BOOMERANG_FLY_SPEED;
		else if (nx < 0)
			vx = -BOOMERANG_FLY_SPEED;
		vy = 0;
		break;

	case BOOMERANG_INACTIVE:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

bool Boomerang::CheckCollision(float left, float top, float right, float bottom)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	return GameObject::SweptAABBExtend(l, t, r, b, left, top, right, bottom);
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BOOMERANG_BBOX_WIDTH;
	bottom = top + BOOMERANG_BBOX_HEIGHT;
}
