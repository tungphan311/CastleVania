//#include "Start.h"
//
//
//Start::Start(int state): GameObject()
//{
//	SetState(state);
//
//	AddAnimation(CASTLE_ANI);
//	AddAnimation(CASTLE_1_ANI);
//	AddAnimation(MESSAGE_ANI);
//}
//
//Start::~Start()
//{
//}
//
//void Start::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
//{
//	textures->Add(ID_TEX_CASTLE, L"Resources\\Scenes\\castle.png", D3DCOLOR_XRGB(255, 0, 255));
//	textures->Add(ID_TEX_MESSAGE, L"Resources\\Scenes\\castle.png", D3DCOLOR_XRGB(0, 0, 0));
//
//	LPDIRECT3DTEXTURE9 texCastle = textures->Get(ID_TEX_CASTLE);
//	LPDIRECT3DTEXTURE9 texMess = textures->Get(ID_TEX_MESSAGE);
//
//	sprites->Add(180001, 0, 0, 144, 112, texCastle);
//	sprites->Add(180002, 144, 0, 288, 112, texCastle);
//	sprites->Add(180003, 288, 0, 432, 112, texCastle);
//	sprites->Add(180004, 432, 0, 576, 112, texCastle);
//	sprites->Add(180005, 576, 0, 720, 112, texCastle);
//	sprites->Add(180006, 0, 112, 144, 224, texCastle);
//	sprites->Add(180007, 144, 112, 288, 224, texCastle);
//	sprites->Add(180008, 288, 112, 432, 224, texCastle);
//	sprites->Add(180009, 432, 112, 576, 224, texCastle);
//	sprites->Add(180010, 576, 112, 720, 224, texCastle);
//	sprites->Add(180011, 0, 224, 144, 336, texCastle);
//	sprites->Add(180012, 144, 224, 288, 336, texCastle);
//	sprites->Add(180013, 288, 224, 432, 336, texCastle);
//	sprites->Add(180014, 432, 224, 576, 336, texCastle);
//	sprites->Add(180015, 576, 224, 720, 336, texCastle);
//
//	sprites->Add(180016, 0, 0, 226, 15, texMess);
//	sprites->Add(180017, 0, 0, 0, 0, texMess);
//
//	LPANIMATION ani;
//	ani = new Animation(100);
//	for (int i = 180001; i < 180013; i++)
//		ani->Add(i);
//	animations->Add(CASTLE_ANI, ani);
//
//	ani = new Animation(100);
//	ani->Add(180013);
//	ani->Add(180014);
//	ani->Add(180015);
//	animations->Add(CASTLE_1_ANI, ani);
//
//	ani = new Animation(100);
//	ani->Add(180016);
//	ani->Add(180017);
//	animations->Add(MESSAGE_ANI, ani);
//}
//
//void Start::Update(DWORD dt, vector<LPGAMEOBJECT>* objects, vector<LPGAMEOBJECT*>* coObjects)
//{
//	if (state == CASTLE && GetTickCount() - timer > 1200)
//	{
//		SetState(CASTLE_1);
//	}
//}
//
//void Start::Render()
//{
//	animations[state]->Render(-1, x, y);
//}
//
//void Start::SetState(int state)
//{
//	GameObject::SetState(state);
//
//	switch (state)
//	{
//	case CASTLE:
//		timer = GetTickCount();
//		animations[state]->ResetAnimation();
//		break;
//
//	case CASTLE_1:
//		animations[state]->ResetAnimation();
//		break;
//
//	default:
//		break;
//	}
//}
