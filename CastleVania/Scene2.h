//#pragma once
//#include "Scene.h"
//
//class Scene2: public Scene
//{
//
//public:
//	Scene2();
//	~Scene2();
//	D3DXVECTOR3 cam;
//
//	bool isSitting = false;	// check if simon is sitting
//	bool isRenderDone(DWORD time);
//	DWORD leftTimer;
//	DWORD rightTimer;
//	DWORD batTimer;
//	DWORD fishmanTimer;
//	DWORD subWeaponTimer;
//	bool isChangingScene;
//
//	int scene;
//	int stage;
//
//	virtual void KeyState(BYTE *state);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//
//	virtual void LoadGameResource();
//	virtual void Update(DWORD dt);
//	virtual void Render();
//
//	virtual void Draw();
//
//	void spawnZombie(int nx, float x, float y);
//	void spawnBat(Simon* simon);
//	void SpawnFishMan(int nx, Simon* simon);
//
//	int CheckCollisionnBetweenSimonAndUpStair();
//	int CheckCollisionnBetweenSimonAndDownStair();
//};
//
