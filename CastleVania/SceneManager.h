#pragma once
#include "Game.h"
#include "Simon.h"

class SceneManager
{
	static SceneManager *__instance;

public:
	SceneManager();
	~SceneManager();
	void Init(int scene);
	void SetNextScene(int scene);

	bool win;

	int scene;
	int stage;
	int timeCount;
	int simonRespawn;
	bool isSitting = false;
	bool pause;
	DWORD pause_timer;
	bool IsRenderDone(DWORD time);
	DWORD leftTimer;
	DWORD rightTimer;
	DWORD batTimer;
	DWORD fishmanTimer;
	DWORD subWeaponTimer;
	bool isChangingScene;
	DWORD crossTimer;
	bool changeBackcolor;
	DWORD backcolorTimer;

	int heal;
	int score;
	int heart;
	int life;
	int whipState;
	bool isPowerUp;
	int simonSubWeapon;

	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	static SceneManager * GetInstance();
	void LoadGameResource();
	void Update(DWORD dt);
	void Render();

	void Draw();

	void spawnZombie(int nx, float x, float y);
	void spawnBat(Simon* simon);
	void SpawnFishMan(int nx, Simon* simon);
	void SpawnFireBall();
	void RespawnLeopard(Simon *simon);

	int CheckCollisionnBetweenSimonAndUpStair();
	int CheckCollisionnBetweenSimonAndDownStair();

	void SetItemOnDestroy();
};

