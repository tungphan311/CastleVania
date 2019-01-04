#include "Item.h"



Item::Item(): GameObject()
{
	vy = ITEM_GRAVITY;

	AddAnimation(LARGE_HEART_ANI);
	AddAnimation(CHAIN_ANI);
	AddAnimation(ITEM_DISAPPEAR_ANI);
	AddAnimation(RED_MONEY_ANI);
	AddAnimation(WHITE_MONEY_ANI);
	AddAnimation(BLUE_MONEY_ANI);
	AddAnimation(FLASH_MONEY_ANI);
	AddAnimation(SMALL_HEART_ANI);
	AddAnimation(CROSS_ANI);
	AddAnimation(DOUBLE_SHOT_ANI);
	AddAnimation(TRIPLE_SHOT_ANI);
	AddAnimation(PORK_CHOP_ANI);
	AddAnimation(DAGGER_ANI);
	AddAnimation(AXE_ANI);
	AddAnimation(FIRE_BOMB_ANI);
	AddAnimation(WATCH_ANI);
	AddAnimation(BALL_ANI);
	AddAnimation(INVISIBILITY_ANI);

	timeAppear = -1;
}

void Item::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
#pragma region __ID_TEX__
	textures->Add(ID_TEX_ITEM_LARGE_HEART, ITEM_LARGE_HEART_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_CHAIN, ITEM_CHAIN_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_DAGGER, ITEM_DAGGER_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_AXE, ITEM_AXE_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_BOOMERANG, ITEM_BOOMERANG_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_CROSS, ITEM_CROSS_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_DOUBLE_SHOT, ITEM_DOUBLE_SHOT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_FIRE_BOMB, ITEM_FIRE_BOMB_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MONEY_BAG, ITEM_MONEY_BAG_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_PORK_CHOP, ITEM_PORK_CHOP_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_TRIPLE_SHOT, ITEM_TRIPLE_SHOT_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_SMALL_HEART, ITEM_SMALL_HEART_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_WATCH, ITEM_WATCH_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_BALL, ITEM_BALL_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_INVISIBILITY, ITEM_INVISIBILITY_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
#pragma endregion

#pragma region __TEXTURES__
	LPDIRECT3DTEXTURE9 texLargeHeart = textures->Get(ID_TEX_ITEM_LARGE_HEART);
	LPDIRECT3DTEXTURE9 texChain = textures->Get(ID_TEX_ITEM_CHAIN);
	LPDIRECT3DTEXTURE9 texDagger = textures->Get(ID_TEX_ITEM_DAGGER);
	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_ITEM_AXE);
	LPDIRECT3DTEXTURE9 texBoomerang = textures->Get(ID_TEX_ITEM_BOOMERANG);
	LPDIRECT3DTEXTURE9 texCross = textures->Get(ID_TEX_ITEM_CROSS);
	LPDIRECT3DTEXTURE9 texDoubleShot = textures->Get(ID_TEX_ITEM_DOUBLE_SHOT);
	LPDIRECT3DTEXTURE9 texFireBomb = textures->Get(ID_TEX_ITEM_FIRE_BOMB);
	LPDIRECT3DTEXTURE9 texMoneyBag = textures->Get(ID_TEX_ITEM_MONEY_BAG);
	LPDIRECT3DTEXTURE9 texPorkChop = textures->Get(ID_TEX_ITEM_PORK_CHOP);
	LPDIRECT3DTEXTURE9 texTripleShot = textures->Get(ID_TEX_ITEM_TRIPLE_SHOT);
	LPDIRECT3DTEXTURE9 texSmallHeart = textures->Get(ID_TEX_ITEM_SMALL_HEART);
	LPDIRECT3DTEXTURE9 texWatch = textures->Get(ID_TEX_ITEM_WATCH);
	LPDIRECT3DTEXTURE9 texBall = textures->Get(ID_TEX_ITEM_BALL);
	LPDIRECT3DTEXTURE9 texInvisibility = textures->Get(ID_TEX_ITEM_INVISIBILITY);
#pragma endregion

	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(ITEM_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			if (resources[i][1] == 1)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texLargeHeart);
			else if (resources[i][1] == 2)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texChain);
			else if (resources[i][1] == 3)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texDagger);
			else if (resources[i][1] == 4)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texAxe);
			else if (resources[i][1] == 5)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texBoomerang);
			else if (resources[i][1] == 6)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texCross);
			else if (resources[i][1] == 7)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texDoubleShot);
			else if (resources[i][1] == 8)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texFireBomb);
			else if (resources[i][1] == 9)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texMoneyBag);
			else if (resources[i][1] == 10)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texPorkChop);
			else if (resources[i][1] == 11)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texSmallHeart);
			else if (resources[i][1] == 12)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texTripleShot);
			else if (resources[i][1] == 13)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texWatch);
			else if (resources[i][1] == 14)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texBall);
			else if (resources[i][1] == 15)
				sprites->Add(resources[i][2], resources[i][3], resources[i][4], resources[i][5], resources[i][6], texInvisibility);
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

void Item::Render()
{
	animations[state]->Render(-1, x, y);
	RenderBoundingBox();
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timeAppear == -1)
		timeAppear = GetTickCount();
	else {
		DWORD now = GetTickCount();

		if (now - timeAppear > ITEM_TIME_DISAPPEAR) {
			isVisible = false;
			return;
		}
	}


	GameObject::Update(dt);

	// Check collision between item and ground (falling on ground)
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

		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) vy = 0;
		DebugOut(L"Item collides ground\n");
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Item::SetItem()
{
	double val = (double)rand()/RAND_MAX;
	if (val < 0.25)
		state = ITEM_SMALL_HEART;
	else if(val < 0.34)
		state = ITEM_DAGGER;
	else if (val < 0.43)
		state = ITEM_LARGE_HEART;
	else if (val < 0.52)
		state = ITEM_CHAIN;
	else if (val < 0.61)
		state = ITEM_RED_MONEY_BAG;
	else if (val < 0.70)
		state = ITEM_WHITE_MONEY_BAG;
	else if (val < 0.79)
		state = ITEM_BLUE_MONEY_BAG;
	else if (val < 0.88)
		state = ITEM_WATCH;
	else if (val < 0.97)
		state = ITEM_FIRE_BOMB;
	else
		state = ITEM_FLASH_MONEY_BAG;
}

void Item::SetItemOnEnemy()
{
	double val = (double)rand() / RAND_MAX;
	
	if (val < 0.5)
		state = ITEM_SMALL_HEART;
	else if (val < 0.15)
		state = ITEM_LARGE_HEART;
	else if (val < 0.15)
		state = ITEM_BLUE_MONEY_BAG;
	else
		state = ITEM_RED_MONEY_BAG;
}

void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case ITEM_LARGE_HEART: // large heart
		right = left + LARGE_HEART_BBOX_WIDTH;
		bottom = top + LARGE_HEART_BBOX_HEIGHT;
		break;
	case ITEM_CHAIN: // chain
		right = left + CHAIN_BBOX_WIDTH;
		bottom = top + CHAIN_BBOX_HEIGHT;
		break;
	case ITEM_DAGGER: // dagger
		right = left + DAGGER_BBOX_WIDTH;
		bottom = top + DAGGER_BBOX_HEIGHT;
		break;
	case ITEM_DISAPPEAR:
		right = left;
		bottom = top;
		break;
	case ITEM_AXE:
		right = left + AXE_BBOX_WIDTH;
		bottom = top + AXE_BBOX_HEIGHT;
		break;

	case ITEM_BLUE_MONEY_BAG:
	case ITEM_WHITE_MONEY_BAG:
	case ITEM_RED_MONEY_BAG:
	case ITEM_FLASH_MONEY_BAG:
		right = left + MONEY_BAG_BBOX_WIDTH;
		bottom = top + MONEY_BAG_BBOX_HEIGHT;
		break;

	case ITEM_CROSS:
		right = left + CROSS_BBOX_WIDTH;
		bottom = top + CROSS_BBOX_HEIGHT;
		break;

	case ITEM_DOUBLE_SHOT:
		right = left + DOUBLE_SHOT_BBOX_WIDTH;
		bottom = top + DOUBLE_SHOT_BBOX_HEIGHT;
		break;

	case ITEM_FIRE_BOMB:
		right = left + FIRE_BOMB_BBOX_WIDTH;
		bottom = top + FIRE_BOMB_BBOX_HEIGHT;
		break;

	case ITEM_PORK_CHOP:
		right = left + PORK_CHOP_BBOX_WIDTH;
		bottom = top + PORK_CHOP_BBOX_HEIGHT;
		break;

	case ITEM_SMALL_HEART:
		right = left + SMALL_HEART_BBOX_WIDTH;
		bottom = top + SMALL_HEART_BBOX_HEIGHT;
		break;

	case ITEM_TRIPLE_SHOT:
		right = left + TRIPLE_SHOT_BBOX_WIDTH;
		bottom = top + TRIPLE_SHOT_BBOX_HEIGHT;
		break;

	case ITEM_WATCH:
		right = left + WATCH_BBOX_WIDTH;
		bottom = top + WATCH_BBOX_HEIGHT;
		break;

	case ITEM_BALL:
		right = left + BALL_BBOX_WIDTH;
		bottom = top + BALL_BBOX_HEIGHT;
		break;

	case ITEM_INVISIBILITY:
		right = left + INVISIBILITY_BBOX_WIDTH;
		bottom = top + INVISIBILITY_BBOX_HEIGHT;
		break;

	default:
		break;
	}
}
