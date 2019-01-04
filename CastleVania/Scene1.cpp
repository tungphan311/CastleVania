//#include "Scene1.h"
//
//Game *game = Game::GetInstance();
//TileMap *tileMap;
//Simon *simon;
//Whip *whip;
//Candle *candle;
//Ground *ground;
//Item *item;
//Dagger *dagger;
//SubWeapon *subWeapon;
//
//vector<LPGAMEOBJECT> objects;
//
//Scene1::Scene1(): Scene()
//{
//	LoadGameResource();
//	Draw();
//}
//
//Scene1::~Scene1()
//{
//}
//
//#pragma region __KEY_HANDLE__
//void Scene1::OnKeyDown(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		if (simon->GetState() == SIMON_STATE_JUMP)
//			return;
//		simon->SetState(SIMON_STATE_JUMP);
//		break;
//
//	case DIK_C:
//		if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP || simon->GetState() == SIMON_STATE_WALKING)
//			simon->SetState(SIMON_STATE_HIT_STANDING);
//		else if (simon->GetState() == SIMON_STATE_SIT)
//			simon->SetState(SIMON_STATE_HIT_SITTING);
//		break;
//
//	case DIK_Z:
//		if (simon->powerUp == false)
//			return;
//
//		if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_JUMP) {
//			float simonX, simonY;
//			simon->GetPosition(simonX, simonY);
//			dagger->SetPosition(simonX, simonY + 10);
//			dagger->SetOrientation(simon->GetOrientation());
//			dagger->isVisible = true;
//			simon->SetState(SIMON_STATE_THROW_STAND);
//		}
//		else if (simon->GetState() == SIMON_STATE_SIT) {
//			float simonX, simonY;
//			simon->GetPosition(simonX, simonY);
//			dagger->SetPosition(simonX, simonY + 20);
//			dagger->SetOrientation(simon->GetOrientation());
//			dagger->isVisible = true;
//			simon->SetState(SIMON_STATE_THROW_SIT);
//		}
//		break;
//
//	case DIK_DOWN:
//		simon->SetState(SIMON_STATE_SIT);
//		isSitting = true;
//	}
//}
//
//void Scene1::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//
//	if (KeyCode == DIK_DOWN)
//		isSitting = false;
//}
//
//bool Scene1::isRenderDone(DWORD time)
//{
//	return GetTickCount() - simon->timer > time;
//}
//
//void Scene1::KeyState(BYTE * state)
//{
//	if (simon->GetState() == SIMON_STATE_JUMP && simon->GetVy() != 0)
//		return;
//
//	if (simon->GetState() == SIMON_STATE_POWER_UP && !isRenderDone(300))
//		return;
//
//	if ((simon->GetState() == SIMON_STATE_THROW_STAND) && !isRenderDone(300))
//		return;
//
//	if ((simon->GetState() == SIMON_STATE_THROW_SIT) && !isRenderDone(300))
//		return;
//
//	if (simon->GetState() == SIMON_STATE_HIT_STANDING && !isRenderDone(300))
//		return;
//
//	if (simon->GetState() == SIMON_STATE_HIT_SITTING && !isRenderDone(300))
//		return;
//
//	if (simon->GetState() == SIMON_STATE_SIT && isSitting)
//		return;
//
//	if (game->IsKeyDown(DIK_RIGHT)) {
//		simon->SetState(SIMON_STATE_WALKING);
//		simon->nx = 1;
//	}
//	else if (game->IsKeyDown(DIK_LEFT)) {
//		simon->SetState(SIMON_STATE_WALKING);
//		simon->nx = -1;
//	}
//	else if (game->IsKeyDown(DIK_DOWN)) {
//		simon->SetState(SIMON_STATE_SIT);
//	}
//	else
//		simon->SetState(SIMON_STATE_IDLE);
//}
//#pragma endregion
//
//void Scene1::LoadGameResource()
//{
//	Textures *textures = Textures::GetInstance();
//	Sprites *sprites = Sprites::GetInstance();
//	Animations *animations = Animations::GetInstance();
//
//	simon = new Simon();
//	simon->LoadResources(textures, sprites, animations);
//
//	whip = new Whip();
//	whip->LoadResources(textures, sprites, animations);
//
//	candle = new Candle();
//	candle->LoadResources(textures, sprites, animations);
//
//	ground = new Ground();
//	ground->LoadResources(textures, sprites, animations);
//
//	item = new Item();
//	item->LoadResources(textures, sprites, animations);
//}
//
//void Scene1::Update(DWORD dt)
//{
//	//tạo 1 con trỏ cấp 2 để có thể thay đổi object trong hàm update 
//	for (int i = 0; i < objects.size(); i++)
//	{
//		if (objects[i]->isVisible == false)
//			continue;
//
//		vector<LPGAMEOBJECT*> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects
//
//		if (dynamic_cast<Simon*>(objects[i]))
//		{
//			for (int j = 0; j < objects.size(); j++)
//			{
//				if (objects[j]->isVisible == false)
//					continue;
//
//				if (i != j) // thêm tất cả objects "ko phải là simon", dùng trong hàm update của simon 
//					coObjects.push_back(&(objects[j]));
//			}
//		}
//		else if (dynamic_cast<Item*>(objects[i]))
//		{
//			for (int j = 0; j < objects.size(); j++)
//			{
//				if (objects[i]->isVisible == false)
//					continue;
//
//				if (dynamic_cast<Ground*>(objects[j])) // thêm tất cả objects "là ground", dùng trong hàm update của item
//				{
//					coObjects.push_back(&(objects[j]));
//				}
//			}
//		}
//		else
//		{
//			coObjects.push_back(&(objects[i]));
//		}
//
//
//		objects[i]->Update(dt, &objects, &coObjects);
//	}
//
//	// render camera
//	float cx, cy;
//	simon->GetPosition(cx, cy);
//
//	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tileMap->GetMapWidth())
//		game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
//}
//
//void Scene1::Render()
//{
//	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
//	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
//	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
//
//	if (d3ddv->BeginScene())
//	{
//		// Clear back buffer with a color
//		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
//
//		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
//
//		tileMap->Draw(game->GetCameraPosition());
//
//		for (int i = 0; i < objects.size(); i++) {
//			if (objects[i]->isVisible == false)
//				continue;
//
//			objects[i]->Render();
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
//void Scene1::Draw()
//{
//	objects.clear();
//
//	dagger = new Dagger();
//	dagger->isVisible = false;
//	objects.push_back(dagger);
//
//	simon = new Simon();
//	simon->SetPosition(5.0f, 224.0f);
//	objects.push_back(simon);
//
//	candle = new Candle();
//	candle->AddAnimation(BIG_CANDLE_ANI);
//	candle->SetPosition(100.0f, 224.0f);
//	objects.push_back(candle);
//
//	candle = new Candle();
//	candle->AddAnimation(BIG_CANDLE_ANI);
//	candle->SetPosition(230.0f, 224.0f);
//	objects.push_back(candle);
//
//	candle = new Candle();
//	candle->AddAnimation(BIG_CANDLE_ANI);
//	candle->SetPosition(360.0f, 224.0f);
//	objects.push_back(candle);
//
//	candle = new Candle();
//	candle->AddAnimation(BIG_CANDLE_ANI);
//	candle->SetPosition(490.0f, 224.0f);
//	objects.push_back(candle);
//
//	candle = new Candle();
//	candle->AddAnimation(BIG_CANDLE_ANI);
//	candle->SetPosition(600.0f, 224.0f);
//	objects.push_back(candle);
//
//
//	for (int i = 0; i < 48; i++) {
//		ground = new Ground(GROUND_1);
//		ground->AddAnimation(GROUND_1_ANI);
//		ground->SetPosition(32 * i, 288.0f);
//		objects.push_back(ground);
//	}
//
//	tileMap = new TileMap(0, L"Resources\\Scenes\\lv1.png", L"Resources\\Scenes\\lv1.txt", 1536, 320, 32, 32);
//	tileMap->LoadSpritesFromFile();
//	tileMap->LoadMatrixFromFile();
//}
