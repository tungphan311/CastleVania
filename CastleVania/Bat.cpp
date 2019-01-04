 #include "Bat.h"



Bat::Bat(): GameObject()
{
}

Bat::Bat(int nx, float y)
{
	posY = y;
	this->nx = nx;
	
	AddAnimation(BAT_ANI_FLY);
	AddAnimation(BAT_ANI_FREEZE);
	AddAnimation(BAT_ANI_DESTROY);
	AddAnimation(BAT_ANI_INACTIVE);

	SetState(BAT_FLY);
}


Bat::~Bat()
{
}

void Bat::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_BAT, BAT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	
	LPDIRECT3DTEXTURE9 texBat = textures->Get(ID_TEX_BAT);
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(BAT_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texBat);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texEffect);
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

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (isFreeze && state != BAT_DESTROY) {
		SetState(BAT_FREEZE);

		if (GetTickCount() - freeze_start > ENEMY_FREE_TIME)
		{
			SetState(currentState);
			isFreeze = false;
		}
	}

	if (!isFreeze)
	{
		x += dx;
		y += dy;
	}

	if (vy > 0 && y > posY + 20)
	{
		vy = -vy;	
	}
	if (vy < 0 && y < posY - 20) {
		vy = -vy;
	}

	if (state == BAT_DESTROY && GetTickCount() - timer > 300)
	{
		SetState(BAT_INACTIVE);
		destroy = false;
	}

	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
	if (x + BAT_BBOX_WIDTH < cam.x || x > cam.x + SCREEN_WIDTH)
		isVisible = false;
}

void Bat::Render()
{
	animations[state]->Render(nx, x, y);
}

void Bat::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{	
	case BAT_FLY:
		if (nx > 0)
			vx = BAT_SPEED_X;
		else if (nx < 0)
			vx = -BAT_SPEED_X;
		vy = BAT_SPEED_Y;
		break;

	case BAT_FREEZE:
		vx = 0;
		vy = 0;
		break;

	case BAT_DESTROY:
		vx = 0;
		vy = 0;
		if (!destroy)
		{
			destroy = true;
			timer = GetTickCount();
		}
		break;

	case BAT_INACTIVE:
		isVisible = false;
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == BAT_INACTIVE)
	{
		right = left;
		bottom = top;
	}
	else
	{
		right = left + BAT_BBOX_WIDTH;
		bottom = top + BAT_BBOX_HEIGHT;
	}
}
