#include "Dagger.h"
#include "Candle.h"
#include "Item.h"
#include "Zombie.h"
#include "Leopard.h"
#include "Bat.h"
#include "FishMan.h"
#include "Boss.h"

Dagger::Dagger(): SubWeapon()
{
	vx = DAGGER_SPEED;
	AddAnimation(DAGGER_ANI);
	isVisible = false;

	SetState(DAGGER_STATE);
}

void Dagger::Render()
{
	if (isVisible == true)
	{
		animations[state]->Render(-nx, x, y);
		RenderBoundingBox();
	}
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isVisible == true)
	{
		if (nx < 0) vx = -DAGGER_SPEED;
		else if (nx > 0)
			vx = DAGGER_SPEED;
		//vy = 0;

		x += dx;

		GameObject::Update(dt);

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);

			if (dynamic_cast<Candle*> (obj))
			{
				Candle *e = dynamic_cast<Candle*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;
					e->SetState(CANDLE_DESTROY);
				}
			}
			else if (dynamic_cast<Zombie*> (obj))
			{
				Zombie *e = dynamic_cast<Zombie*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;
					e->SetState(ZOMBIE_DESTROY);
				}
			}
			else if (dynamic_cast<Leopard*> (obj))
			{
				Leopard *e = dynamic_cast<Leopard*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;
					e->SetState(LEOPARD_DESTROY);
				}
			}
			else if (dynamic_cast<Bat*> (obj))
			{
				Bat *e = dynamic_cast<Bat*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;
					e->SetState(BAT_DESTROY);
				}
			}
			else if (dynamic_cast<FishMan*> (obj))
			{
				FishMan *e = dynamic_cast<FishMan*> (obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;
					e->SetState(FISHMAN_DESTROY);
				}
			}
			else if (dynamic_cast<Boss*>(obj))
			{
				Boss *e = dynamic_cast<Boss*>(obj);

				float l, t, r, b;
				e->GetBoundingBox(l, t, r, b);

				if (CheckCollision(l, t, r, b)) {
					isVisible = false;

					if (e->HP > 0)
						e->HP -= 1;
					else
						e->SetState(BOSS_DIE);
				}
			}
		}

		D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
		if (x > cam.x + SCREEN_WIDTH || x + DAGGER_BBOX_WIDTH < cam.x)
		{
			isVisible = false;
		}
	}	
}

void Dagger::SetDaggerPosition(D3DXVECTOR3 simonPos, bool isStand)
{
	if (isStand == false)
		simonPos.y += 20.0f;
	else
		simonPos.y += 10.0f;

	SetPosition(simonPos.x, simonPos.y);
}

bool Dagger::CheckCollision(float left, float top, float right, float bottom)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	return GameObject::SweptAABBExtend(l, t, r, b, left, top, right, bottom);
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}


