#include "Boss.h"



Boss::Boss()
{
	nx = -1;
	ny - 1;
	active = false;
	isStop = false;	// true: stop  || false: attack
	isAttack = false;
	HP = 2;

	AddAnimation(BOSS_ANI_INACTIVE);
	AddAnimation(BOSS_ANI_FLY);
	AddAnimation(BOSS_ANI_STOP);
	AddAnimation(BOSS_ANI_FREEZE);
	AddAnimation(BOSS_ANI_ATTACK);
	AddAnimation(BOSS_ANI_ATTACK_STRAIGHT);
	AddAnimation(BOSS_ANI_DIE);
	AddAnimation(BOSS_ANI_DISAPPEAR);
	
	SetState(BOSS_INACTIVE);
}


Boss::~Boss()
{
}

void Boss::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BOSS, BOSS_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOSS_DIE, BOSS_DIE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBoss = textures->Get(ID_TEX_BOSS);
	LPDIRECT3DTEXTURE9 texBossDie = textures->Get(ID_TEX_BOSS_DIE);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(BOSS_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texBoss);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texBossDie);
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

void Boss::Update(DWORD dt, Simon * simon)
{
	GameObject::Update(dt);

	if (active)
		vy -= BOSS_GRAVITY* 10 * dt;

	if (isFreeze && state != BOSS_DIE) {
		SetState(BOSS_FREEZE);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(currentState);
			isFreeze = false;
		}
	}

	if (active) {
		if (!isFreeze)
		{
			x += dx;
			y += dy;
		}
		SetState(BOSS_FLY);
		if (y > 130 && state == BOSS_FLY) {
			SetState(BOSS_STOP);	
			isStop = true;
		}

		if (state == BOSS_STOP && stopTimer > 1500)
		{
			float sx, sy;
			simon->GetPosition(sx, sy);

			nx = (sx - x > 0) ? 1 : -1;

			if (sx == x) {
				SetState(BOSS_ATTACK_STRAIGHT);
			}
			else
			{
				int distanceX = (int)abs(sx - x);
				int distanceY = (int)abs(sy - y);
				if (!isAttack) 
					attackTimer = GetTickCount();
				SetState(BOSS_ATTACK);
			}
			stopTimer = 0;
			isStop = false;
		}	


		float camL = 5628 - SCREEN_WIDTH;	// cammera left
		float camR = 5628.0f;				// camera right

		if(vy > 0 && y > 270 + 80)
		{
			ny = 1;
			vy = -BOSS_SPEED_X_SLOW;
		}
		if (vy < 0 && y < 50 + 80 ) {
			ny = -1;
			SetState(BOSS_STOP);
			vy = 0;
		}
		if (x < camL && vx <0)
		{
			nx = -nx;
			vx = BOSS_SPEED_X_SLOW;
		}
		if (x + 96 > camR && vx > 0)
		{
			nx = -nx;
			vx = -BOSS_SPEED_X_SLOW;
		}

		stopTimer += dt;
	}

	if (HP <= 0)
	{
		HP = 0;
		SetState(BOSS_DIE);
	}

	if (state == BOSS_DIE && GetTickCount() - timer > 300)
	{
		SetState(BOSS_DISAPPEAR);
		destroy = false;
	}
}

void Boss::Render()
{
	animations[state]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Boss::SetState(int state, float a)
{
	this->state = state;

	switch (state)
	{
	case BOSS_INACTIVE:
		vx = 0;
		vy = 0;
		SetPosition(5336, -4 + 80);
		break;

	case BOSS_FLY:
		if (nx > 0)
			vx = BOSS_SPEED_X_SLOW;
		else if (nx < 0)
			vx = -BOSS_SPEED_X_SLOW;
		if (ny > 0)
			vy = -BOSS_SPEED_X_FAST;
		else if (ny < 0)
			vy = BOSS_SPEED_Y;
		break;

	case BOSS_ATTACK: 
		isAttack = true;
		if (nx > 0)
			vx = BOSS_SPEED_X_SLOW;
		else if (nx < 0)
			vx = -BOSS_SPEED_X_SLOW;
		if (ny > 0)
			vy = -BOSS_SPEED_X_FAST*1.5;
		else if (ny < 0)
			vy = BOSS_SPEED_Y;
		break;
		
	case BOSS_ATTACK_STRAIGHT:
		vx = 0;
		vy = BOSS_SPEED_X_FAST;
		break;

	case BOSS_STOP:
		if (!isStop)
		{
			stopTimer = 0;
			vx = 0;
			vy = 0;
		}		
		break;

	case BOSS_FREEZE:
		vx = 0;
		vy = 0;
		break;

	case BOSS_DIE:
		vx = 0;
		vy = 0;
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case BOSS_DISAPPEAR:
		isVisible = false;
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 20;
	top = y;
	right = left + BOSS_BBOX_WIDTH;
	bottom = top + BOSS_BBOX_HEIGHT;
}

