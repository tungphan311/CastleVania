#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "TileMap.h"
#include "Define.h"
#include "Simon.h"
#include "Whip.h"
#include "Candle.h"
#include "Ground.h"
#include "Item.h"
#include "Dagger.h"
#include "Stair.h"
#include "Leopard.h"
#include "Bat.h"
#include "Gate.h"
#include "Effect.h"
#include "FireBomb.h"
#include "Axe.h"
#include "Boomerang.h"
#include "FishMan.h"
#include "FireBall.h"

class Scene
{
public:
	bool nextScene;

	Scene();

	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	virtual void LoadGameResource() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void Draw() = 0;
};

