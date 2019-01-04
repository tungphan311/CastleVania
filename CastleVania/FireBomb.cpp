#include "FireBomb.h"
#include "Ground.h"
#include "Zombie.h"
#include "Leopard.h"
#include "Bat.h"
#include "Item.h"
#include "Candle.h"
#include "FishMan.h"
#include "Boss.h"

FireBomb::FireBomb(): SubWeapon()
{
	burn_time = 0;

	AddAnimation(FB_ANI_THROW);
	AddAnimation(FB_ANI_BURN);
	AddAnimation(FB_ANI_INACTIVE);

	SetState(FB_INACTIVE);
}


FireBomb::~FireBomb()
{
}

void FireBomb::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_FIRE_BOMB, FIREBOMB_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texFireBomb = textures->Get(ID_TEX_FIRE_BOMB);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(FIREBOMB_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texFireBomb);
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

void FireBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += FB_GRAVITY * dt;

	if (state == FB_BURN && GetTickCount() - burn_time > FB_BURN_TIME) {
		isVisible = false;
		SetState(FB_INACTIVE);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
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

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*> (e->obj))
			{
				if (e->ny != 0) {
					vy = 0;
					if (state == FB_THROW)
					{
						SetState(FB_BURN);
						burn_time = GetTickCount();
					}
				}
				if (e->nx != 0) x += dx;
			}
			else if (dynamic_cast<Candle*> (e->obj))
			{
				x += dx;
				y += dy;

				Candle *can = dynamic_cast<Candle*>(e->obj);

				can->SetState(CANDLE_DESTROY);
			}
			else {
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (ny != 0) vy = 0;
			}
		}
	}

	if (state == FB_BURN)
	{
		RenderBoundingBox();

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
			else if (dynamic_cast<Candle*>(obj))
			{
				Candle *e = dynamic_cast<Candle*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b) == true)
				{
					e->SetState(CANDLE_DESTROY);
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
			else if (dynamic_cast<FishMan*> (obj))
			{
				FishMan *e = dynamic_cast<FishMan*> (obj);

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
		
}

void FireBomb::Render()
{
	animations[state]->Render(nx, x, y);
}

void FireBomb::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case FB_THROW:
		if (nx > 0)
			vx = FB_FLY_SPEED * 0.75;
		else if (nx < 0)
			vx = -FB_FLY_SPEED * 0.75;
		vy = -FB_FLY_SPEED;
		break;

	case FB_BURN:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

bool FireBomb::CheckCollision(float left, float top, float right, float bottom)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	return GameObject::SweptAABBExtend(l, t, r, b, left, top, right, bottom);
}

void FireBomb::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FB_BBOX_WIDTH;
	bottom = top + FB_BBOX_HEIGHT;
}
	