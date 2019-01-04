#pragma region __INCLUDE__
#include "SceneManager.h"
#include "Game.h"
#include "Simon.h"
#include "SubWeapon.h"
#include "Dagger.h"
#include "FireBomb.h"
#include "Axe.h"
#include "Boomerang.h"
#include "Ground.h"
#include "Whip.h"
#include "Candle.h"
#include "Item.h"
#include "Zombie.h"
#include "Leopard.h"
#include "Bat.h"
#include "Gate.h"
#include "FishMan.h"
#include "FireBall.h"
#include "TileMap.h"
#include "Stair.h"
#include "Boss.h"
#include "ScoreBoard.h"
#include "Grid.h"
#include "BrickDestroyEffect.h"
#include "WaterEffect.h"
#pragma endregion

#pragma region __DECLARE__
Game *game = Game::GetInstance();
Simon *simon;
SubWeapon *subWeapon = SubWeapon::GetInstance();
Dagger *dagger;
FireBomb *firebomb;
Axe *axe;
Boomerang *boomerang;
Ground *ground;
Whip *whip;
Candle *candle;
Item *item;
Zombie *zombie;
Leopard *leopard;
Bat *bat;
Gate *gate;
FishMan *fishman;
FireBall *fireball;
TileMap *tileMap;
Stair *stair;
Boss *boss;
ScoreBoard *scoreboard;
Grid *grid;
BrickDestroyEffect *brickEffect;
BrickEffects *effects;
WaterEffect *waterEffect;
WaterEffects *waterEffects;

vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> listStairs;
vector<LPGAMEOBJECT> listFishMan;
vector<LPGAMEOBJECT> listEnemies;
vector<vector<int>> objectPosition;
vector<LPGAMEOBJECT> listItems;
vector<LPBRICKEFFECTS> listEffects;
vector<LPGAMEOBJECT> listLeopards;
vector<LPWATEREFFECTS> listWaterEffects;

Textures *textures = Textures::GetInstance();
Sprites *sprites = Sprites::GetInstance();
Animations *animations = Animations::GetInstance();
SceneManager *SceneManager::__instance = NULL;
#pragma endregion

SceneManager::SceneManager()
{
	scene = 0;
	SetNextScene(scene);
	Init(scene);
	stage = STAGE_1;
	pause = false;
	timeCount = 0;
	simonRespawn = 0;
	heal = 17;
	win = false;

	leftTimer = GetTickCount();
	rightTimer = GetTickCount() + 4000;
	batTimer = GetTickCount() + 5000;
	fishmanTimer = GetTickCount() - 7000;
	crossTimer = 0;
	changeBackcolor = false;
	backcolorTimer = 0;
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init(int scene)
{
	Draw();
}


void SceneManager::SetNextScene(int scene)
{
	if (scene == 0)
		this->scene = SCENE_1;
	else if (scene == SCENE_1)
		this->scene = SCENE_2;
}

#pragma region __KEY_HANDLER__
bool SceneManager::IsRenderDone(DWORD time)
{
	return GetTickCount() - simon->timer > time;
}

void SceneManager::KeyState(BYTE * states)
{
	if (simon->GetState() == SIMON_STATE_DIE)
		return;

	if (simon->GetState() == SIMON_STATE_JUMP && simon->GetVy() != 0)
		return;

	if (simon->GetState() == SIMON_STATE_POWER_UP && !IsRenderDone(300))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->x + 20 < game->GetCameraPosition().x || objects[i]->x > game->GetCameraPosition().x + SCREEN_WIDTH)
				continue;
			if (dynamic_cast<Candle*>(objects[i]))
			{
				Candle *c = dynamic_cast<Candle*>(objects[i]);
				if (c->state == BIG_CANDLE)
					continue;
			}
			if (dynamic_cast<Zombie*>(objects[i]))
			{
				Zombie *z = dynamic_cast<Zombie*>(objects[i]);
				if (z->state == ZOMBIE_DESTROY || z->state == ZOMBIE_INACTIVE)
					continue;
			}
			if (dynamic_cast<Leopard*>(objects[i]))
			{
				Leopard *l = dynamic_cast<Leopard*>(objects[i]);
				if (l->state != LEOPARD_JUMP || l->state == LEOPARD_RUN)
					continue;
			}
			objects[i]->currentState = objects[i]->GetState();
			objects[i]->isFreeze = true;
			objects[i]->freeze_start = GetTickCount() - 3700;
			simon->allowUseSubWeapon = false;
			pause = true;
		}
		return;
	}
		
	if ((simon->GetState() == SIMON_STATE_THROW_STAND) && !IsRenderDone(300))
		return;

	if ((simon->GetState() == SIMON_STATE_THROW_SIT) && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_HIT_STANDING && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_HIT_SITTING && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_SIT && isSitting)
		return;

	if (simon->GetState() == SIMON_STATE_INJURED_LEFT && simon->vy < 0)
		return;

	if (simon->GetState() == SIMON_STATE_INJURED_RIGHT && simon->vy < 0)
		return;

	if (simon->GetState() == SIMON_STATE_HIT_UP_STAIR && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_HIT_DOWN_STAIR && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_THROW_UP_STAIR && !IsRenderDone(300))
		return;

	if (simon->GetState() == SIMON_STATE_THROW_DOWN_STAIR && !IsRenderDone(300))
		return;

	if (simon->isHitGate) return;

	if (simon->win)
	{
		simon->SetState(SIMON_STATE_IDLE);
		return;
	}

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (!simon->isOnStair)
		{
			simon->SetState(SIMON_STATE_WALKING);
			simon->nx = 1;
		}
		else if (simon->isOnStair)
		{
			if (simon->isUpOrDown == false)
			{
				if (simon->nx > 0) {
					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
						simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
						simon->nx = 1;
					}
				}
				else if (simon->nx < 0) {
					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
						simon->isUpOrDown = true;		// go up stair
						simon->SetState(SIMON_STATE_GO_UP_STAIR);
						simon->nx = 1;
					}
				}
			}
			else if (simon->isUpOrDown == true)
			{
				if (simon->nx > 0) {
					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
						simon->SetState(SIMON_STATE_GO_UP_STAIR);
						simon->nx = 1;
					}
				}
				else if (simon->nx < 0) {
					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
						simon->isUpOrDown = false;		// go down stair
						simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
						simon->nx = 1;
					}
				}
			}
		}

	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (!simon->isOnStair) {
			simon->SetState(SIMON_STATE_WALKING);
			simon->nx = -1;
		}
		else if (simon->isOnStair)
		{
			if (simon->isUpOrDown == false)
			{
				if (simon->nx > 0) {
					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
						simon->isUpOrDown = true;		// go up stair
						simon->SetState(SIMON_STATE_GO_UP_STAIR);
						simon->nx = -1;
					}
				}
				else if (simon->nx < 0) {
					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
						simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
						simon->nx = -1;
					}
				}
			}
			else if (simon->isUpOrDown == true)
			{
				if (simon->nx > 0) {
					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
						simon->isUpOrDown = false;		// go down stair
						simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
						simon->nx = -1;
					}
				}
				else if (simon->nx < 0) {
					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
						simon->SetState(SIMON_STATE_GO_UP_STAIR);
						simon->nx = -1;
					}
				}
			}
		}

	}
	else if (game->IsKeyDown(DIK_UP)) {
		if (simon->isOnStair == false) {
			CheckCollisionnBetweenSimonAndUpStair();
		}
		else if (simon->isOnStair)
		{
			if (CheckCollisionnBetweenSimonAndDownStair() == false)
			{
				if (simon->isUpOrDown == true)
				{
					simon->SetState(SIMON_STATE_GO_UP_STAIR);
				}
				else if (!simon->isUpOrDown)
				{
					simon->isUpOrDown = true;
					simon->SetState(SIMON_STATE_GO_UP_STAIR);
					simon->nx = -simon->nx;
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		if (simon->isOnStair == false) {
			if (CheckCollisionnBetweenSimonAndDownStair() == false)
				simon->SetState(SIMON_STATE_SIT);

		}
		else if (simon->isOnStair)
		{
			if (CheckCollisionnBetweenSimonAndUpStair() == false)
			{
				if (simon->isUpOrDown == false)
				{
					simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
				}
				else if (simon->isUpOrDown == true)
				{
					simon->isUpOrDown = false;
					simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
					simon->nx = -simon->nx;
				}
			}
		}
	}
	else
	{
		if (simon->isOnStair == false)
			simon->SetState(SIMON_STATE_IDLE);
		else if (simon->isOnStair == true)
		{
			if (simon->isUpOrDown == true) {
				simon->SetState(SIMON_STATE_IDLE_UP_STAIR);

			}
			else if (simon->isUpOrDown == false)
			{
				simon->SetState(SIMON_STATE_IDLE_DOWN_STAIR);
			}
		}
	}
}

void SceneManager::OnKeyDown(int KeyCode)
{
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	if (simon->isHitGate) return;
	if (simon->win)
	{
		simon->SetState(SIMON_STATE_IDLE);
		return;
	}

	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->GetState() == SIMON_STATE_JUMP || simon->isOnStair == true || simon->isOnStair)
			return;
		simon->SetState(SIMON_STATE_JUMP);
		break;

	case DIK_C:
		if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP || simon->GetState() == SIMON_STATE_WALKING)
			simon->SetState(SIMON_STATE_HIT_STANDING);
		else if (simon->GetState() == SIMON_STATE_SIT)
			simon->SetState(SIMON_STATE_HIT_SITTING);
		else if (simon->isOnStair == true)
		{
			if (simon->GetState() == SIMON_STATE_IDLE_UP_STAIR)
				simon->SetState(SIMON_STATE_HIT_UP_STAIR);
			else if (simon->GetState() == SIMON_STATE_IDLE_DOWN_STAIR)
				simon->SetState(SIMON_STATE_HIT_DOWN_STAIR);
		}
		break;

#pragma region __USE_SUB_WEAPON__
	case DIK_Z:
		if (simon->powerUp == false)
			return;
		if (simon->allowUseSubWeapon == false)
			return;
		if (subWeapon->GetState() == DAGGER) {
			if (simon->heart <= 0) return;			
			if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				dagger->SetPosition(simonX, simonY + 10);
				dagger->SetOrientation(simon->GetOrientation());
				dagger->isVisible = true;
				simon->SetState(SIMON_STATE_THROW_STAND);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_DOWN_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				dagger->SetPosition(simonX, simonY + 10);
				dagger->SetOrientation(simon->GetOrientation());
				dagger->isVisible = true;
				simon->SetState(SIMON_STATE_THROW_DOWN_STAIR);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_UP_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				dagger->SetPosition(simonX, simonY + 10);
				dagger->SetOrientation(simon->GetOrientation());
				dagger->isVisible = true;
				simon->SetState(SIMON_STATE_THROW_UP_STAIR);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_SIT) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				dagger->SetPosition(simonX, simonY + 20);
				dagger->SetOrientation(simon->GetOrientation());
				dagger->isVisible = true;
				simon->SetState(SIMON_STATE_THROW_SIT);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
		}
		else if (subWeapon->GetState() == WATCH)
		{
			if (simon->heart <= 4) return;
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->x + 20 < game->GetCameraPosition().x || objects[i]->x > game->GetCameraPosition().x + SCREEN_WIDTH)
					continue;
				if (dynamic_cast<Leopard*>(objects[i]))
				{
					Leopard *l = dynamic_cast<Leopard*>(objects[i]);
					if (l->state != LEOPARD_JUMP || l->state == LEOPARD_RUN)
						continue;
				}
				objects[i]->currentState = objects[i]->GetState();
				objects[i]->isFreeze = true;
				objects[i]->freeze_start = GetTickCount();
				simon->allowUseSubWeapon = false;				
				pause = true;
				pause_timer = GetTickCount();
				subWeaponTimer = GetTickCount();
			}
			simon->heart -= 5;
		}
		else if (subWeapon->GetState() == FIRE_BOMB)
		{
			if (simon->heart <= 0) return;
			if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				firebomb->SetPosition(simonX, simonY + 10);
				firebomb->SetOrientation(simon->GetOrientation());
				firebomb->isVisible = true;
				firebomb->SetState(FB_THROW);
				simon->SetState(SIMON_STATE_THROW_STAND);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_DOWN_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				firebomb->SetPosition(simonX, simonY + 10);
				firebomb->SetOrientation(simon->GetOrientation());
				firebomb->isVisible = true;
				firebomb->SetState(FB_THROW);
				simon->SetState(SIMON_STATE_THROW_DOWN_STAIR);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_UP_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				firebomb->SetPosition(simonX, simonY + 10);
				firebomb->SetOrientation(simon->GetOrientation());
				firebomb->isVisible = true;
				firebomb->SetState(FB_THROW);
				simon->SetState(SIMON_STATE_THROW_UP_STAIR);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
			else if (simon->GetState() == SIMON_STATE_SIT) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				firebomb->SetPosition(simonX, simonY + 20);
				firebomb->SetOrientation(simon->GetOrientation());
				firebomb->isVisible = true;
				firebomb->SetState(FB_THROW);
				simon->SetState(SIMON_STATE_THROW_SIT);
				simon->heart -= 1;
				simon->allowUseSubWeapon = false;
				subWeaponTimer = GetTickCount();
			}
		}
		else if (subWeapon->GetState() == AXE)
		{
			if (simon->heart <= 0) return;
			if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				axe->SetPosition(simonX, simonY + 10);
				axe->SetOrientation(simon->GetOrientation());
				axe->isVisible = true;
				axe->loseHP = false;
				axe->SetState(AXE_THROW);
				simon->SetState(SIMON_STATE_THROW_STAND);
				simon->heart -= 1;
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_DOWN_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				axe->SetPosition(simonX, simonY + 10);
				axe->SetOrientation(simon->GetOrientation());
				axe->isVisible = true;
				axe->loseHP = false;
				axe->SetState(AXE_THROW);
				simon->SetState(SIMON_STATE_THROW_DOWN_STAIR);
				simon->heart -= 1;
			}
			else if (simon->GetState() == SIMON_STATE_IDLE_UP_STAIR)
			{
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				axe->SetPosition(simonX, simonY + 10);
				axe->SetOrientation(simon->GetOrientation());
				axe->isVisible = true;
				axe->loseHP = false;
				axe->SetState(AXE_THROW);
				simon->SetState(SIMON_STATE_THROW_UP_STAIR);
				simon->heart -= 1;
			}
			else if (simon->GetState() == SIMON_STATE_SIT) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				axe->SetPosition(simonX, simonY + 20);
				axe->SetOrientation(simon->GetOrientation());
				axe->isVisible = true;
				axe->loseHP = false;
				axe->SetState(AXE_THROW);
				simon->SetState(SIMON_STATE_THROW_SIT);
				simon->heart -= 1;
			}
		}
		else if (subWeapon->GetState() == BOOMERANG)
		{
			if (simon->heart <= 0) return;
			if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP || 
				simon->GetState() == SIMON_STATE_IDLE_DOWN_STAIR || simon->GetState() == SIMON_STATE_IDLE_UP_STAIR) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				boomerang->posX = simonX;
				boomerang->SetPosition(simonX, simonY + 10);
				boomerang->SetOrientation(simon->GetOrientation());
				boomerang->isVisible = true;
				boomerang->SetState(BOOMERANG_THROW);
				simon->SetState(SIMON_STATE_THROW_STAND);
				simon->heart -= 1;
			}
			else if (simon->GetState() == SIMON_STATE_SIT) {
				float simonX, simonY;
				simon->GetPosition(simonX, simonY);
				boomerang->posX = simonX;
				boomerang->SetPosition(simonX, simonY + 20);
				boomerang->SetOrientation(simon->GetOrientation());
				boomerang->isVisible = true;
				boomerang->SetState(BOOMERANG_THROW);
				simon->SetState(SIMON_STATE_THROW_SIT);
				simon->heart -= 1;
			}
		}
		break;

#pragma endregion

#pragma region __SET_SUBWEAPON__
	case DIK_1:
		simon->powerUp = true;
		subWeapon->replaceSubWeapon(DAGGER);
		break;

	case DIK_2:
		simon->powerUp = true;
		subWeapon->replaceSubWeapon(AXE);
		break;

	case DIK_3:
		simon->powerUp = true;
		subWeapon->replaceSubWeapon(FIRE_BOMB);
		break;

	case DIK_4:
		simon->powerUp = true;
		subWeapon->replaceSubWeapon(WATCH);
		break;

	case DIK_5:
		simon->powerUp = true;
		subWeapon->replaceSubWeapon(BOOMERANG);
		break;
#pragma endregion
	case DIK_A:
		if (scene == SCENE_2)
		{
			stage = 3;
			simon->SetPosition(4900, 200);
		}		
		break;

	case DIK_S:
		if (scene == SCENE_2)
		{
			stage = 1;
			simon->SetPosition(2900, 60);
		}		
		break;

	case DIK_D:
		if (scene == SCENE_2)
		{
			stage = 2;
			simon->SetPosition(3200, 60);
		}	
		break;
	}
}

void SceneManager::OnKeyUp(int KeyCode)
{
	//currentScene->OnKeyUp(KeyCode);
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
#pragma endregion

SceneManager * SceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new SceneManager();
	return __instance;
}

void SceneManager::LoadGameResource()
{
	simon = new Simon();
	simon->LoadResources(textures, sprites, animations);

	ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	whip = new Whip();
	whip->LoadResources(textures, sprites, animations);

	candle = new Candle();
	candle->LoadResources(textures, sprites, animations);

	item = new Item();
	item->LoadResources(textures, sprites, animations);

	zombie = new Zombie();
	zombie->LoadResources(textures, sprites, animations);

	leopard = new Leopard();
	leopard->LoadResources(textures, sprites, animations);

	bat = new Bat();
	bat->LoadResources(textures, sprites, animations);

	gate = new Gate();
	gate->LoadResources(textures, sprites, animations);

	firebomb = new FireBomb();
	firebomb->LoadResources(textures, sprites, animations);

	axe = new Axe();
	axe->LoadResources(textures, sprites, animations);

	boomerang = new Boomerang();
	boomerang->LoadResources(textures, sprites, animations);

	fishman = new FishMan();
	fishman->LoadResources(textures, sprites, animations);

	fireball = new FireBall();
	fireball->LoadResources(textures, sprites, animations);

	boss = new Boss();
	boss->LoadResources(textures, sprites, animations);

	scoreboard = new ScoreBoard();
	scoreboard->LoadResources(textures, sprites, animations);

	brickEffect = new BrickDestroyEffect();
	brickEffect->LoadResources(textures, sprites, animations);

	waterEffect = new WaterEffect();
	waterEffect->LoadResources(textures, sprites, animations);
}

void SceneManager::Update(DWORD dt)
{
	if (simon->allowUseSubWeapon == false && GetTickCount() - subWeaponTimer > 2000)
		simon->allowUseSubWeapon = true;

	if (scene == SCENE_1)
	{
		// render camera
		float cx, cy;
		simon->GetPosition(cx, cy);

		if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap->GetMapWidth())
			game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);

		if (simon->isHitGate == true)
		{
			if (simon->x < 1410 - SIMON_BBOX_WIDTH)
			{
				simon->SetState(SIMON_STATE_WALKING);
				simon->vx /= 2;
			}			
			else
			{
				simon->SetState(SIMON_STATE_IDLE);
				simon->isHitGate = false;
				//KillALlObject();			
				SetNextScene(scene);
				Init(scene);
			}
		}
	}
	else if (scene == SCENE_2)
	{		
		if (stage == STAGE_1) {
			if (!simon->isHitGate) {
				// render camera
				game->SetCameraPosition(0, 0);
				float cx, cy;
				simon->GetPosition(cx, cy);

				if (listLeopards.size() == 0)
				{
					RespawnLeopard(simon);
				}

				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap->GetMapWidth())
					game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);

				if (cx + SCREEN_WIDTH / 2 > 3088)
					game->SetCameraPosition(3088 - SCREEN_WIDTH, 0);

				if (cx + SIMON_BBOX_WIDTH > 1260)
				{
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<Leopard*>(objects[i]))
						{
							Leopard *leo = dynamic_cast<Leopard*>(objects[i]);
							if (leo->order == 1)
								leo->allowJump = true;
						}
					}
				}
			}
#pragma region __PASSING_DOOR__
			else
			{
				if (game->GetCameraPosition().x <= 2800)
				{
					game->SetCameraPosition(game->GetCameraPosition().x + 2, 0);
				}
				else if (game->GetCameraPosition().x > 2800)
				{
					if (simon->x < 3136) {
						gate->SetState(GATE_OPENING);
						if (IsRenderDone(200)) {
							gate->SetState(GATE_OPENED);
							simon->nx = 1;
							simon->SetState(SIMON_STATE_WALKING);						
						}
					}
					else
					{
						simon->SetState(SIMON_STATE_IDLE);
						gate->SetState(GATE_CLOSE);
						if (IsRenderDone(200))
							gate->SetState(GATE_INACTIVE);

						if (game->GetCameraPosition().x < 3071)
						{
							game->SetCameraPosition(game->GetCameraPosition().x + 2, 0);
						}
						if (game->GetCameraPosition().x >= 3072) {
							simon->isHitGate = false;
							stage = 2;
						}
					}
				}
			}
#pragma endregion		
		}
		else if (stage == STAGE_2)
		{
			if (simon->isHitGate == false) {
				// render camera
				float cx, cy;
				simon->GetPosition(cx, cy);

				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap->GetMapWidth())
					game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);

				if (cx - SCREEN_WIDTH / 2 < 3072)
					game->SetCameraPosition(3072, 0);

				if (simon->x > 5626 && simon->x < 6662 - SIMON_BBOX_WIDTH)
				{
					if (game->GetCameraPosition().x + SCREEN_WIDTH >= 6662)
						game->SetCameraPosition(6662 - SCREEN_WIDTH, 0);
					if (game->GetCameraPosition().x < 5626)
						game->SetCameraPosition(5628, 0);

#pragma region __SPAWN_FISHMAN__
					if (pause == false)
					{
						if (GetTickCount() - fishmanTimer > 8000) {
							if (listFishMan.size() == 0) {
								SpawnFishMan(1, simon);
								SpawnFishMan(-1, simon);
							}
							else if (listFishMan.size() == 1)
							{
								SpawnFishMan(rand() % 2 == 0 ? 1 : -1, simon);
							}
							fishmanTimer = GetTickCount();
						}					
					}		
					SpawnFireBall();
				}
#pragma endregion

				//if (simon->isOnStair == false) {
					if (game->GetCameraPosition().x + SCREEN_WIDTH > 4112 && simon->x < 4112)
						game->SetCameraPosition(4112 - SCREEN_WIDTH, 0);
				//}
			}
			else if (simon->isHitGate == true)
			{
				if (game->GetCameraPosition().x <= 3850)
				{
					game->SetCameraPosition(game->GetCameraPosition().x + 2, 0);
				}
				if (game->GetCameraPosition().x > 3850)
				{
					if (simon->x < 4160) {
						gate->SetState(GATE_OPENING);
						if (IsRenderDone(200)) {
							gate->SetState(GATE_OPENED);
							simon->nx = 1;
							simon->SetState(SIMON_STATE_WALKING);
						}
					}
					else
					{
						simon->SetState(SIMON_STATE_IDLE);
						gate->SetState(GATE_CLOSE);
						if (IsRenderDone(200))
							gate->SetState(GATE_INACTIVE);

						if (game->GetCameraPosition().x < 4080)
						{
							game->SetCameraPosition(game->GetCameraPosition().x + 2, 0);
						}
						if (game->GetCameraPosition().x >= 4080) {
							simon->isHitGate = false;
							stage = 3;
							rightTimer = GetTickCount() - 5000;
							leftTimer = GetTickCount();
						}
					}
				}
			}
		}
		else if (stage == STAGE_3)
		{
			if (game->GetCameraPosition().x < 5628 - SCREEN_WIDTH) {
				// render camera
				float cx, cy;
				simon->GetPosition(cx, cy);

				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap->GetMapWidth())
					game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);

				if (game->GetCameraPosition().x < 4080)
					game->SetCameraPosition(4080, 0);
			}
			else
			{
				game->SetCameraPosition(5640 - SCREEN_WIDTH, 0);
				if (simon->x - 14 <= 5640 - SCREEN_WIDTH) 
					simon->x = 5640 - SCREEN_WIDTH;
				if (simon->x > 5438 - SIMON_BBOX_WIDTH)
					boss->active = true;
			}

			if (simon->y > 402 - SIMON_BBOX_HEIGHT && simon->vy > 0)
			{
				simon->y = 402 - SIMON_BBOX_HEIGHT;
				simon->vy = 0;
			}
		}

#pragma region __SPAWN_ZOMBIE__
		if (pause == false)
		{
			if (game->GetCameraPosition().x + SCREEN_WIDTH < 1150) {
				// left every 10s
				if (GetTickCount() - leftTimer > ZOMBIE_LEFT_SPAWN_TIME)
				{
					spawnZombie(1, simon->x - SCREEN_WIDTH / 2 + 1.0f, 256.0f + 80);
					leftTimer = GetTickCount();
				}
				// right every 6s 
				if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
				{
					for (int i = 0; i < 2; i++)
					{
						spawnZombie(-1, game->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f + 80);
						rightTimer = GetTickCount();
					}
				}
			}
			else if (game->GetCameraPosition().x > 2368 && game->GetCameraPosition().x + SCREEN_WIDTH < 3056)
			{
				// right every 6s 
				if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
				{
					for (int i = 0; i < 2; i++)
					{
						spawnZombie(-1, game->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f + 80);
						rightTimer = GetTickCount();
					}
				}
			}
			
			if (game->GetCameraPosition().x == 4080)
			{
				if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
				{
					for (int i = 0; i < 2; i++)
					{
						spawnZombie(-1, game->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f + 80);
						spawnZombie(-1, game->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 128.0f + 80);
						rightTimer = GetTickCount();
					}
				}
			}
			else if (game->GetCameraPosition().x > 4080 && game->GetCameraPosition().x + SCREEN_WIDTH < 5628 - SCREEN_WIDTH)
			{
				// left every 10s
				if (GetTickCount() - leftTimer > ZOMBIE_LEFT_SPAWN_TIME)
				{
					spawnZombie(1, simon->x - SCREEN_WIDTH / 2 + 1.0f, 256.0f + 80);
					leftTimer = GetTickCount();
				}
				// right every 6s 
				if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
				{
					for (int i = 0; i < 3; i++)
					{
						spawnZombie(-1, game->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f + 80);
						rightTimer = GetTickCount();
					}
				}
			}
		}		
#pragma endregion

#pragma region __SPAWN_BAT__
		if (pause == false)
		{
			if (simon->x > 3136 && simon->x < 4032 && !simon->isHitGate)
			{
				if (GetTickCount() - batTimer > BAT_SPAWN_TIME)
				{
					spawnBat(simon);
					batTimer = GetTickCount();
				}
			}
		}	
#pragma endregion

		boss->Update(dt, simon);
	}	
	grid->getListObjectPotential(objects);
#pragma region __UPDATE__
	//tạo 1 con trỏ cấp 2 để có thể thay đổi object trong hàm update 
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isVisible == false)
			continue;

		vector<LPGAMEOBJECT> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects

		if (dynamic_cast<Item*>(objects[i]))
		{
			for (int j = 0; j < objects.size(); j++)
			{
				if (objects[j]->isVisible == false)
					continue;

				if (dynamic_cast<Ground*>(objects[j])) // thêm tất cả objects "là ground", dùng trong hàm update của item
				{
					coObjects.push_back(objects[j]);
				}
			}
		}
		else if (dynamic_cast<Zombie*>(objects[i]))
		{
			for (int j = 0; j < objects.size(); j++)
			{
				if (objects[j]->isVisible == false)
					continue;

				// thêm ground vào coObject dùng trong hàm update của Zombie
				if (dynamic_cast<Ground*>(objects[j])) {
					coObjects.push_back(objects[j]);
				}
			}
		}
		else if (dynamic_cast<Leopard*>(objects[i]))
		{
			for (int j = 0; j < objects.size(); j++)
			{
				if (objects[j]->isVisible == false)
					continue;

				// thêm ground vào coObject dùng trong hàm update của Leopard
				if (dynamic_cast<Ground*>(objects[j])) {
					coObjects.push_back(objects[j]);
				}
			}
		}
		else if (dynamic_cast<FishMan*> (objects[i]))
		{
			for (int j = 0; j < objects.size(); j++)
			{
				if (objects[j]->isVisible == false)
					continue;

				// thêm ground vào coObject dùng trong hàm update của Leopard
				if (dynamic_cast<Ground*>(objects[j])) {
					coObjects.push_back(objects[j]);
				}
			}
		}
		else
		{
			coObjects.push_back(objects[i]);
		}

		objects[i]->Update(dt, &coObjects);
	}	
#pragma region __SIMON_UPDATE__
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isVisible == false)
			continue;

		coObjects.push_back(objects[i]);
	}
	for (int j = 0; j < listItems.size(); j++)
	{
		if (listItems[j]->isVisible == false)
			continue;

		coObjects.push_back(listItems[j]);
	}
	simon->Update(dt, &coObjects);
#pragma endregion

#pragma region ___SUBWEAPON_UPDATE__
	vector<LPGAMEOBJECT> coObjectsSW;
	switch (subWeapon->state)
	{
	case DAGGER:
		coObjectsSW.clear();
		for (int j = 0; j < objects.size(); j++)
		{
			if (objects[j]->isVisible == false)
				continue;

			// thêm Candle vào coObject dùng trong hàm update của Dagger
			if (dynamic_cast<Candle*>(objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Zombie*>(objects[j])) // thêm Zombie vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Leopard*>(objects[j])) // thêm Leopard vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Bat*>(objects[j])) // thêm Bat vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<FishMan*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Boss*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
		}
		dagger->Update(dt, &coObjectsSW);	
		break;

	case AXE:
		coObjectsSW.clear();
		for (int j = 0; j < objects.size(); j++)
		{
			if (objects[j]->isVisible == false)
				continue;

			// thêm Candle vào coObject dùng trong hàm update của Dagger
			if (dynamic_cast<Candle*>(objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Zombie*>(objects[j])) // thêm Zombie vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Leopard*>(objects[j])) // thêm Leopard vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Bat*>(objects[j])) // thêm Bat vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<FishMan*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Boss*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
		}
		axe->Update(dt, &coObjectsSW);
		break;

	case BOOMERANG:
		coObjectsSW.clear();
		for (int j = 0; j < objects.size(); j++)
		{
			if (objects[j]->isVisible == false)
				continue;

			// thêm Candle vào coObject dùng trong hàm update của Dagger
			if (dynamic_cast<Candle*>(objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Zombie*>(objects[j])) // thêm Zombie vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Leopard*>(objects[j])) // thêm Leopard vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Bat*>(objects[j])) // thêm Bat vào coObject dùng trong hàm update của dagger
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<FishMan*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Boss*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
		}
		boomerang->Update(dt, &coObjectsSW);
		break;

	case FIRE_BOMB:
		coObjectsSW.clear();
		for (int j = 0; j < objects.size(); j++)
		{
			if (objects[j]->isVisible == false)
				continue;

			if (dynamic_cast<Ground*> (objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Zombie*> (objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Leopard*> (objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Bat*> (objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Candle*> (objects[j])) {
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<FishMan*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
			else if (dynamic_cast<Boss*> (objects[j]))
			{
				coObjectsSW.push_back(objects[j]);
			}
		}
		firebomb->Update(dt, &coObjectsSW);
		break;
	}
#pragma endregion

	// xoá tất cả các objects có Visible = false ra khỏi vector
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<Candle*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Zombie*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Leopard*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<FishMan*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Bat*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Boss*>(objects[i]))
		{
			if (objects[i]->isVisible == false) {
				objects.erase(objects.begin() + i);
				i -= 1;
			}
		}
	}

	// xoá tất cả các objects có Visible = false ra khỏi vector
	for (int i = 0; i < listEnemies.size(); i++) {
		if (dynamic_cast<Zombie*> (listEnemies[i])) {
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		if (dynamic_cast<Candle*> (listEnemies[i])) {
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Bat*>(listEnemies[i]))
		{
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Candle*>(listEnemies[i]))
		{
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<FishMan*>(listEnemies[i]))
		{
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<Leopard*>(listEnemies[i]))
		{
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
		else if (dynamic_cast<FireBall*>(listEnemies[i]))
		{
			if (listEnemies[i]->isVisible == FALSE) {
				listEnemies.erase(listEnemies.begin() + i);
				i -= 1;
			}
		}
	}
	 
	if (listLeopards.size() > 0)
	{
		for (int i = 0; i < listLeopards.size(); i++)
		{
			if (listLeopards[i]->isVisible == false)
			{
				listLeopards.erase(listLeopards.begin() + i);
				i -= 1;
			}
		}
	}
	
	for (int i = 0; i < listFishMan.size(); i++)
	{
		if (listFishMan[i]->isVisible == FALSE) {
			listFishMan.erase(listFishMan.begin() + i);
			i -= 1;
		}
	}
#pragma endregion

	if (simon->GetState() == SIMON_STATE_DIE)
	{
		simonRespawn += dt;
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->currentState = objects[i]->GetState();
			objects[i]->isFreeze = true;
			objects[i]->freeze_start = GetTickCount() - 3000;
			simon->allowUseSubWeapon = false;
			pause = true;
			pause_timer = GetTickCount();
		}
	}
	if (simon->GetState() == SIMON_STATE_DIE && simon->life > 0)
	{
		if (simonRespawn >= 1000)
		{
			simon->isOnStair = false;
			simon->untouchable = false;
			simon->nx = 1;
			simon->SetState(SIMON_STATE_IDLE);
			if (stage == STAGE_1)
			{
				simon->SetPosition(60, 250);
				game->SetCameraPosition(0, 0);
			}			
			else if (stage == STAGE_2)
			{
				simon->SetPosition(3200, 60);
				game->SetCameraPosition(3072, 60);
			}				
			else if (stage == STAGE_3)
			{
				simon->SetPosition(4160, 60);
				game->SetCameraPosition(4080, 60);
				boss->isVisible = false;
				boss = new Boss();
				grid->insertObjectIntoGrid(boss);
			}
			simon->life -= 1;
			simon->HP = 17;
			simon->powerUp = false;
			simon->whipState = NORMAL_WHIP;
			simon->heart = 5;
			simonRespawn = 0;
			scoreboard->time = 300;

			bool killAll = false;
			if (killAll == false)
			{
				for (int i = 0; i < listEnemies.size(); i++)
				{
					if (dynamic_cast<Zombie*>(listEnemies[i]))
					{
						if ((listEnemies[i]->x >= game->GetCameraPosition().x) && (listEnemies[i]->x <= game->GetCameraPosition().x + SCREEN_WIDTH - 20))
						{
							listEnemies[i]->isVisible = false;
						}
					}				
				}
				killAll = true;
			}
		}	
	}

	if (GetTickCount() - pause_timer > ENEMY_FREE_TIME)
	{
		pause = false;
	}

	if (!pause && !simon->win)
	{
		timeCount += dt;
		if (timeCount >= 1000)
		{
			timeCount %= 1000;
			scoreboard->time -= 1;
		}
		if (scoreboard->time <= 0)
			simon->SetState(SIMON_STATE_DIE);
	}	

	if (simon->isHitCross)
	{
		crossTimer += dt;
		bool killAll = false;

		if (crossTimer >= 1000)
		{
			simon->isHitCross = false;
			crossTimer = 0;
		}

		if (killAll == false)
		{
			for (int i = 0; i < listEnemies.size(); i++)
			{
				if ((listEnemies[i]->x >= game->GetCameraPosition().x) && (listEnemies[i]->x <= game->GetCameraPosition().x + SCREEN_WIDTH - 20))
				{
					listEnemies[i]->isVisible = false;
				}
			}
		}
	}

	if (simon->win)
	{
		if (scoreboard->time > 0)
		{
			scoreboard->time -= 1;
			simon->point += 100;
		}
		else
		{
			if (simon->heart > 0)
			{
				simon->heart -= 1;
				simon->point += 1000;
			}		
			else if (simon->heart == 0)
			{
				win = true;
			}
		}
	}
	//if (win)
	//{
	//	game->Draw(1, game->GetCameraPosition().x, 0, Textures::GetInstance()->Get(ID_TEX_BLACKBOARD), 0, 0, 520, 480);
	//	SetRect(&rect, game->GetCameraPosition().x + SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 20, game->GetCameraPosition().x + SCREEN_WIDTH / 2 + 25, SCREEN_HEIGHT / 2 + 20);
	//	string message = "YOU WIN !!!";
	//	scoreboard->font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_VCENTER | DT_LEFT | DT_TOP, D3DCOLOR_XRGB(255, 255, 255));
	//}

	backcolorTimer += dt;

	scoreboard->stage = scene;
	heal = simon->HP;
	heart = simon->heart;
	life = simon->life;
	score = simon->point;
	whipState = simon->whipState;
	isPowerUp = simon->powerUp;
	simonSubWeapon = subWeapon->state;

	scoreboard->Update(dt, simon, subWeapon, boss);
	SetItemOnDestroy();

	// brick destroy effect update
	if (listEffects.size() > 0)
	{
		for (int i = 0; i < listEffects.size(); i++)
		{
			if (listEffects[i]->isDone)
			{
				listEffects.erase(listEffects.begin() + i);
				i -= 1;
			}
			else
				listEffects[i]->Update(dt);
		}
	}
	// water effect update
	if (listWaterEffects.size() > 0)
	{
		for (int i = 0; i < listWaterEffects.size(); i++)
		{
			if (listWaterEffects[i]->isDone)
			{
				listWaterEffects.erase(listWaterEffects.begin() + i);
				i -= 1;
			}
			else
				listWaterEffects[i]->Update(dt);
		}
	}

	//DebugOut(L"List Leopard: %d\n", listLeopards.size());
	//DebugOut(L"Objects: %d\n", objects.size());
}

void SceneManager::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		// cross effect render
		if (simon->isHitCross)
		{
			if (backcolorTimer >= 50)
			{
				if (changeBackcolor == false)
				{
					d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR_WHITE);
					changeBackcolor = true;
				}
				else
				{
					d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
					changeBackcolor = false;
				}
				backcolorTimer = 0;
			}
		}

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		tileMap->Draw(game->GetCameraPosition());
		scoreboard->Render();

		// object render
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->isVisible == false)
				continue;
			objects[i]->Render();
		}
		// simon render
		simon->Render();

		// brick destroy effect render
		if (listEffects.size() > 0)
		{
			for (int i = 0; i < listEffects.size(); i++)
			{
				listEffects[i]->Render();
			}
		}

		// water effect render
		if (listWaterEffects.size() > 0)
		{
			for (int i = 0; i < listWaterEffects.size(); i++)
			{
				listWaterEffects[i]->Render();
			}
		}

#pragma region __SUBWEAPON_RENDER__
		switch (subWeapon->state)
		{
		case DAGGER:
			if (dagger->isVisible == true)
				dagger->Render();
			break;

		case AXE:
			if (axe->isVisible == true)
				axe->Render();
			break;

		case FIRE_BOMB:
			if (firebomb->isVisible == true)
				firebomb->Render();
			break;

		case BOOMERANG:
			if (boomerang->isVisible == true)
				boomerang->Render();
			break;

		default:
			break;
		}
#pragma endregion	
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	//Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void SceneManager::Draw()
{	
	scoreboard = new ScoreBoard();
	scoreboard->SetPosition(0, 0);

	if (scene == SCENE_1)
	{
		objects.clear();
		listEnemies.clear();
		listItems.clear();
		grid = new Grid();

#pragma region __SIMON__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(SIMON_INFO, objectPosition);
		simon = new Simon();
		simon->SetPosition(objectPosition[1][0], objectPosition[1][1]);
		simon->HP = scoreboard->playerHeal;
		simon->heart = scoreboard->heart;
		simon->life = scoreboard->playerLife;
		simon->point = scoreboard->score;
		//objects.push_back(simon);
		//grid->insertObjectIntoGrid(simon);
#pragma endregion
		dagger = new Dagger();

#pragma region __GROUND__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(GROUND_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == SCENE_1)
			{
				ground = new Ground(objectPosition[i][1], objectPosition[i][2]);
				ground->SetPosition(objectPosition[i][3], objectPosition[i][4] + 80);
				//objects.push_back(ground);
				grid->insertObjectIntoGrid(ground);
			}
		}
#pragma endregion
		
#pragma region __CANDLE___
		objectPosition.clear();
		game->LoadObjectPositionFromFile(CANDLE_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == SCENE_1)
			{
				candle = new Candle(objectPosition[i][0] - 1);
				candle->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
				candle->item = objectPosition[i][3];
				//objects.push_back(candle);
				grid->insertObjectIntoGrid(candle);
				listEnemies.push_back(candle);
			}
		}
#pragma endregion
	
#pragma region __GATE__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(GATE_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == GATE_1)
			{
				gate = new Gate(GATE_1);
				gate->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
				//objects.push_back(gate);
				grid->insertObjectIntoGrid(gate);
			}
		}
#pragma endregion

		tileMap = new TileMap(0, LEVEL1_TEXTURE, LEVEL1_INFO, 1536, 320, 32, 32);
		tileMap->LoadSpritesFromFile();
		tileMap->LoadMatrixFromFile();
	}
	else if (scene == SCENE_2)
	{
		objects.clear();
		listEnemies.clear();
		grid = new Grid();

#pragma region __SIMON__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(SIMON_INFO, objectPosition);
		simon = new Simon();
		simon->SetPosition(80, 60);
		simon->HP = heal;
		simon->heart = heart;
		simon->life = life;
		simon->point = score;
		simon->whipState = whipState;
		simon->powerUp = isPowerUp;
		subWeapon->SetState(simonSubWeapon);
		//objects.push_back(simon);
		//grid->insertObjectIntoGrid(simon);
#pragma endregion

		boss = new Boss();
		grid->insertObjectIntoGrid(boss);

#pragma region __SUB_WEAPON__
		dagger = new Dagger();
		dagger->isVisible = false;

		firebomb = new FireBomb();
		firebomb->isVisible = false;

		axe = new Axe();
		axe->isVisible = false;
		
		boomerang = new Boomerang();
		boomerang->isVisible = false;

		fireball = new FireBall();
		fireball->isVisible = false;

#pragma endregion

#pragma region __GROUND__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(GROUND_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == SCENE_2)
			{
				ground = new Ground(objectPosition[i][1], objectPosition[i][2]);
				ground->SetPosition(objectPosition[i][3], objectPosition[i][4] + 80);
				if (ground->state != GROUND)
					ground->what = objectPosition[i][5];
				//objects.push_back(ground);		
				grid->insertObjectIntoGrid(ground);
			}		
		}
#pragma endregion

#pragma region __CANDLE__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(L"Resources\\Candle\\candle.txt", objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == SCENE_2)
			{
				candle = new Candle(objectPosition[i][0] - 1);
				candle->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
				candle->item = objectPosition[i][3];
				//objects.push_back(candle);
				listEnemies.push_back(candle);
				grid->insertObjectIntoGrid(candle);
			}
		}
#pragma endregion

#pragma region __STAIR__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(STAIR_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			stair = new Stair(objectPosition[i][0], objectPosition[i][1]);
			stair->SetPosition(objectPosition[i][2], objectPosition[i][3] + 80);
			//objects.push_back(stair);
			listStairs.push_back(stair);
			grid->insertObjectIntoGrid(stair);
		}
#pragma endregion

#pragma region __LEOPARD__
		//objectPosition.clear();
		//game->LoadObjectPositionFromFile(LEOPARD_INFO, objectPosition);
		//for (int i = 0; i < 3; i++)
		//{
		//	leopard = new Leopard(objectPosition[i][0]);
		//	leopard->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
		//	leopard->nx = -1;
		//	leopard->direction = -1;
		//	leopard->posY = objectPosition[i][2] + 80;
		//	//objects.push_back(leopard);
		//	listEnemies.push_back(leopard);
		//	listLeopards.push_back(leopard);
		//	grid->insertObjectIntoGrid(leopard);
		//}
#pragma endregion

#pragma region __GATE__
		objectPosition.clear();
		game->LoadObjectPositionFromFile(GATE_INFO, objectPosition);
		for (int i = 0; i < objectPosition.size(); i++)
		{
			if (objectPosition[i][0] == GATE_2)
			{
				gate = new Gate(GATE_2);
				gate->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
				//objects.push_back(gate);
				grid->insertObjectIntoGrid(gate);
			}		
		}
#pragma endregion	

		// load map
		tileMap = new TileMap(0, LEVEL2_TEXTURE, LEVEL2_INFO, 6688, 352, 32, 32);
		tileMap->LoadSpritesFromFile();
		tileMap->LoadMatrixFromFile();
	}
}

void SceneManager::spawnZombie(int nx, float x, float y)
{
	zombie = new Zombie(nx);
	zombie->SetPosition(x, y);
	//objects.push_back(zombie);
	listEnemies.push_back(zombie);
	grid->insertObjectIntoGrid(zombie);
}

void SceneManager::spawnBat(Simon * simon)
{
	bat = new Bat(-simon->nx, simon->y + 25);
	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();

	if (bat->nx > 0)
		bat->SetPosition(cam.x, simon->y + 25);
	else if (bat->nx < 0)
		bat->SetPosition(cam.x + SCREEN_WIDTH - BAT_BBOX_WIDTH, simon->y + 25);
	//objects.push_back(bat);
	listEnemies.push_back(bat);
	grid->insertObjectIntoGrid(bat);
}

void SceneManager::SpawnFishMan(int nx, Simon * simon)
{
	D3DXVECTOR3 cam = game->GetCameraPosition();

	fishman = new FishMan(nx);
	if (nx > 0)
	{
		int fx = rand() % ((int)simon->x - (int)cam.x + 1) + ((int)cam.x + 1);
		fishman->SetPosition(fx, 222);
	}
	else if (nx < 0)
	{
		int fx = rand() % ((int)cam.x + SCREEN_WIDTH  - (int)simon->x - SIMON_BBOX_WIDTH) + ((int)simon->x + SIMON_BBOX_WIDTH + 1);
		if (fx > 6586)
			fx = 6545;
		fishman->SetPosition(fx, 222);
	}
	//objects.push_back(fishman);
	listEnemies.push_back(fishman);
	listFishMan.push_back(fishman);
	grid->insertObjectIntoGrid(fishman);

	waterEffects = new WaterEffects();
	waterEffects->SetPosition(fishman->x, 290);
	listWaterEffects.push_back(waterEffects);
}

void SceneManager::SpawnFireBall()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<FishMan*>(objects[i]))
		{
			FishMan *f = dynamic_cast<FishMan*>(objects[i]);

			if (f->GetState() == FISHMAN_SHOT)
			{
				if (f->nx == 1) {
					float fx, fy;
					f->GetPosition(fx, fy);
					fireball->SetPosition(fx + FISHMAN_BBOX_WIDTH, fy + 4);
					fireball->nx = 1;
				}
				else if (f->nx == -1)
				{
					float fx, fy;
					f->GetPosition(fx, fy);
					fireball->SetPosition(fx, fy + 4);
					fireball->nx = -1;
				}
				fireball->isVisible = true;
				fireball->SetState(FIREBALL);
				//objects.push_back(fireball);
				listEnemies.push_back(fireball);
				grid->insertObjectIntoGrid(fireball);
			}
		}
	}
}

void SceneManager::RespawnLeopard(Simon * simon)
{
	if (simon->x <= 600)
	{
		objectPosition.clear();
		game->LoadObjectPositionFromFile(LEOPARD_INFO, objectPosition);
		for (int i = 0; i < 3; i++)
		{
			leopard = new Leopard(objectPosition[i][0]);
			leopard->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
			leopard->nx = -1;
			leopard->direction = -1;
			leopard->posY = objectPosition[i][2] + 80;
			//objects.push_back(leopard);
			listEnemies.push_back(leopard);
			listLeopards.push_back(leopard);
			grid->insertObjectIntoGrid(leopard);
		}
	}
	else if (simon->x >= 2366)
	{
		objectPosition.clear();
		game->LoadObjectPositionFromFile(LEOPARD_INFO, objectPosition);
		for (int i = 0; i < 3; i++)
		{
			leopard = new Leopard(objectPosition[i][0]);
			leopard->SetPosition(objectPosition[i][1], objectPosition[i][2] + 80);
			leopard->nx = 1;
			leopard->direction = 1;
			leopard->posY = objectPosition[i][2] + 80;
			//objects.push_back(leopard);
			listEnemies.push_back(leopard);
			listLeopards.push_back(leopard);
			grid->insertObjectIntoGrid(leopard);
		}
	}
}

int SceneManager::CheckCollisionnBetweenSimonAndUpStair()
{
	for (int i = 0; i < listStairs.size(); i++)
	{
		float simonL, simonT, simonR, simonB;
		float stairL, stairT, stairR, stairB;
		listStairs[i]->GetBoundingBox(stairL, stairT, stairR, stairB);
		simon->GetBoundingBox(simonL, simonT, simonR, simonB);

		if (listStairs[i]->state == UP_STAIR)
		{
			if (simon->SweptAABBExtend(simonL, simonT, simonR, simonB, stairL, stairT, stairR, stairB) == true)
			{
				if (simon->isOnStair == true)
					simon->isOnStair = false;
				else if (simon->isOnStair == false)
				{
					if (simon->x > listStairs[i]->x)
					{
						simon->SetState(SIMON_STATE_WALKING);
						simon->nx = -1;
					}
					else if (simon->x < listStairs[i]->x - 2)
					{
						simon->SetState(SIMON_STATE_WALKING);
						simon->nx = 1;
					}
					else
					{
						if ((listStairs[i]->nx) == 1)
						{
							simon->SetState(SIMON_STATE_GO_UP_STAIR);
							simon->SetPosition(simon->x - 2, simon->y);
							simon->nx = 1;
							simon->isUpOrDown = true;	// go down stair
						}
						else if (listStairs[i]->nx == -1)
						{
							simon->SetState(SIMON_STATE_GO_UP_STAIR);
							simon->SetPosition(simon->x + 2, simon->y);
							simon->nx = -1;
							simon->isUpOrDown = true;	// go down stair
						}
						simon->isOnStair = true;

					}
					return true;
				}
			}
		}

	}
	return false;
}

int SceneManager::CheckCollisionnBetweenSimonAndDownStair()
{
	for (int i = 0; i < listStairs.size(); i++)
	{
		float simonL, simonT, simonR, simonB;
		float stairL, stairT, stairR, stairB;
		listStairs[i]->GetBoundingBox(stairL, stairT, stairR, stairB);
		simon->GetBoundingBox(simonL, simonT, simonR, simonB);

		if (listStairs[i]->state == DOWN_STAIR)
		{
			if (simon->SweptAABBExtend(simonL, simonT, simonR, simonB, stairL, stairT, stairR, stairB) == true)
			{
				if ((simon->isOnStair) == true)
				{
					if (simon->nx == 1)
						simon->SetPosition(simon->x + 2, simon->y);
					else if (simon->nx == -1)
						simon->SetPosition(simon->x - 2, simon->y);
					simon->vy = 9999999;
					simon->SetState(SIMON_STATE_IDLE);
					simon->isOnStair = false;
				}
				else if (simon->isOnStair == false)
				{
					if (simon->x > 3872 && simon->x < 3900)
						return false;
					if (simon->x > listStairs[i]->x + 10) {
						simon->SetState(SIMON_STATE_WALKING);
						simon->nx = -1;
					}
					else if (simon->x < listStairs[i]->x - 6) {
						simon->SetState(SIMON_STATE_WALKING);
						simon->nx = 1;
					}
					else if (simon->x >= listStairs[i]->x  && simon->x <= listStairs[i]->x + 10)
					{
						if (listStairs[i]->nx == 1)
						{
							simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
							simon->SetPosition(simon->x, simon->y + 2);
							simon->nx = 1;
							simon->isUpOrDown = false;		// go down stair
						}
						else if (listStairs[i]->nx == -1)
						{
							simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
							simon->SetPosition(simon->x, simon->y + 2);
							simon->nx = -1;
							simon->isUpOrDown = false;		// go down stair
						}
						simon->isOnStair = true;
						return true;
					}
				}
				return true;
			}
		}
	}
	return false;
}

void SceneManager::SetItemOnDestroy()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Candle*> (objects[i]))
		{
			Candle *candle = dynamic_cast<Candle*>(objects[i]);

			if (candle->GetState() == CANDLE_DESTROY)
			{
				if (candle->itemInside == 0)
				{
					Item *item = new Item();
					item->isVisible = true;
					item->SetPosition(candle->x, candle->y);
					item->SetState(candle->item);
					//objects.push_back(item);
					grid->insertObjectIntoGrid(item);
					listItems.push_back(item);
					candle->itemInside += 1;
				}			
			}
		}
		else if (dynamic_cast<Zombie*> (objects[i]))
		{
			Zombie *zom = dynamic_cast<Zombie*>(objects[i]);

			if (zom->GetState() == ZOMBIE_DESTROY)
			{
				if (zom->itemInside == 0)
				{
					Item *item = new Item();
					item->isVisible = true;
					item->SetPosition(zom->x, zom->y);
					item->SetItem();
					grid->insertObjectIntoGrid(item);
					//objects.push_back(item);
					listItems.push_back(item);
					zom->itemInside += 1;
				}
			}
		}
		else if (dynamic_cast<Leopard*> (objects[i]))
		{
			Leopard *leo = dynamic_cast<Leopard*> (objects[i]);
			if (leo->GetState() == LEOPARD_DESTROY)
			{
				if (leo->itemInside == 0)
				{
					Item *item = new Item();
					item->isVisible = true;
					item->SetPosition(leo->x, leo->y);
					item->SetItem();
					grid->insertObjectIntoGrid(item);
					//objects.push_back(item);
					listItems.push_back(item);
					leo->itemInside += 1;
				}
			}
		}
		else if (dynamic_cast<Bat*> (objects[i]))
		{
			Bat *bat = dynamic_cast<Bat*> (objects[i]);
			if (bat->GetState() == BAT_DESTROY)
			{
				if (bat->itemInside == 0)
				{
					Item *item = new Item();
					item->isVisible = true;
					item->SetPosition(bat->x, bat->y);
					item->SetItem();
					grid->insertObjectIntoGrid(item);
					//objects.push_back(item);
					listItems.push_back(item);
					bat->itemInside += 1;
				}
			}
		}
		else if (dynamic_cast<FishMan*> (objects[i]))
		{
			FishMan *fm = dynamic_cast<FishMan*> (objects[i]);
			if (fm->GetState() == FISHMAN_DESTROY)
			{
				if (fm->itemInside == 0)
				{
					Item *item = new Item();
					item->isVisible = true;
					item->SetPosition(fm->x, fm->y);
					item->SetItem();
					grid->insertObjectIntoGrid(item);
					//objects.push_back(item);
					listItems.push_back(item);
					fm->itemInside += 1;
				}
			}
		}
		else if (dynamic_cast<Ground*>(objects[i]))
		{
			Ground *gr = dynamic_cast<Ground*>(objects[i]);
			if (gr->GetState() == GROUND_DESTROY)
			{
				if (gr->itemInside == 0)
				{
					effects = new BrickEffects();
					effects->SetPosition(gr->x, gr->y);
					listEffects.push_back(effects);
					gr->itemInside += 1;
				}	
				if (effects->isDone)
				{
					if (gr->itemInside == 1)
					{
						Item *item = new Item();
						item->isVisible = true;
						item->SetPosition(gr->x, gr->y);
						item->SetState(gr->what);
						grid->insertObjectIntoGrid(item);
						//objects.push_back(item);
						listItems.push_back(item);
						gr->itemInside += 1;
					}
				}
			}
		}
		else if (dynamic_cast<Boss*>(objects[i]))
		{
			Boss *bo = dynamic_cast<Boss*>(objects[i]);
			if (bo->GetState() == BOSS_DIE)
			{
				if (bo->itemInside == 0)
				{
					Item * item = new Item();
					item->isVisible = true;
					item->SetPosition(game->GetCameraPosition().x + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					item->SetState(ITEM_BALL);
					grid->insertObjectIntoGrid(item);
					listItems.push_back(item);
					bo->itemInside += 1;
				}
				simon->win = true;
			}
		}
	}
}	