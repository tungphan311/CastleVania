#include "Axe.h"
#include "Candle.h"
#include "Zombie.h"
#include "Leopard.h"
#include "Bat.h"
#include "Item.h"
#include "Boss.h"
#include "FishMan.h"

Axe::Axe(): SubWeapon()
{
	isChangeDirection = false;
	
	AddAnimation(AXE_ANI_THROW);
	AddAnimation(AXE_ANI_INACTIVE);

	SetState(AXE_INACTIVE);
}

Axe::~Axe()
{
}

void Axe::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_AXE, AXE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_AXE);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(AXE_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texAxe);
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

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += AXE_GRAVITY * dt;

	x += dx;
	y += dy;

	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
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
				if (e->HP > 1)
				{
					if (!loseHP) {
						e->HP -= 2;
						loseHP = true;
					}
				}
				else if (e->HP == 1)
				{
					if (!loseHP)
					{
						e->HP -= 1;
						loseHP = true;
					}
				}
				else if (e->HP <= 0)
					e->SetState(BOSS_DIE);
			}
		}
	}

	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
	if (x > cam.x + SCREEN_WIDTH || x + AXE_BBOX_WIDTH < cam.x || y > SCREEN_HEIGHT)
		isVisible = false;
}

void Axe::Render()
{
	animations[state]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Axe::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case AXE_THROW:
		if (nx > 0)
			vx = AXE_FLY_SPEED;
		else if (nx < 0)
			vx = -AXE_FLY_SPEED;
		vy = -AXE_FLY_SPEED*1.5f;
		//animations[state]->ResetAnimation();
		break;

	default:
		break;
	}
}

bool Axe::CheckCollision(float left, float top, float right, float bottom)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	return GameObject::SweptAABBExtend(l, t, r, b, left, top, right, bottom);
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + AXE_BBOX_WIDTH;
	bottom = top + AXE_BBOX_HEIGHT;
}
