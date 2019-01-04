//#include "Scene2.h"
//
//
//Game *game2 = Game::GetInstance();
//Simon *simon2;
//TileMap *tileMap2;
//Ground *ground2;
//Dagger *dagger2;
//Whip *whip2;
//Candle *candle2;
//Item *item2;
//Zombie *zombie2;
//Stair *stair2;
//Leopard *leopard2;
//Bat *bat;
//FishMan *fishman2;
//FireBall *fireball2;
//Gate *gate;
//Effect *effect2;
//FireBomb *firebomb2;
//Axe *axe2;
//Boomerang *boomerang2;
//SubWeapon *subWeapon2 = SubWeapon::GetInstance();
//
//Textures *textures = Textures::GetInstance();
//Sprites *sprites = Sprites::GetInstance();
//Animations *animations = Animations::GetInstance();
//
//vector<LPGAMEOBJECT> objects2;
//vector<LPGAMEOBJECT> listEnemies2;
//vector<LPGAMEOBJECT> listStairs;
//vector<LPGAMEOBJECT> listFishMan2;
//
//Scene2::Scene2(): Scene()
//{
//	scene = SCENE_2;
//	stage = 1;
//	LoadGameResource();
//	Draw();
//
//	leftTimer = GetTickCount();
//	rightTimer = GetTickCount() + 4000;
//	batTimer = GetTickCount() + 5000;
//	fishmanTimer = GetTickCount() - 7000;
//}
//
//Scene2::~Scene2()
//{
//}
//
//bool Scene2::isRenderDone(DWORD time)
//{
//	return GetTickCount() - simon2->timer > time;
//}
//
//#pragma region __KEY_HANDLER__
//
//void Scene2::OnKeyDown(int KeyCode)
//{
//	if (simon2->isHitGate) return;
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		if (simon2->GetState() == SIMON_STATE_JUMP || simon2->isOnStair == true || simon2->isOnStair)
//			return;
//		simon2->SetState(SIMON_STATE_JUMP);
//		break;
//
//	case DIK_C:
//		if (simon2->GetState() == SIMON_STATE_IDLE || simon2->GetState() == SIMON_STATE_JUMP || simon2->GetState() == SIMON_STATE_WALKING)
//			simon2->SetState(SIMON_STATE_HIT_STANDING);
//		else if (simon2->GetState() == SIMON_STATE_SIT)
//			simon2->SetState(SIMON_STATE_HIT_SITTING);
//		else if (simon2->isOnStair == true)
//		{
//			if (simon2->isUpOrDown == true)
//				simon2->SetState(SIMON_STATE_HIT_UP_STAIR);
//			else if (simon2->isUpOrDown == false)
//				simon2->SetState(SIMON_STATE_HIT_DOWN_STAIR);
//		}
//			
//		break;
//
//#pragma region __USE_SUB_WEAPON__
//	case DIK_Z:
//		if (simon2->powerUp == false)
//			return;
//		if (simon2->allowUseSubWeapon == false)
//			return;
//		if (subWeapon2->GetState() == DAGGER) {
//			if (simon2->GetState() == SIMON_STATE_IDLE || simon2->GetState() == SIMON_STATE_JUMP) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				dagger2->SetPosition(simonX, simonY + 10);
//				dagger2->SetOrientation(simon2->GetOrientation());
//				dagger2->isVisible = true;
//				simon2->SetState(SIMON_STATE_THROW_STAND);
//				simon2->allowUseSubWeapon = false;
//				subWeaponTimer = GetTickCount();
//			}
//			else if (simon2->GetState() == SIMON_STATE_SIT) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				dagger2->SetPosition(simonX, simonY + 20);
//				dagger2->SetOrientation(simon2->GetOrientation());
//				dagger2->isVisible = true;
//				simon2->SetState(SIMON_STATE_THROW_SIT);
//				simon2->allowUseSubWeapon = false;
//				subWeaponTimer = GetTickCount();
//			}
//		}
//		else if (subWeapon2->GetState() == WATCH)
//		{
//			for (int i = 0; i < objects2.size(); i++)
//			{
//				objects2[i]->currentState = objects2[i]->GetState();
//				objects2[i]->isFreeze = true;
//				objects2[i]->freeze_start = GetTickCount();
//				simon2->allowUseSubWeapon = false;
//				subWeaponTimer = GetTickCount();
//			}
//		}
//		else if (subWeapon2->GetState() == FIRE_BOMB)
//		{
//			if (simon2->GetState() == SIMON_STATE_IDLE || simon2->GetState() == SIMON_STATE_JUMP) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				firebomb2->SetPosition(simonX, simonY + 10);
//				firebomb2->SetOrientation(simon2->GetOrientation());
//				firebomb2->isVisible = true;
//				firebomb2->SetState(FB_THROW);
//				simon2->SetState(SIMON_STATE_THROW_STAND);
//				simon2->allowUseSubWeapon = false;
//				subWeaponTimer = GetTickCount();
//			}
//			else if (simon2->GetState() == SIMON_STATE_SIT) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				firebomb2->SetPosition(simonX, simonY + 20);
//				firebomb2->SetOrientation(simon2->GetOrientation());
//				firebomb2->isVisible = true;
//				firebomb2->SetState(FB_THROW);
//				simon2->SetState(SIMON_STATE_THROW_SIT);
//				simon2->allowUseSubWeapon = false;
//				subWeaponTimer = GetTickCount();
//			}
//		}
//		else if (subWeapon2->GetState() == AXE)
//		{
//			if (simon2->GetState() == SIMON_STATE_IDLE || simon2->GetState() == SIMON_STATE_JUMP) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				axe2->SetPosition(simonX, simonY + 10);
//				axe2->SetOrientation(simon2->GetOrientation());
//				axe2->isVisible = true;
//				axe2->SetState(AXE_THROW);
//				simon2->SetState(SIMON_STATE_THROW_STAND);
//			}
//			else if (simon2->GetState() == SIMON_STATE_SIT) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				axe2->SetPosition(simonX, simonY + 20);
//				axe2->SetOrientation(simon2->GetOrientation());
//				axe2->isVisible = true;
//				axe2->SetState(AXE_THROW);
//				simon2->SetState(SIMON_STATE_THROW_SIT);
//			}
//		}
//		else if (subWeapon2->GetState() == BOOMERANG)
//		{
//			if (simon2->GetState() == SIMON_STATE_IDLE || simon2->GetState() == SIMON_STATE_JUMP) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				boomerang2->posX = simonX;
//				boomerang2->SetPosition(simonX, simonY + 10);
//				boomerang2->SetOrientation(simon2->GetOrientation());
//				boomerang2->isVisible = true;
//				boomerang2->SetState(BOOMERANG_THROW);
//				simon2->SetState(SIMON_STATE_THROW_STAND);
//			}
//			else if (simon2->GetState() == SIMON_STATE_SIT) {
//				float simonX, simonY;
//				simon2->GetPosition(simonX, simonY);
//				boomerang2->posX = simonX;
//				boomerang2->SetPosition(simonX, simonY + 20);
//				boomerang2->SetOrientation(simon2->GetOrientation());
//				boomerang2->isVisible = true;
//				boomerang2->SetState(BOOMERANG_THROW);
//				simon2->SetState(SIMON_STATE_THROW_SIT);
//			}
//		}
//		break;
//#pragma endregion
//
//#pragma region __SET_SUBWEAPON__
//	case DIK_1:
//		simon2->powerUp = true;
//		subWeapon2->replaceSubWeapon(DAGGER);
//		break;
//
//	case DIK_2:
//		simon2->powerUp = true;
//		subWeapon2->replaceSubWeapon(AXE);
//		break;
//
//	case DIK_3:
//		simon2->powerUp = true;
//		subWeapon2->replaceSubWeapon(FIRE_BOMB);
//		break;
//
//	case DIK_4:
//		simon2->powerUp = true;
//		subWeapon2->replaceSubWeapon(WATCH);
//		break;
//
//	case DIK_5:
//		simon2->powerUp = true;
//		subWeapon2->replaceSubWeapon(BOOMERANG);
//#pragma endregion
//
//#pragma region __SET_SIMON_POSITION__
//	case DIK_A:
//		stage = 1;
//		simon2->SetPosition(50, 60);
//		break;
//
//	case DIK_S:
//		stage = 1;
//		simon2->SetPosition(2920, 60);
//		break;
//
//	case DIK_D:
//		stage = 2;
//		simon2->SetPosition(3230, 60);
//		break;
//
//	case DIK_F:
//		stage = 2;
//		simon2->SetPosition(3970, 60);
//		break;
//#pragma endregion
//	
//	//case DIK_DOWN:
//	//	if (simon2->isOnStair)
//	//		return;
//	//	simon2->SetState(SIMON_STATE_SIT);
//	//	isSitting = true;
//	//	break;
//	}	
//}
//
//void Scene2::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//
//	//if (KeyCode == DIK_DOWN)
//	//	isSitting = false;
//}
//
//void Scene2::KeyState(BYTE * state)
//{
//	if (simon2->GetState() == SIMON_STATE_JUMP && simon2->GetVy() != 0)
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_POWER_UP && !isRenderDone(300))
//		return;
//
//	if ((simon2->GetState() == SIMON_STATE_THROW_STAND) && !isRenderDone(300))
//		return;
//
//	if ((simon2->GetState() == SIMON_STATE_THROW_SIT) && !isRenderDone(300))
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_HIT_STANDING && !isRenderDone(300))
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_HIT_SITTING && !isRenderDone(300))
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_SIT && isSitting)
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_INJURED && !isRenderDone(200))
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_HIT_UP_STAIR && !isRenderDone(300))
//		return;
//
//	if (simon2->GetState() == SIMON_STATE_HIT_DOWN_STAIR && !isRenderDone(300))
//		return;
//
//	if (simon2->isHitGate) return;
//
//	if (game2->IsKeyDown(DIK_RIGHT)) {
//		if (!simon2->isOnStair)
//		{
//			simon2->SetState(SIMON_STATE_WALKING);
//			simon2->nx = 1;
//		}
//		else if (simon2->isOnStair)
//		{
//			if (simon2->isUpOrDown == false)
//			{
//				if (simon2->nx > 0) {
//					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
//						simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//						simon2->nx = 1;
//					}
//				}
//				else if (simon2->nx < 0) {
//					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
//						simon2->isUpOrDown = true;		// go up stair
//						simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//						simon2->nx = 1;
//					}
//				}			
//			}
//			else if (simon2->isUpOrDown == true)
//			{
//				if (simon2->nx > 0) {
//					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
//						simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//						simon2->nx = 1;
//					}
//				}
//				else if (simon2->nx < 0) {
//					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
//						simon2->isUpOrDown = false;		// go down stair
//						simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//						simon2->nx = 1;
//					}
//				}
//			}
//		}
//			
//	}
//	else if (game2->IsKeyDown(DIK_LEFT)) {
//		if (!simon2->isOnStair) {
//			simon2->SetState(SIMON_STATE_WALKING);
//			simon2->nx = -1;
//		}
//		else if (simon2->isOnStair)
//		{
//			if (simon2->isUpOrDown == false)
//			{
//				if (simon2->nx > 0) {
//					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
//						simon2->isUpOrDown = true;		// go up stair
//						simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//						simon2->nx = -1;
//					}
//				}
//				else if (simon2->nx < 0) {
//					if (CheckCollisionnBetweenSimonAndUpStair() == false) {
//						simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//						simon2->nx = -1;
//					}
//				}
//			}
//			else if (simon2->isUpOrDown == true)
//			{
//				if (simon2->nx > 0) {
//					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
//						simon2->isUpOrDown = false;		// go down stair
//						simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//						simon2->nx = -1;
//					}
//				}
//				else if (simon2->nx < 0) {
//					if (CheckCollisionnBetweenSimonAndDownStair() == false) {
//						simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//						simon2->nx = -1;
//					}
//				}
//			}
//		}
//		
//	}
//	else if (game2->IsKeyDown(DIK_UP)) {
//		if(simon2->isOnStair == false) {
//			CheckCollisionnBetweenSimonAndUpStair();
//		}
//		else if (simon2->isOnStair)
//		{
//			if (CheckCollisionnBetweenSimonAndDownStair() == false)
//			{
//				if (simon2->isUpOrDown == true)
//				{
//					simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//				}
//				else if (!simon2->isUpOrDown)
//				{
//					simon2->isUpOrDown = true;
//					simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//					simon2->nx = -simon2->nx;
//				}
//			}
//		}
//	}
//	else if (game2->IsKeyDown(DIK_DOWN)) {
//		if (simon2->isOnStair == false) {
//			if (CheckCollisionnBetweenSimonAndDownStair() == false)
//				simon2->SetState(SIMON_STATE_SIT);
//				
//		}
//		else if (simon2->isOnStair)
//		{
//			if (CheckCollisionnBetweenSimonAndUpStair() == false)
//			{
//				if (simon2->isUpOrDown == false)
//				{
//					simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//				}
//				else if(simon2->isUpOrDown == true)
//				{
//					simon2->isUpOrDown = false;
//					simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//					simon2->nx = -simon2->nx;
//				}
//			}
//		}		
//	}
//	else
//	{
//		if (simon2->isOnStair == false)
//			simon2->SetState(SIMON_STATE_IDLE);
//		else if (simon2->isOnStair == true)
//		{
//			if (simon2->isUpOrDown == true) {
//				simon2->SetState(SIMON_STATE_IDLE_UP_STAIR);
//
//			}
//			else if (simon2->isUpOrDown == false)
//			{
//				simon2->SetState(SIMON_STATE_IDLE_DOWN_STAIR);
//			}
//		}
//	}
//}
//
//#pragma endregion
//
//
//void Scene2::LoadGameResource()
//{
//	simon2 = new Simon();
//	simon2->LoadResources(textures, sprites, animations);
//
//	ground2 = new Ground();
//	ground2->LoadResources(textures, sprites, animations);
//
//	whip2 = new Whip();
//	whip2->LoadResources(textures, sprites, animations);
//
//	candle2 = new Candle();
//	candle2->LoadResources(textures, sprites, animations);
//
//	item2 = new Item();
//	item2->LoadResources(textures, sprites, animations);
//
//	zombie2 = new Zombie();
//	zombie2->LoadResources(textures, sprites, animations);
//
//	leopard2 = new Leopard();
//	leopard2->LoadResources(textures, sprites, animations);
//
//	bat = new Bat();
//	bat->LoadResources(textures, sprites, animations);
//
//	gate = new Gate();
//	gate->LoadResources(textures, sprites, animations);
//
//	effect2 = new Effect();
//	effect2->LoadResources(textures, sprites, animations);
//
//	firebomb2 = new FireBomb();
//	firebomb2->LoadResources(textures, sprites, animations);
//
//	axe2 = new Axe();
//	axe2->LoadResources(textures, sprites, animations);
//
//	boomerang2 = new Boomerang();
//	boomerang2->LoadResources(textures, sprites, animations);
//
//	fishman2 = new FishMan();
//	fishman2->LoadResources(textures, sprites, animations);
//
//	fireball2 = new FireBall();
//	fireball2->LoadResources(textures, sprites, animations);
//}
//
//void Scene2::Update(DWORD dt)
//{
//	if (simon2->allowUseSubWeapon == false && GetTickCount() - subWeaponTimer > 2000)
//		simon2->allowUseSubWeapon = true;
//
//	if (scene == SCENE2)
//	{
//		//DebugOut(L"Stage: %d\n", stage);
//		if (stage == 1) {
//			if (!simon2->isHitGate) {
//				// render camera
//				float cx, cy;
//				simon2->GetPosition(cx, cy);
//
//				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap2->GetMapWidth())
//					game2->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
//
//				if (cx + SCREEN_WIDTH / 2 > 3088)
//					game2->SetCameraPosition(3088 - SCREEN_WIDTH, 0);
//			}
//#pragma region __PASSING_DOOR__
//			else 
//			{
//				DebugOut(L"Camera Position: %f\n", game2->GetCameraPosition().x);
//
//				if (game2->GetCameraPosition().x <= 2800)
//				{
//					game2->SetCameraPosition(game2->GetCameraPosition().x + 2, 0);
//				}
//				else if (game2->GetCameraPosition().x > 2800)
//				{
//					if (simon2->x < 3136) {
//						gate->SetState(GATE_OPENING);
//						if (isRenderDone(200)) {
//							gate->SetState(GATE_OPENED);
//							simon2->SetState(SIMON_STATE_WALKING);
//						}
//					}
//					else
//					{
//						simon2->SetState(SIMON_STATE_IDLE);
//						gate->SetState(GATE_CLOSE);
//						if (isRenderDone(200))
//							gate->SetState(GATE_INACTIVE);
//
//						if (game2->GetCameraPosition().x < 3071)
//						{
//							game2->SetCameraPosition(game2->GetCameraPosition().x + 2, 0);
//						}
//						if (game2->GetCameraPosition().x >= 3072) {
//							simon2->isHitGate = false;
//							stage = 2;
//						}
//					}
//				}
//			}
//#pragma endregion		
//		}
//		else if (stage == 2)
//		{
//			if (simon2->isHitGate == false) {
//				// render camera
//				float cx, cy;
//				simon2->GetPosition(cx, cy);
//
//				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap2->GetMapWidth())
//					game2->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
//
//				if (cx - SCREEN_WIDTH / 2 < 3072)
//					game2->SetCameraPosition(3072, 0);
//
//				if (simon2->x > 5626 && simon2->x < 6636 - SIMON_BBOX_WIDTH)
//				{
//					if (game2->GetCameraPosition().x + SCREEN_WIDTH >= 6652)
//						game2->SetCameraPosition(6652 - SCREEN_WIDTH, 0);
//					if (game2->GetCameraPosition().x < 5626)
//						game2->SetCameraPosition(5628, 0);
//
//#pragma region __SPAWN_FISHMAN__
//					if (GetTickCount() - fishmanTimer > 8000) {
//						if (listFishMan2.size() == 0) {
//							SpawnFishMan(1, simon2);
//							SpawnFishMan(-1, simon2);
//						}
//						else if (listFishMan2.size() == 1)
//						{
//							SpawnFishMan(rand() % 2 == 0 ? 1 : -1, simon2);
//						}
//						fishmanTimer = GetTickCount();
//					}
//
//					for (int i = 0; i < objects2.size(); i++)
//					{
//						if (dynamic_cast<FishMan*>(objects2[i]))
//						{
//							FishMan *f = dynamic_cast<FishMan*>(objects2[i]);
//
//							if (f->GetState() == FISHMAN_SHOT)
//							{
//								if (f->nx == 1) {
//									fireball2->SetPosition(f->x + FISHMAN_BBOX_WIDTH, f->y + 4);
//									fireball2->SetOrientation(1);
//								}
//								else if (f->nx == -1)
//								{
//									fireball2->SetPosition(f->x, f->y + 4);
//									fireball2->SetOrientation(-1);
//								}
//								fireball2->isVisible = true;
//								fireball2->SetState(FIREBALL);
//								objects2.push_back(fireball2);
//								listEnemies2.push_back(fireball2);
//							}						
//						}
//					}					
//				}
//#pragma endregion
//
//				if (game2->GetCameraPosition().x + SCREEN_WIDTH > 4112 && simon2->x < 4112)
//					game2->SetCameraPosition(4112 - SCREEN_WIDTH, 0);
//			}
//			else if (simon2->isHitGate == true)
//			{
//				if (game2->GetCameraPosition().x <= 3850)
//				{
//					game2->SetCameraPosition(game2->GetCameraPosition().x + 2, 0);
//				}
//				if (game2->GetCameraPosition().x > 3850)
//				{
//					if (simon2->x < 4160) {
//						gate->SetState(GATE_OPENING);
//						if (isRenderDone(200)) {
//							gate->SetState(GATE_OPENED);
//							simon2->SetState(SIMON_STATE_WALKING);
//						}
//					}
//					else
//					{
//						simon2->SetState(SIMON_STATE_IDLE);
//						gate->SetState(GATE_CLOSE);
//						if (isRenderDone(200))
//							gate->SetState(GATE_INACTIVE);
//
//						if (game2->GetCameraPosition().x < 4080)
//						{
//							game2->SetCameraPosition(game2->GetCameraPosition().x + 2, 0);
//						}
//						if (game2->GetCameraPosition().x >= 4080) {
//							simon2->isHitGate = false;
//							stage = 3;
//							rightTimer = GetTickCount() - 5000;
//							leftTimer = GetTickCount();
//						}
//					}
//				}
//			}
//		}
//		else if (stage == 3)
//		{
//			if (game2->GetCameraPosition().x < 5628 - SCREEN_WIDTH) {
//				// render camera
//				float cx, cy;
//				simon2->GetPosition(cx, cy);
//
//				if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap2->GetMapWidth())
//					game2->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
//
//				if (game2->GetCameraPosition().x < 4080)
//					game2->SetCameraPosition(4080, 0);
//			}			
//			else
//			{
//				game2->SetCameraPosition(5628 - SCREEN_WIDTH, 0);
//				if (simon2->x - 14 <= 5628 - SCREEN_WIDTH)
//					simon2->x = 5628 + 14 - SCREEN_WIDTH;
//			}
//		}
//
//#pragma region __SPAWN_ZOMBIE__
//
//		if ((simon2->x - SCREEN_WIDTH / 2 < 832) || (simon2->x + SCREEN_WIDTH / 2 > 2368 && simon2->x + SCREEN_WIDTH / 2 < 3056)) {
//			// left every 10s
//			if (GetTickCount() - leftTimer > ZOMBIE_LEFT_SPAWN_TIME)
//			{
//				spawnZombie(1, simon2->x - SCREEN_WIDTH / 2 + 1.0f, 256.0f);
//				leftTimer = GetTickCount();
//			}
//			// right every 6s 
//			if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
//			{
//				for (int i = 0; i < 3; i++)
//				{
//					spawnZombie(-1, game2->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f);
//					rightTimer = GetTickCount();
//				}
//			}
//		}
//
//		if (game2->GetCameraPosition().x == 4080)
//		{
//			if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
//			{
//				for (int i = 0; i < 3; i++)
//				{
//					spawnZombie(-1, game2->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f);
//					spawnZombie(-1, game2->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 128.0f);
//					rightTimer = GetTickCount();
//				}
//			}
//		}
//		else if (game2->GetCameraPosition().x > 4080 && game2->GetCameraPosition().x + SCREEN_WIDTH < 5628 - SCREEN_WIDTH)
//		{
//			// left every 10s
//			if (GetTickCount() - leftTimer > ZOMBIE_LEFT_SPAWN_TIME)
//			{
//				spawnZombie(1, simon2->x - SCREEN_WIDTH / 2 + 1.0f, 256.0f);
//				leftTimer = GetTickCount();
//			}
//			// right every 6s 
//			if (GetTickCount() - rightTimer > ZOMBIE_RIGHT_SPAWN_TIME)
//			{
//				for (int i = 0; i < 3; i++)
//				{
//					spawnZombie(-1, game2->GetCameraPosition().x + SCREEN_WIDTH + 60 * i - ZOMBIE_BBOX_WIDTH, 256.0f);
//					rightTimer = GetTickCount();
//				}
//			}
//		}
//#pragma endregion
//
//#pragma region __SPAWN_BAT__
//
//		if (simon2->x > 3136 && simon2->x < 4032 && !simon2->isHitGate)
//		{
//			if (GetTickCount() - batTimer > BAT_SPAWN_TIME)
//			{
//				spawnBat(simon2);
//				batTimer = GetTickCount();
//			}			
//		}
//#pragma endregion
//	
//	}
//		
//#pragma region __UPDATE__
//	//tạo 1 con trỏ cấp 2 để có thể thay đổi object trong hàm update 
//	for (int i = 0; i < objects2.size(); i++)
//	{
//		if (objects2[i]->isVisible == false)
//			continue;
//
//		vector<LPGAMEOBJECT*> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects
//
//		if (dynamic_cast<Simon*>(objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				if (i != j) // thêm tất cả objects "ko phải là simon", dùng trong hàm update của simon 
//					coObjects.push_back(&(objects2[j]));
//			}
//		}
//		else if (dynamic_cast<Item*>(objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				if (dynamic_cast<Ground*>(objects2[j])) // thêm tất cả objects "là ground", dùng trong hàm update của item
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<Zombie*>(objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				// thêm ground vào coObject dùng trong hàm update của Zombie
//				if (dynamic_cast<Ground*>(objects2[j])) {
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<Leopard*>(objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				// thêm ground vào coObject dùng trong hàm update của Leopard
//				if (dynamic_cast<Ground*>(objects2[j])) {
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<Dagger*> (objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				// thêm Candle vào coObject dùng trong hàm update của Dagger
//				if (dynamic_cast<Candle*>(objects2[j])) {
//					coObjects.push_back(&(objects2[j]));
//				}
//				else if (dynamic_cast<Zombie*>(objects2[j])) // thêm Zombie vào coObject dùng trong hàm update của dagger
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//				else if (dynamic_cast<Leopard*>(objects2[j])) // thêm Leopard vào coObject dùng trong hàm update của dagger
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//				else if (dynamic_cast<Bat*>(objects2[j])) // thêm Bat vào coObject dùng trong hàm update của dagger
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//				else if (dynamic_cast<FishMan*> (objects2[j]))
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<FireBomb*>(objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				if (dynamic_cast<Ground*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Zombie*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Leopard*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Bat*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Candle*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<FishMan*> (objects2[j]))
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<Axe*> (objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				if (dynamic_cast<Zombie*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Leopard*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Bat*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Candle*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<FishMan*> (objects2[j]))
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<Boomerang*> (objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				if (dynamic_cast<Zombie*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Leopard*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Bat*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Candle*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<Simon*> (objects2[j])) {
//					coObjects.push_back(&objects2[j]);
//				}
//				else if (dynamic_cast<FishMan*> (objects2[j]))
//				{
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else if (dynamic_cast<FishMan*> (objects2[i]))
//		{
//			for (int j = 0; j < objects2.size(); j++)
//			{
//				if (objects2[j]->isVisible == false)
//					continue;
//
//				// thêm ground vào coObject dùng trong hàm update của Leopard
//				if (dynamic_cast<Ground*>(objects2[j])) {
//					coObjects.push_back(&(objects2[j]));
//				}
//			}
//		}
//		else
//		{
//			coObjects.push_back(&(objects2[i]));
//		}
//
//		objects2[i]->Update(dt, &objects2, &coObjects);
//	}
//
//	// xoá tất cả các objects có Visible = false ra khỏi vector
//	for (int i = 0; i < objects2.size(); i++) {
//		if (dynamic_cast<Item*>(objects2[i])) {
//			if (objects2[i]->isVisible == FALSE) {
//				objects2.erase(objects2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<Candle*>(objects2[i])) {
//			if (objects2[i]->isVisible == FALSE) {
//				objects2.erase(objects2.begin() + i);
//				i -= 1;
//			}
//		}
//	}
//
//	// xoá tất cả các objects có Visible = false ra khỏi vector
//	for (int i = 0; i < listEnemies2.size(); i++) {
//		if (dynamic_cast<Zombie*> (listEnemies2[i])) {
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		if (dynamic_cast<Candle*> (listEnemies2[i])) {
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<Bat*>(listEnemies2[i]))
//		{
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<Candle*>(listEnemies2[i]))
//		{
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<FishMan*>(listEnemies2[i]))
//		{
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<Leopard*>(listEnemies2[i]))
//		{
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//		else if (dynamic_cast<FireBall*>(listEnemies2[i]))
//		{
//			if (listEnemies2[i]->isVisible == FALSE) {
//				listEnemies2.erase(listEnemies2.begin() + i);
//				i -= 1;
//			}
//		}
//	}
//
//
//	for (int i = 0; i < listFishMan2.size(); i++)
//	{
//		if (listFishMan2[i]->isVisible == FALSE) {
//			listFishMan2.erase(listFishMan2.begin() + i);
//			i -= 1;
//		}
//	}
//#pragma endregion
//
//	DebugOut(L"List Enemy: %d\n", listEnemies2.size());
//	//DebugOut(L"Objects: %d\n", objects2.size());
//}
//
//void Scene2::Render()
//{
//	LPDIRECT3DDEVICE9 d3ddv = game2->GetDirect3DDevice();
//	LPDIRECT3DSURFACE9 bb = game2->GetBackBuffer();
//	LPD3DXSPRITE spriteHandler = game2->GetSpriteHandler();
//
//	if (d3ddv->BeginScene())
//	{
//		// Clear back buffer with a color
//		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
//
//		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
//
//		tileMap2->Draw(game2->GetCameraPosition());
//
//		for (int i = 0; i < objects2.size(); i++) {
//			if (objects2[i]->isVisible == false)
//				continue;
//
//			objects2[i]->Render();
//		}
//
//		spriteHandler->End();
//		d3ddv->EndScene();
//	}
//
//	//Display back buffer content to the screen
//	d3ddv->Present(NULL, NULL, NULL, NULL);
//}
//
//void Scene2::Draw()
//{
//	objects2.clear();
//
//	if (scene == SCENE1)
//	{
//		dagger2 = new Dagger();
//		dagger2->isVisible = false;
//		objects2.push_back(dagger2);
//
//		simon2 = new Simon();
//		simon2->SetPosition(5.0f, 224.0f);
//		objects2.push_back(simon2);
//
//		candle2 = new Candle();
//		candle2->AddAnimation(BIG_CANDLE_ANI);
//		candle2->SetPosition(100.0f, 224.0f);
//		objects2.push_back(candle2);
//
//		candle2 = new Candle();
//		candle2->AddAnimation(BIG_CANDLE_ANI);
//		candle2->SetPosition(230.0f, 224.0f);
//		objects2.push_back(candle2);
//
//		candle2 = new Candle();
//		candle2->AddAnimation(BIG_CANDLE_ANI);
//		candle2->SetPosition(360.0f, 224.0f);
//		objects2.push_back(candle2);
//
//		candle2 = new Candle();
//		candle2->AddAnimation(BIG_CANDLE_ANI);
//		candle2->SetPosition(490.0f, 224.0f);
//		objects2.push_back(candle2);
//
//		candle2 = new Candle();
//		candle2->AddAnimation(BIG_CANDLE_ANI);
//		candle2->SetPosition(600.0f, 224.0f);
//		objects2.push_back(candle2);
//
//		for (int i = 0; i < 48; i++) {
//			ground2 = new Ground(GROUND);
//			ground2->SetPosition(32 * i, 288.0f);
//			objects2.push_back(ground2);
//		}
//
//		tileMap2 = new TileMap(0, L"Resources\\Scenes\\lv1.png", L"Resources\\Scenes\\lv1.txt", 1536, 320, 32, 32);
//		tileMap2->LoadSpritesFromFile();
//		tileMap2->LoadMatrixFromFile();
//	}
//	else if (scene == SCENE2)
//	{
//		simon2 = new Simon();
//		simon2->SetPosition(50, 60.0f);
//		objects2.push_back(simon2);
//
//#pragma region __SUB_WEAPON__
//		dagger2 = new Dagger();
//		dagger2->isVisible = false;
//		objects2.push_back(dagger2);
//
//		firebomb2 = new FireBomb();
//		firebomb2->isVisible = false;
//		objects2.push_back(firebomb2);
//
//		axe2 = new Axe();
//		axe2->isVisible = false;
//		objects2.push_back(axe2);
//
//		boomerang2 = new Boomerang();
//		boomerang2->isVisible = false;
//		objects2.push_back(boomerang2);
//
//		fireball2 = new FireBall();
//		fireball2->isVisible = false;
//		//fireball2->SetPosition(60, 250);
//		//objects2.push_back(fireball2);
//#pragma endregion
//
//#pragma region __GROUND__
//		for (int i = 0; i < 176; i++) {
//			if (i == 99 || i == 112 || i == 113 || i == 114 || i == 115 || i == 119)
//				continue;
//			ground2 = new Ground(GROUND);
//			ground2->SetPosition(i * 32, 322.0f);
//			objects2.push_back(ground2);
//		}
//		for (int i = 0; i < 21; i++) {
//			if (i == 3 || i == 14)
//				continue;
//			else {
//				ground2 = new Ground(GROUND);
//				if (3 < i&&i < 14)
//					ground2->SetPosition(1376 + i * 32, 130.0f);
//				else
//					ground2->SetPosition(1376 + i * 32, 194.0f);
//				objects2.push_back(ground2);
//			}
//		}
//		for (int i = 0; i < 20; i++) {
//			ground2 = new Ground(GROUND);
//			if (16 < i&&i < 20)
//				ground2->SetPosition(2784 + i * 32, 194.0f);
//			else
//				ground2->SetPosition(2784 + i * 32, 130.0f);
//			objects2.push_back(ground2);
//		}
//		for (int i = 0; i < 6; i++) {
//			for (int j = 0; j < 4; j++) {
//				if (i == 3 && j == 0) {
//					ground2 = new Ground(GROUND_3);
//					ground2->SetPosition(3584 + 32 * j, 160 + 32 * i);
//					objects2.push_back(ground2);
//				}
//				else if (i == 4 && j == 0) {
//					ground2 = new Ground(GROUND_4);
//					ground2->SetPosition(3584 + 32 * j, 160 + 32 * i);
//					objects2.push_back(ground2);
//				}
//				else {
//					ground2 = new Ground(GROUND);
//					ground2->SetPosition(3584 + 32 * j, 160 + 32 * i);
//					objects2.push_back(ground2);
//				}			
//			}
//		}
//		for (int i = 0; i < 10; i++) {
//			if (i > 0 && i < 5)
//				continue;
//			else {
//				ground2 = new Ground(GROUND);
//				ground2->SetPosition(3056.0f, 0 + 32 * i);
//				objects2.push_back(ground2);
//			}
//		}
//		for (int i = 0; i < 31; i++) {
//			if (i == 5 || i == 19)
//				continue;
//			else {
//				ground2 = new Ground(GROUND);
//				if (i == 0 || i == 1)
//					ground2->SetPosition(3712 + i * 32, 160.0f);
//				else if (i > 1 && i < 5 || i>19)
//					ground2->SetPosition(3712 + i * 32, 194.0f);
//				else
//					ground2->SetPosition(3712 + i * 32, 130.0f);
//				objects2.push_back(ground2);
//			}
//
//		}
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(4032.0f, 0);
//		objects2.push_back(ground2);
//
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(4064.0f, 0);
//		objects2.push_back(ground2);
//		for (int i = 0; i < 6; i++) {
//			if (i == 2)
//				continue;
//			else 
//				if (i == 0) {
//					ground2 = new Ground(GROUND);
//					ground2->SetPosition(5440 + 32 * i, 256.0f);
//					objects2.push_back(ground2);
//				}
//				else if (i == 1) {
//					ground2 = new Ground(GROUND_2);
//					ground2->SetPosition(5440 + 32 * i, 256.0f);
//					objects2.push_back(ground2);
//				}
//				else {
//					ground2 = new Ground(GROUND);
//					ground2->SetPosition(5440 + 32 * i, 194.0f);
//					objects2.push_back(ground2);
//				}
//		}
//		for (int i = 0; i < 10; i++) {
//			if (2 < i&&i < 7)
//				continue;
//			else {
//				ground2 = new Ground(GROUND);
//				ground2->SetPosition(5616.0f, 0 + 32 * i);
//				objects2.push_back(ground2);
//			}
//		}
//
//		for (int i = 0; i < 32; i++) {
//			if (i == 14 || i == 15 || i == 18 || i == 19)
//				continue;
//			if (i < 30) {
//				ground2 = new Ground(GROUND);
//				ground2->SetPosition(5632 + 32 * i, 160.0f);
//				objects2.push_back(ground2);
//			}
//			else {
//				ground2 = new Ground(GROUND);
//				ground2->SetPosition(5632 + 32 * i, 224.0f);
//				objects2.push_back(ground2);
//			}
//		}
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(6528.0f, 288.0f);
//		objects2.push_back(ground2);
//
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(6560.0f, 288.0f);
//		objects2.push_back(ground2);
//
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(5824, 96);
//		objects2.push_back(ground2);
//
//		ground2 = new Ground(GROUND);
//		ground2->SetPosition(5856, 96);
//		objects2.push_back(ground2);
//
//#pragma endregion
//
//#pragma region __CANDLE__
//		for (int i = 0; i < 9; i++) {
//			if (i % 2 == 0) {
//				candle2 = new Candle(SMALL_CANDLE);
//				candle2->SetPosition(54.0f + 258 * i / 2, 258.0f);
//				objects2.push_back(candle2);
//				listEnemies2.push_back(candle2);
//			}
//			else {
//				candle2 = new Candle(SMALL_CANDLE);
//				candle2->SetPosition(186.0f + 258 * (i - 1) / 2, 198.0f);
//				objects2.push_back(candle2);
//				listEnemies2.push_back(candle2);
//			}
//		}
//		candle2 = new Candle(SMALL_CANDLE);
//		candle2->SetPosition(2800.0f, 198.0f);
//		objects2.push_back(candle2);
//
//#pragma endregion
//
//#pragma region __STAIR__
//		// cầu thang 1
//		stair2 = new Stair(UP_STAIR, 1);
//		stair2->SetPosition(1216.0f, 318.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(DOWN_STAIR, -1);
//		stair2->SetPosition(1344.0f, 102.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang 2
//		stair2 = new Stair(UP_STAIR, 1);
//		stair2->SetPosition(1408.0f, 190.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(DOWN_STAIR, -1);
//		stair2->SetPosition(1472.0f, 38.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//
//		// cầu thang 3
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(1792.0f, 38.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(1856.0f, 190.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang cuối cảnh 1
//		stair2 = new Stair(UP_STAIR, 1);
//		stair2->SetPosition(2560.0f, 318.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(DOWN_STAIR, -1);
//		stair2->SetPosition(2752.0f, 38.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang xuống ăn gà
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(3392.0f, 102.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(3520.0f, 318.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang đi xuống màn dưới nước
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(3136.0f, 230.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(5792, 88.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang đi lên lại
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(3776, 230.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(6498, 142);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang 4
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(3840, 104.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(3970, 316.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang 5
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(4288, 38.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(4352, 190.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang qua màn đánh boss
//		stair2 = new Stair(UP_STAIR, -1);
//		stair2->SetPosition(4800, 318.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(DOWN_STAIR, 1);
//		stair2->SetPosition(4672, 102.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		// cầu thang màn đánh boss
//		stair2 = new Stair(UP_STAIR, 1);
//		stair2->SetPosition(5400, 240);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//		stair2 = new Stair(DOWN_STAIR, -1);
//		stair2->SetPosition(5504, 102.0f);
//		objects2.push_back(stair2);
//		listStairs.push_back(stair2);
//
//#pragma endregion
//
//#pragma region __LEOPARD__
//
//		leopard2 = new Leopard(1);
//		leopard2->SetPosition(1376.0f, 162.0f);
//		objects2.push_back(leopard2);
//		listEnemies2.push_back(leopard2);
//
//		leopard2 = new Leopard(2);
//		leopard2->SetPosition(1760.0f, 97.0f);
//		objects2.push_back(leopard2);
//		listEnemies2.push_back(leopard2);
//
//		leopard2 = new Leopard(3);
//		leopard2->SetPosition(1856.0f, 162.0f);
//		objects2.push_back(leopard2);
//		listEnemies2.push_back(leopard2);
//#pragma endregion
//
//		gate = new Gate();
//		gate->SetPosition(3053.0f, 32.0f);
//		objects2.push_back(gate);
//
//		gate = new Gate();
//		gate->SetPosition(4073, 32.0f);
//		objects2.push_back(gate);
//
//		// load map
//		tileMap2 = new TileMap(0, L"Resources\\Scenes\\lv2.png", L"Resources\\Scenes\\lv2.txt", 6688, 352, 32, 32);
//		tileMap2->LoadSpritesFromFile();
//		tileMap2->LoadMatrixFromFile();
//	}
//	
//}
//
//void Scene2::spawnZombie(int nx, float x, float y)
//{
//	zombie2 = new Zombie(nx);
//	zombie2->SetPosition(x, y);
//	objects2.push_back(zombie2);
//	listEnemies2.push_back(zombie2);
//}
//
//void Scene2::spawnBat(Simon* simon)
//{
//	bat = new Bat(-simon->nx, simon->y +25);
//	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
//	
//	if (bat->nx > 0)
//		bat->SetPosition(cam.x, simon->y + 25);
//	else if (bat->nx < 0)
//		bat->SetPosition(cam.x + SCREEN_WIDTH - BAT_BBOX_WIDTH, simon->y + 25);	
//	objects2.push_back(bat);
//	listEnemies2.push_back(bat);
//}
//
//void Scene2::SpawnFishMan(int nx, Simon* simon)
//{
//	D3DXVECTOR3 cam = game2->GetCameraPosition();
//
//	fishman2 = new FishMan(nx);
//	if (nx > 0)
//	{
//		int fx = rand() % ((int)simon->x - (int)cam.x + 1) + ((int)cam.x + 1);
//		DebugOut(L"Fish man X = %d", fx);
//		fishman2->SetPosition(fx, 222);
//	}
//	else if (nx < 0)
//	{
//		int fx = rand() % ((int)cam.x + SCREEN_WIDTH - (int)simon->x - SIMON_BBOX_WIDTH) + ((int)simon->x + SIMON_BBOX_WIDTH + 1);
//		DebugOut(L"Fish man X = %d", fx);
//		fishman2->SetPosition(fx, 222);
//	}
//	objects2.push_back(fishman2);
//	listEnemies2.push_back(fishman2);
//	listFishMan2.push_back(fishman2);
//}
//
//int Scene2::CheckCollisionnBetweenSimonAndUpStair()
//{
//	for (int i = 0; i < listStairs.size(); i++)
//	{
//		float simonL, simonT, simonR, simonB;
//		float stairL, stairT, stairR, stairB;
//		listStairs[i]->GetBoundingBox(stairL, stairT, stairR, stairB);
//		simon2->GetBoundingBox(simonL, simonT, simonR, simonB);
//
//		if (listStairs[i]->state == UP_STAIR)
//		{
//			if (simon2->SweptAABBExtend(simonL, simonT, simonR, simonB, stairL, stairT, stairR, stairB) == true)
//			{
//				if (simon2->isOnStair == true)
//					simon2->isOnStair = false;
//				else if (simon2->isOnStair == false)
//				{
//					if (simon2->x > listStairs[i]->x)
//					{
//						simon2->SetState(SIMON_STATE_WALKING);
//						simon2->nx = -1;
//					}
//					else if (simon2->x < listStairs[i]->x - 2)
//					{
//						simon2->SetState(SIMON_STATE_WALKING);
//						simon2->nx = 1;
//					}
//					else
//					{
//						if ((listStairs[i]->nx) == 1)
//						{
//							simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//							simon2->SetPosition(simon2->x - 2, simon2->y);
//							simon2->nx = 1;
//							simon2->isUpOrDown = true;	// go down stair
//						}
//						else if (listStairs[i]->nx == -1)
//						{
//							simon2->SetState(SIMON_STATE_GO_UP_STAIR);
//							simon2->SetPosition(simon2->x + 2, simon2->y);
//							simon2->nx = -1;
//							simon2->isUpOrDown = true;	// go down stair
//						}
//						simon2->isOnStair = true;
//						
//					}	
//					return true;
//				}				
//			}
//		}
//
//	}
//	return false;
//}
//
//int Scene2::CheckCollisionnBetweenSimonAndDownStair()
//{
//	for (int i = 0; i < listStairs.size(); i++)
//	{
//		float simonL, simonT, simonR, simonB;
//		float stairL, stairT, stairR, stairB;
//		listStairs[i]->GetBoundingBox(stairL, stairT, stairR, stairB);
//		simon2->GetBoundingBox(simonL, simonT, simonR, simonB);
//
//		if (listStairs[i]->state == DOWN_STAIR)
//		{
//			if (simon2->SweptAABBExtend(simonL, simonT, simonR, simonB, stairL, stairT, stairR, stairB) == true)
//			{
//				if ((simon2->isOnStair) == true)
//				{
//					if (simon2->nx == 1)
//						simon2->SetPosition(simon2->x + 2, simon2->y);
//					else if (simon2->nx == -1)
//						simon2->SetPosition(simon2->x - 2, simon2->y);
//					simon2->vy = 9999999;
//					simon2->SetState(SIMON_STATE_IDLE);
//					simon2->isOnStair = false;
//				}
//				else if (simon2->isOnStair == false)
//				{
//					if (simon2->x > listStairs[i]->x + 10) {
//						simon2->SetState(SIMON_STATE_WALKING);
//						simon2->nx = -1;
//					}
//					else if (simon2->x < listStairs[i]->x - 6) {
//						simon2->SetState(SIMON_STATE_WALKING);
//						simon2->nx = 1;
//					}
//					else if (simon2->x >= listStairs[i]->x  && simon2->x <= listStairs[i]->x + 10)
//					{
//						if (listStairs[i]->nx == 1)
//						{
//							simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//							simon2->SetPosition(simon2->x, simon2->y + 2);
//							simon2->nx = 1;
//							simon2->isUpOrDown = false;		// go down stair
//						}
//						else if (listStairs[i]->nx == -1)
//						{
//							simon2->SetState(SIMON_STATE_GO_DOWN_STAIR);
//							simon2->SetPosition(simon2->x, simon2->y + 2);
//							simon2->nx = -1; 
//							simon2->isUpOrDown = false;		// go down stair
//						}
//						simon2->isOnStair = true;
//						return true;
//					}
//				}	
//				return true;
//			}			
//		}
//	}
//	return false;
//}
//
