#include "ScoreBoard.h"



ScoreBoard::ScoreBoard()
{
	nx = -1;
	font = NULL;
	D3DXCreateFont(Game::GetInstance()->GetDirect3DDevice(), 0, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI", &font);
	healBar = 17;
	playerHeal = 17;
	enemyHeal = 17;
	time = 300;
	heart = 5;
	playerLife = 3;
	score = 0;
	AddAnimation(SCORE_BOARD_ANI);

	SetState(SCORE_BOARD);
}


ScoreBoard::~ScoreBoard()
{
	
}

void ScoreBoard::LoadResources(Textures *& textures, Sprites *& sprites, Animations *& animations)
{
	textures->Add(ID_TEX_SCORE_BOARD, BOARD_TEXTURE, D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_HEAL, HEAL_TEXTURE, D3DCOLOR_XRGB(255, 0, 255));
}

void ScoreBoard::Update(DWORD dt, Simon * simon, SubWeapon * subWeapon, Boss *boss)
{
	GameObject::Update(dt);
	x = Game::GetInstance()->GetCameraPosition().x;

	// set sub-weapon
	if (simon->powerUp == false)
		this->subWeapon = -1;
	else
	{
		this->subWeapon = subWeapon->GetState();
	}

	// set player heal
	playerHeal = simon->HP;
	heart = simon->heart;
	playerLife = simon->life;
	score = simon->point;
	enemyHeal = boss->HP;
	doubleShot = simon->doubleShot;
}

void ScoreBoard::Render()
{
	// vẽ scoreboard
	Game::GetInstance()->Draw(nx, x, y, Textures::GetInstance()->Get(ID_TEX_SCORE_BOARD), 0, 0, 520, 79);

	// vẽ subweapon
	if (subWeapon == 0)
		Game::GetInstance()->Draw(-1, x + 280, y + 40, Textures::GetInstance()->Get(ID_TEX_ITEM_DAGGER), 0, 0, 32, 18);
	else if (subWeapon == 1)
		Game::GetInstance()->Draw(-1, x + 280, y + 32, Textures::GetInstance()->Get(ID_TEX_ITEM_AXE), 0, 0, 30, 28);
	else if (subWeapon == 2)
		Game::GetInstance()->Draw(-1, x + 280, y + 32, Textures::GetInstance()->Get(ID_TEX_ITEM_FIRE_BOMB), 0, 0, 32, 32);
	else if (subWeapon == 3)
		Game::GetInstance()->Draw(-1, x + 280, y + 32, Textures::GetInstance()->Get(ID_TEX_ITEM_WATCH), 0, 0, 30, 32);
	else if (subWeapon == 4)
		Game::GetInstance()->Draw(-1, x + 280, y + 32, Textures::GetInstance()->Get(ID_TEX_ITEM_BOOMERANG), 0, 0, 32, 32);

	// vẽ máu của player và boss
	for (int i = 0; i < healBar; i++)
	{
		Game::GetInstance()->Draw(-1, x + 105 + 8*i + 1, y + 30, Textures::GetInstance()->Get(ID_TEX_HEAL), 8, 0, 16, 12);
		Game::GetInstance()->Draw(-1, x + 105 + 8 * i + 1, y + 48, Textures::GetInstance()->Get(ID_TEX_HEAL), 8, 0, 16, 12);
	}

	for (int i = 0; i < playerHeal; i++)
		Game::GetInstance()->Draw(-1, x + 105 + 8 * i + 1, y + 30, Textures::GetInstance()->Get(ID_TEX_HEAL), 0, 0, 8, 12);

	for (int i = 0; i < enemyHeal; i++)
		Game::GetInstance()->Draw(-1, x + 105 + 8 * i + 1, y + 48, Textures::GetInstance()->Get(ID_TEX_HEAL), 16, 0, 24, 12);
	
	// tính toán thời gian
	SetRect(&rect, 280, 8, 373, 26);
	string timeLeft = std::to_string(time);
	while (timeLeft.length() < 4)
	{
		timeLeft = '0' + timeLeft;
	}
	font->DrawTextA(NULL, timeLeft.c_str(), -1, &rect, DT_VCENTER | DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));

	// đặt giá trị cho stage
	SetRect(&rect, 457, 8, 520, 26);
	string scene = std::to_string(stage);
	scene = '0' + scene;
	font->DrawTextA(NULL, scene.c_str(), -1, &rect, DT_VCENTER | DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));

	// hiện giá trị của heart
	SetRect(&rect, 378, 28, 444, 49);
	string simonHeart = std::to_string(heart);
	if (simonHeart.length() < 2)
		simonHeart = '0' + simonHeart;
	font->DrawTextA(NULL, simonHeart.c_str(), -1, &rect, DT_VCENTER | DT_LEFT | DT_TOP, D3DCOLOR_XRGB(255, 255, 255));

	// hiện giá trị của life
	SetRect(&rect, 378, 54, 444, 75);
	string simonLife = std::to_string(playerLife);
	if (simonLife.length() < 2)
		simonLife = '0' + simonLife;
	font->DrawTextA(NULL, simonLife.c_str(), -1, &rect, DT_VCENTER | DT_LEFT | DT_TOP, D3DCOLOR_XRGB(255, 255, 255));

	// hiện giá trị score
	SetRect(&rect, 100, 8, 212, 26);
	string point = std::to_string(score);
	while (point.length() < 6)
		point = '0' + point;
	font->DrawTextA(NULL, point.c_str(), -1, &rect, DT_VCENTER | DT_LEFT | DT_TOP, D3DCOLOR_XRGB(255, 255, 255));

	// vẽ double shot
	if (doubleShot)
	{
		Game::GetInstance()->Draw(-1, 410, 42, Textures::GetInstance()->Get(ID_TEX_ITEM_DOUBLE_SHOT), 0, 0, 28, 28);
	}
}
