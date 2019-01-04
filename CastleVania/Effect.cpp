#include "Effect.h"



Effect::Effect()
{
	//turnon = false;
	//AddAnimation(EFFECT_ANI);
	//AddAnimation(EFFECT_ANI_OFF);

	//SetState(EFFECT_OFF);
	//item = new Item();
}


Effect::~Effect()
{
}

void Effect::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	

	//LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	//LPANIMATION	ani;

	//vector<vector<int>> resources;
	//Game::GetInstance()->LoadObjectPositionFromFile(L"Resources\\effect.txt", resources);

	//for (int i = 0; i < resources.size(); i++)
	//{
	//	if (resources[i][0] == 1)
	//	{
	//		sprites->Add(resources[i][1], resources[i][2], resources[i][3], resources[i][4], resources[i][5], texEffect);
	//	}
	//	else if (resources[i][0] == 2)
	//	{
	//		ani = new Animation(100);
	//		for (int j = 2; j < resources[i].size(); j++)
	//			ani->Add(resources[i][j]);
	//		animations->Add(resources[i][1], ani);
	//	}
	//}
}

void Effect::Render()
{
	//animations[state]->Render(nx, x, y);
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* objects, vector<LPGAMEOBJECT*>* coObjects)
{
	//GameObject::Update(dt);

	//if (state == EFFECT && GetTickCount() - timer > 300)
	//{
	//	isVisible = false;

	//	Item *item = new Item();
	//	item->isVisible = true;
	//	item->SetPosition(x, y);
	//	item->SetItem();
	//}
}

void Effect::SetState(int state)
{
	GameObject::Update(state);

	switch (state)
	{
	case EFFECT:
		//if (turnon == false)
		//{
		//	timer = GetTickCount();
		//	turnon = true;
		//}
		
		break;

	case EFFECT_OFF:
		break;

	default:
		break;
	}
}
