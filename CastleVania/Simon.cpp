#include "Simon.h"
#include "Candle.h"
#include "Ground.h"
#include "Item.h"
#include "Stair.h"
#include "Leopard.h"
#include "Bat.h"
#include "Gate.h"
#include "Effect.h"
#include "FishMan.h"
#include "Boss.h"

Simon::Simon(): GameObject()
{
	isStand = TRUE;
	isOnStair = FALSE;
	untouchable = FALSE;
	isHitGate = FALSE;
	isHitCross = FALSE;
	allowUseSubWeapon = TRUE;
	whipState = 0;
	doubleShot = FALSE;

	AddAnimation(SIMON_ANI_IDLE);
	AddAnimation(SIMON_ANI_WALKING);
	AddAnimation(SIMON_ANI_JUMP);
	AddAnimation(SIMON_ANI_SITING);	
	AddAnimation(SIMON_ANI_HIT_STAND);
	AddAnimation(SIMON_ANI_HIT_SIT);
	AddAnimation(SIMON_ANI_POWER_UP);
	AddAnimation(SIMON_ANI_THROW_STAND);
	AddAnimation(SIMON_ANI_THROW_SIT);
	AddAnimation(SIMON_ANI_INJURED);
	AddAnimation(SIMON_ANI_GO_UP_STAIR);
	AddAnimation(SIMON_ANI_IDLE_UP_STAIR);
	AddAnimation(SIMON_ANI_GO_DOWN_STAIR);
	AddAnimation(SIMON_ANI_IDLE_DOWN_STAIR);
	AddAnimation(SIMON_ANI_HIT_UP_STAIR);
	AddAnimation(SIMON_ANI_HIT_DOWN_STAIR);
	AddAnimation(SIMON_ANI_DIE);
	AddAnimation(SIMON_ANI_INVISIBLE);
	AddAnimation(SIMON_ANI_THROW_UP_STAIR);
	AddAnimation(SIMON_ANI_THROW_DONW_STAIR);

	SetState(SIMON_STATE_IDLE);

	whip = new Whip();
	dagger = new Dagger();
	subWeapon = SubWeapon::GetInstance();
	firebomb = new FireBomb();
}

void Simon::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_SIMON, SIMON_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, BOUNDINGBOX_TEXTURE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 tSimon = textures->Get(ID_TEX_SIMON);
	LPANIMATION ani;

	vector<vector<int>> resources;
	Game::GetInstance()->LoadObjectPositionFromFile(SIMON_INFO, resources);

	for (int i = 0; i < resources.size(); i++)
	{
		if (resources[i][0] == SPRITES)
		{
			sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], tSimon);
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

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	// simple fall down
	if (isOnStair)
		vy = 0;
	else 
		vy += SIMON_GRAVITY * dt;

	// simple collision with edge
	if (x - 15 <= 0 && vx < 0) x = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable = FALSE;
		untouchable_start = 0;
	}

	if (state == SIMON_STATE_INVISIBLE && GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable = false;
		SetState(SIMON_STATE_IDLE);
		untouchable_start = 0;
	}

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// if simon hit candle, do nothing
			if (dynamic_cast<Candle*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Ground*>(e->obj)) {
				if (e->ny > 0)
				{
					x += dx;
					y += dy;
				}
				else {
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.46f;

					if (isOnStair) {
						x += dx;
						y += dy;
					}

					if (ny != 0) vy = 0;
					if (nx != 0) vx = 0;
				}
			
			}
			else if (dynamic_cast<Item*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;

				e->obj->isVisible = false;

				if (e->obj->GetState() >= ITEM_DAGGER) {
					powerUp = true;

					if (e->obj->GetState() == ITEM_DAGGER) {
						subWeapon->replaceSubWeapon(DAGGER);
						DebugOut(L"Power Up: Dagger\n");
					}
					else if (e->obj->GetState() == ITEM_FIRE_BOMB) {
						subWeapon->replaceSubWeapon(FIRE_BOMB);
						DebugOut(L"Power Up: Fire Bomb\n");
					}
					else if (e->obj->GetState() == ITEM_WATCH) {
						subWeapon->replaceSubWeapon(WATCH);
						DebugOut(L"Power Up: Watch\n");
					}
					else if (e->obj->GetState() == ITEM_AXE) {
						subWeapon->replaceSubWeapon(AXE);
						DebugOut(L"Power Up: Axe\n");
					}
				}
				else if (e->obj->GetState() == ITEM_CHAIN) {
					SetState(SIMON_STATE_POWER_UP);

					vx = 0;

					// upgrade whip
					if (whip->GetState() == NORMAL_WHIP)
					{
						whip->SetState(SHORT_CHAIN);
						whipState = SHORT_CHAIN;
					}
					else if (whip->GetState() == SHORT_CHAIN)
					{
						whip->SetState(LONG_CHAIN);
						whipState = LONG_CHAIN;
					}

				}
				else if (e->obj->GetState() == ITEM_SMALL_HEART)
					heart += 1;
				else if (e->obj->GetState() == ITEM_LARGE_HEART)
					heart += 5;
				else if (e->obj->GetState() == ITEM_RED_MONEY_BAG)
					point += 100;
				else if (e->obj->GetState() == ITEM_BLUE_MONEY_BAG)
					point += 400;
				else if (e->obj->GetState() == ITEM_WHITE_MONEY_BAG)
					point += 700;
				else if (e->obj->GetState() == ITEM_FLASH_MONEY_BAG)
					point += 1000;
				else if (e->obj->GetState() == ITEM_PORK_CHOP)
					HP = 17;
				else if (e->obj->GetState() == ITEM_CROSS)
					isHitCross = true;
				else if (e->obj->GetState() == ITEM_DOUBLE_SHOT)
					doubleShot = true;
				else if (e->obj->GetState() == ITEM_INVISIBILITY)
					SetState(SIMON_STATE_INVISIBLE);
			}
			else if (dynamic_cast<Zombie*>(e->obj))
			{
				Zombie *z = dynamic_cast<Zombie*>(e->obj);
				if (z->state != ZOMBIE_DESTROY && z->state != ZOMBIE_ANI_INACTIVE)
				{
					if (!untouchable) {
						if (e->nx != 0) x += dx;
						if (e->ny != 0) y += dy;

						if (e->nx < 0 && nx < 0) nx = 1;
						else if (e->nx < 0 && nx > 0) nx = 1;
						else if (e->nx > 0 && nx < 0) nx = -1;
						else if (e->nx > 0 && nx > 0) nx = -1;

						SetState(SIMON_STATE_INJURED);
						StartUntouchable();

						HP -= 2;
					}
					else
					{
						x += dx;
						if (e->ny < 0)
							y += dy;
					}
				}			
			}
			else if (dynamic_cast<Leopard*> (e->obj))
			{
				if (!untouchable)
				{
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					if (e->nx < 0) nx = 1;
					else if (e->nx > 0) nx = -1;

					SetState(SIMON_STATE_INJURED);
					StartUntouchable();

					HP -= 2;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Bat*> (e->obj)) {
				Bat *b = dynamic_cast<Bat*>(e->obj);
				if (b->state != BAT_DESTROY && b->state != BAT_INACTIVE)
				{
					if (!untouchable) {
						if (e->nx != 0) x += dx;
						if (e->ny != 0) y += dy;

						if (e->nx < 0 && nx < 0) nx = 1;
						else if (e->nx < 0 && nx > 0) nx = 1;
						else if (e->nx > 0 && nx < 0) nx = -1;
						else if (e->nx > 0 && nx > 0) nx = -1;

						SetState(SIMON_STATE_INJURED);
						StartUntouchable();

						HP -= 2;

						b->SetState(BAT_DESTROY);
					}
					else
					{
						x += dx;
						y += dy;
					}
				}		
			}
			else if (dynamic_cast<FishMan*> (e->obj))
			{
				FishMan *fm = dynamic_cast<FishMan*>(e->obj);
				if (fm->state != FISHMAN_DESTROY && fm->state != FISHMAN_INACTIVE)
				{
					if (!untouchable) {
						if (e->nx != 0) x += dx;
						if (e->ny != 0) y += dy;

						if (e->nx < 0 && nx < 0) nx = 1;
						else if (e->nx < 0 && nx > 0) nx = 1;
						else if (e->nx > 0 && nx < 0) nx = -1;
						else if (e->nx > 0 && nx > 0) nx = -1;

						SetState(SIMON_STATE_INJURED);
						StartUntouchable();

						e->obj->isVisible = false;
					}
					else
					{
						x += dx;
						y += dy;
					}
				}			
			}
			else if (dynamic_cast<FireBall*> (e->obj))
			{
				if (!untouchable) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					if (e->nx < 0 && nx < 0) nx = 1;
					else if (e->nx < 0 && nx > 0) nx = 1;
					else if (e->nx > 0 && nx < 0) nx = -1;
					else if (e->nx > 0 && nx > 0) nx = -1;

					SetState(SIMON_STATE_INJURED);
					StartUntouchable();

					e->obj->isVisible = false;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Boss*> (e->obj)) {
				if (!untouchable) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					if (e->nx < 0 && nx < 0) nx = 1;
					else if (e->nx < 0 && nx > 0) nx = 1;
					else if (e->nx > 0 && nx < 0) nx = -1;
					else if (e->nx > 0 && nx > 0) nx = -1;

					SetState(SIMON_STATE_INJURED);
					StartUntouchable();

					HP -= 2;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Stair*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Gate*>(e->obj))
			{
				isHitGate = true;
				vy = 0;
				SetState(SIMON_STATE_IDLE);

				x += dx;
				//y += dy;
			}
			else {
				x += min_tx * dx + nx * 0.4f;;
				y += min_ty * dy + ny * 0.46f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	// check collision between whip and candle
	if (state == SIMON_STATE_HIT_SITTING || state == SIMON_STATE_HIT_STANDING ||
		state == SIMON_STATE_HIT_DOWN_STAIR || state == SIMON_STATE_HIT_UP_STAIR) {
		// set position for whip
		whip->SetOrientation(nx);
		whip->SetWhipPosition(D3DXVECTOR3(x, y, 0), isStand);
		loseHP = false;
	
		// calcutator collision when render last sprite of whip
		if (animations[state]->GetCurrentFrame() == animations[state]->GetFramesSize() - 1)
		{
			RenderBoundingBox();
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT obj = coObjects->at(i);
				if (dynamic_cast<Candle*>(obj)) {
					Candle *e = dynamic_cast<Candle*> (obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						DebugOut(L"Collide\n");
						e->SetState(CANDLE_DESTROY);			
					}
				}
				else if (dynamic_cast<Zombie*>(obj))
				{
					Zombie *e = dynamic_cast<Zombie*> (obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						e->SetState(ZOMBIE_DESTROY);
						point += 100;
					}
				}
				else if (dynamic_cast<Leopard*>(obj))
				{
					Leopard *e = dynamic_cast<Leopard*> (obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						e->SetState(LEOPARD_DESTROY);
						point += 100;
					}
				}
				else if (dynamic_cast<Bat*> (obj))
				{
					Bat *e = dynamic_cast<Bat*>(obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						e->SetState(BAT_DESTROY);
						point += 100;
					}
				}
				else if (dynamic_cast<FishMan*> (obj))
				{
					FishMan *e = dynamic_cast<FishMan*> (obj);
					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						e->SetState(FISHMAN_DESTROY);
						point += 100;
					}
				}
				else if (dynamic_cast<FireBall*> (obj))
				{
					FireBall *e = dynamic_cast<FireBall*> (obj);
					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						e->isVisible = false;
					}
				}
				else if (dynamic_cast<Boss*> (obj))
				{
					Boss *e = dynamic_cast<Boss*>(obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b)) {
						if (e->HP > 0)
						{
							if (whip->GetState() == NORMAL_WHIP)
							{
								if (!loseHP)
								{
									e->HP -= 1;
									loseHP = true;
								}
							}					
							else if (whip->GetState() == SHORT_CHAIN)
							{
								if (e->HP >= 2)
								{
									if (!loseHP)
									{
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
							}
							else if (whip->GetState() == LONG_CHAIN)
							{
								if (e->HP >= 3)
								{
									if (!loseHP)
									{
										e->HP -= 3;
										loseHP = true;
									}
								}
								else if (e->HP == 2)
								{
									if (!loseHP)
									{
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
							}
						}
					}
				}
				else if (dynamic_cast<Ground*> (obj))
				{
					Ground *e = dynamic_cast<Ground*> (obj);

					float l, t, r, b;
					e->GetBoundingBox(l, t, r, b);

					if (whip->CheckCollision(l, t, r, b) == true)
					{
						if (e->GetState() != GROUND) {
							e->SetState(GROUND_DESTROY);
						}
					}
				}
			}
		}
	}
	
	if (HP <= 0)
	{
		SetState(SIMON_STATE_DIE);
		timer = GetTickCount();
	}
			
	if (y > 276 + 80 && isOnStair)
	{
		if (x < 3500)
			SetPosition(5730.0f, -33.0f + 80);
		else if (x > 3700)
			SetPosition(6730, -33 + 80);
	}		

	if (y < -33 + 80 && isOnStair) {
		if (x < 5800)
			SetPosition(3168.0f, 276.0f + 80);
		else if (x > 6000)
			SetPosition(3806, 276 + 80);
	}

	if (whipState == NORMAL_WHIP)
		whip->SetState(NORMAL_WHIP);
	else if (whipState == SHORT_CHAIN)
		whip->SetState(SHORT_CHAIN);
	else if (whipState == LONG_CHAIN)
		whip->SetState(LONG_CHAIN);
}

void Simon::Render()
{
	if(state==SIMON_STATE_HIT_STANDING || state== SIMON_STATE_HIT_SITTING ||
	   state == SIMON_STATE_HIT_DOWN_STAIR || state == SIMON_STATE_HIT_UP_STAIR)
		whip->Render();

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[state]->Render(nx, x, y, alpha);

	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING:
		if(nx == 1)
			vx = SIMON_WALKING_SPEED;
		else if(nx == -1)
			vx = -SIMON_WALKING_SPEED;
		break;

	case SIMON_STATE_JUMP:
		isStand = TRUE;
		vy = -SIMON_JUMP_SPEED_Y;
		break;

	case SIMON_STATE_IDLE:
		isStand = TRUE;
		vx = 0;
		//vy = 0;
		break;

	case SIMON_STATE_DIE:
		vx = 0;
		vy = 0;
		isStand = FALSE;
		break;

	case SIMON_STATE_SIT:
		isStand = FALSE;
		vx = 0;
		vy = 0;
		break;

	case SIMON_STATE_HIT_STANDING:
	case SIMON_STATE_THROW_STAND:
	case SIMON_STATE_HIT_UP_STAIR:
	case SIMON_STATE_HIT_DOWN_STAIR:
	case SIMON_STATE_THROW_DOWN_STAIR:
	case SIMON_STATE_THROW_UP_STAIR:
		isStand = TRUE;
		vx = 0;
		timer = GetTickCount();
		animations[state]->ResetAnimation();
		break;

	case SIMON_STATE_HIT_SITTING:
	case SIMON_STATE_THROW_SIT:
		isStand = FALSE;
		timer = GetTickCount();
		animations[state]->ResetAnimation();
		break;

	case SIMON_STATE_POWER_UP:
		isStand = TRUE;
		timer = GetTickCount();
		animations[state]->ResetAnimation();
		break;

	case SIMON_STATE_INJURED:
		if (!isOnStair) {
			if (nx > 0) {
				vx = -SIMON_INJURED_DEFLECT_SPEED / 2;
			}
			else if (nx < 0)
			{
				vx = SIMON_INJURED_DEFLECT_SPEED / 2;
			}
			vy = -SIMON_INJURED_DEFLECT_SPEED;
			timer = GetTickCount();
			animations[state]->ResetAnimation();
		}		
		else {
			vx = 0; 
			vy = 0;
		}
		break;

	case SIMON_STATE_GO_UP_STAIR:
		if (nx > 0) {
			vx = SIMON_SPEED_ON_STAIR;
			vy = -SIMON_SPEED_ON_STAIR;
		}		
		else if (nx < 0) {
			vx = -SIMON_SPEED_ON_STAIR;
			vy = -SIMON_SPEED_ON_STAIR;
		}
		break;

	case SIMON_STATE_GO_DOWN_STAIR:
		if (nx > 0)
		{
			vx = SIMON_SPEED_ON_STAIR;
			vy = SIMON_SPEED_ON_STAIR;
		}
		else if (nx < 0)
		{
			vx = -SIMON_SPEED_ON_STAIR;
			vy = SIMON_SPEED_ON_STAIR;
		}
		break;

	case SIMON_STATE_IDLE_UP_STAIR:
	case SIMON_STATE_IDLE_DOWN_STAIR:
		isStand = TRUE;
		vx = 0;
		vy = 0;
		break;

	case SIMON_STATE_INVISIBLE:
		StartUntouchable();
		break;
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 14;
	top = y + 2;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}
