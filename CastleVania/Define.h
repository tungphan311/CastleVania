	#pragma once

#pragma region _MAIN_

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR_WHITE	D3DCOLOR_XRGB(255,255,255)
#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 480
#define WINDOW_CLASS_NAME L"game-project"
#define MAIN_WINDOW_TITLE L"Castle Vania"
#define MAX_FRAME_RATE 90

#define START_SCENE	0
#define SCENE_1	1
#define SCENE_2	2

#define STAGE_1	1
#define STAGE_2	2
#define STAGE_3	3

#define SPRITES		1
#define ANIMATION	2

#pragma endregion

#pragma region __BOUNDING_BOX__

#define SIMON_BBOX_WIDTH	45
#define SIMON_BBOX_HEIGHT	62

#define WHIP_BBOX_WIDTH		55
#define WHIP_BBOX_HEIGHT	12
#define LONG_CHAIN_BBOX_WIDTH	88

#define BIG_CANDLE_BBOX_WIDTH	32
#define BIG_CANDLE_BBOX_HEIGHT	64

#define GROUND_BBOX_WIDTH	32
#define GROUND_BBOX_HEIGHT	32

#define SMALL_CANLDE_BBOX_WIDTH		16
#define SMALL_CANDLE_BBOX_HEIGHT	32

#define ZOMBIE_BBOX_WIDTH	34
#define ZOMBIE_BBOX_HEIGHT	64

#define STAIR_BBOX_WIDTH	64
#define STAIR_BBOX_HEIGHT	32

// item
#define LARGE_HEART_BBOX_WIDTH	24
#define LARGE_HEART_BBOX_HEIGHT	20

#define CHAIN_BBOX_WIDTH	32
#define CHAIN_BBOX_HEIGHT	32

#define DAGGER_BBOX_WIDTH	32
#define DAGGER_BBOX_HEIGHT	18

#define AXE_BBOX_WIDTH	30
#define AXE_BBOX_HEIGHT	28

#define CROSS_BBOX_WIDTH	32
#define CROSS_BBOX_HEIGHT	32

#define DOUBLE_SHOT_BBOX_WIDTH  28
#define DOUBLE_SHOT_BBOX_HEIGHT	28

#define FIRE_BOMB_BBOX_WIDTH	32
#define FIRE_BOMB_BBOX_HEIGHT	32

#define MONEY_BAG_BBOX_WIDTH	30
#define MONEY_BAG_BBOX_HEIGHT	30

#define SMALL_HEART_BBOX_WIDTH	16
#define SMALL_HEART_BBOX_HEIGHT	16

#define PORK_CHOP_BBOX_WIDTH	32
#define PORK_CHOP_BBOX_HEIGHT	26

#define TRIPLE_SHOT_BBOX_WIDTH	28
#define TRIPLE_SHOT_BBOX_HEIGHT	28

#define WATCH_BBOX_WIDTH	30
#define WATCH_BBOX_HEIGHT	30

#define BALL_BBOX_WIDTH		28
#define BALL_BBOX_HEIGHT	32

#define INVISIBILITY_BBOX_WIDTH		33
#define INVISIBILITY_BBOX_HEIGHT	40

// end item

#define LEOPARD_BBOX_WIDTH	64
#define LEOPARD_BBOX_HEIGHT	32
#define LEOPARD_ACTIVE_BBOX_WIDTH	16
#define LEOPARD_ACTIVE_BBOX_HEIGHT	300

#define BAT_BBOX_WIDTH	32
#define BAT_BBOX_HEIGHT	32

#define GATE_BBOX_WIDTH		16
#define GATE_BBOX_HEIGHT	16

#define FB_BBOX_WIDTH	30
#define FB_BBOX_HEIGHT	25

#define AXE_BBOX_WIDTH	30
#define AXE_BBOX_HEIGHT	28

#define BOOMERANG_BBOX_WIDTH	28
#define BOOMERANG_BBOX_HEIGHT	28

#define FISHMAN_BBOX_WIDTH	32
#define FISHMAN_BBOX_HEIGHT	64

#define FIREBALL_BBOX_WIDTH		14
#define FIREBALL_BBOX_HEIGHT	12

#define BOSS_BBOX_WIDTH		56
#define BOSS_BBOX_HEIGHT	38
	
#pragma endregion

#pragma region __INPUT__

#define KEYBOARD_BUFFER_SIZE 1024

#pragma endregion

#pragma region __SIMON__

#define SIMON_WALKING_SPEED			0.14f 
#define SIMON_JUMP_SPEED_Y			0.55f
#define SIMON_INJURED_DEFLECT_SPEED	0.4f
#define SIMON_GRAVITY				0.002f
#define SIMON_DIE_DEFLECT_SPEED		0.5f
#define SIMON_SPEED_ON_STAIR		0.05625f
#define SIMON_UNTOUCHABLE_TIME		3000

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING			1
#define SIMON_STATE_JUMP			2
#define SIMON_STATE_SIT				3
#define SIMON_STATE_HIT_STANDING	4
#define SIMON_STATE_HIT_SITTING		5
#define SIMON_STATE_POWER_UP		6
#define SIMON_STATE_THROW_STAND		7
#define SIMON_STATE_THROW_SIT		8
#define SIMON_STATE_GO_UP_STAIR		9
#define SIMON_STATE_IDLE_UP_STAIR	10
#define SIMON_STATE_GO_DOWN_STAIR	11
#define SIMON_STATE_IDLE_DOWN_STAIR	12
#define SIMON_STATE_HIT_UP_STAIR	13
#define SIMON_STATE_HIT_DOWN_STAIR	14
#define SIMON_STATE_DIE				15
#define SIMON_STATE_INVISIBLE		16
#define SIMON_STATE_THROW_UP_STAIR	17
#define SIMON_STATE_THROW_DOWN_STAIR	18
#define SIMON_STATE_INJURED_LEFT	19
#define SIMON_STATE_INJURED_RIGHT	20

#define SIMON_ANI_IDLE				0			
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_JUMP				2
#define	SIMON_ANI_SITING			3
#define SIMON_ANI_HIT_STAND			4	
#define SIMON_ANI_HIT_SIT			5
#define SIMON_ANI_POWER_UP			6
#define SIMON_ANI_THROW_STAND		7
#define SIMON_ANI_THROW_SIT			8
#define SIMON_ANI_GO_UP_STAIR		9
#define SIMON_ANI_IDLE_UP_STAIR		10
#define SIMON_ANI_GO_DOWN_STAIR		11
#define SIMON_ANI_IDLE_DOWN_STAIR	12
#define SIMON_ANI_HIT_UP_STAIR		13
#define SIMON_ANI_HIT_DOWN_STAIR	14
#define SIMON_ANI_DIE				15
#define SIMON_ANI_INVISIBLE			16
#define SIMON_ANI_THROW_UP_STAIR	17
#define SIMON_ANI_THROW_DONW_STAIR  18
#define SIMON_ANI_INJURED_LEFT		19
#define SIMON_ANI_INJURED_RIGHT		20

#pragma endregion

#pragma region __TEXTURES_FILEPATH__
#define BAT_TEXTURE				L"Resources\\Enemy\\bat.png"
#define BOSS_TEXTURE			L"Resources\\Enemy\\boss.png"
#define BOSS_DIE_TEXTURE		L"Resources\\Enemy\\boss_die.png"
#define BIG_CANDLE_TEXTURE		L"Resources\\Candle\\candle.png"
#define SMALL_CANDLE_TEXTURE	L"Resources\\Candle\\small_candle.png"
#define EFFECT_TEXTURE			L"Resources\\effect.png"
#define FIREBALL_TEXTURE		L"Resources\\Enemy\\fireball.png"
#define FISHMAN_TEXTURE			L"Resources\\Enemy\\fishman.png"
#define LEOPARD_TEXTURE			L"Resources\\Enemy\\leopard.png"
#define ZOMBIE_TEXTURE			L"Resources\\Enemy\\zombie.png"
#define BOARD_TEXTURE			L"Resources\\board.png"
#define HEAL_TEXTURE			L"Resources\\heal.png"
#define BRICK_DESTROY_EFFECT_TEXTURE	L"Resources\\Effect\\brick_destroy.png"
#define WATER_EFFECT_TEXTURE	L"Resources\\Effect\\water_effect.png"
#define SIMON_TEXTURE			L"Resources\\simon.png"
#define BOUNDINGBOX_TEXTURE		L"Resources\\bbox.png"
#define GATE_TEXTURE			L"Resources\\Ground\\gate.png"
#define GROUND_2_TEXTURE		L"Resources\\Ground\\ground2.png"
#define GROUND_3_TEXTURE		L"Resources\\Ground\\ground3.png"
#define GROUND_4_TEXTURE		L"Resources\\Ground\\ground4.png"
#define ITEM_LARGE_HEART_TEXTURE	L"Resources\\Items\\large_heart.png"
#define ITEM_CHAIN_TEXTURE		L"Resources\\Items\\chain.png"
#define ITEM_DAGGER_TEXTURE		L"Resources\\Items\\dagger.png"
#define ITEM_AXE_TEXTURE		L"Resources\\Items\\axe.png"
#define ITEM_BOOMERANG_TEXTURE	L"Resources\\Items\\boomerang.png"
#define ITEM_CROSS_TEXTURE		L"Resources\\Items\\cross.png"
#define ITEM_DOUBLE_SHOT_TEXTURE	L"Resources\\Items\\double_shot.png"
#define ITEM_FIRE_BOMB_TEXTURE	L"Resources\\Items\\fire_bomb.png"
#define ITEM_MONEY_BAG_TEXTURE	L"Resources\\Items\\money_bag.png"
#define ITEM_PORK_CHOP_TEXTURE	L"Resources\\Items\\pork_chop.png"
#define ITEM_TRIPLE_SHOT_TEXTURE	L"Resources\\Items\\triple_shot.png"
#define ITEM_SMALL_HEART_TEXTURE	L"Resources\\Items\\small_heart.png"
#define ITEM_WATCH_TEXTURE		L"Resources\\Items\\watch.png"
#define ITEM_BALL_TEXTURE		L"Resources\\Items\\ball.png"
#define ITEM_INVISIBILITY_TEXTURE	L"Resources\\Items\\invisibility.png"
#define AXE_TEXTURE				L"Resources\\Weapon\\axe.png"
#define BOOMERANG_TEXTURE		L"Resources\\Weapon\\boomerang.png"
#define FIREBOMB_TEXTURE		L"Resources\\Weapon\\fire-bomb.png"
#define WHIP_TEXTURE			L"Resources\\Weapon\\whip.png"
#define LEVEL1_TEXTURE			L"Resources\\Scenes\\lv1.png"
#define LEVEL2_TEXTURE			L"Resources\\Scenes\\lv2.png"
#define BLACKBOARD_TEXTURE		L"Resources\\blackboard.png"
#pragma endregion

#pragma region __DATA_FILEPATH__
#define BAT_INFO	L"Resources\\Enemy\\bat.txt"
#define BOSS_INFO	L"Resources\\Enemy\\boss.txt"
#define CANDLE_INFO	L"Resources\\Candle\\candle.txt"
#define FIREBALL_INFO	L"Resources\\Enemy\\fireball.txt"
#define FISHMAN_INFO	L"Resources\\Enemy\\fishman.txt"
#define LEOPARD_INFO	L"Resources\\Enemy\\leopard.txt"
#define ZOMBIE_INFO		L"Resources\\Enemy\\zombie.txt"
#define BRICK_DESTROY_INFO	L"Resources\\Effect\\brick_destroy.txt"
#define WATER_EFFECT_INFO	L"Resources\\Effect\\water_effect.txt"
#define SIMON_INFO	L"Resources\\simon.txt"
#define GATE_INFO	L"Resources\\Ground\\gate.txt"
#define GROUND_INFO	L"Resources\\Ground\\ground.txt"
#define ITEM_INFO	L"Resources\\Items\\item.txt"
#define AXE_INFO	L"Resources\\Weapon\\axe.txt"
#define BOOMERANG_INFO	L"Resources\\Weapon\\boomerang.txt"
#define FIREBOMB_INFO	L"Resources\\Weapon\\firebomb.txt"
#define WHIP_INFO		L"Resources\\Weapon\\whip.txt"
#define LEVEL1_INFO		L"Resources\\Scenes\\lv1.txt"
#define STAIR_INFO		L"Resources\\stair.txt"
#define LEVEL2_INFO		L"Resources\\Scenes\\lv2.txt"
#pragma endregion

#pragma region __TEXTURE_ID__

#define ID_TEX_BBOX		-100

#define ID_TEX_SIMON			0
#define ID_TEX_WHIP				1
#define ID_TEX_CANDLE			2
#define ID_TEX_ITEM_LARGE_HEART	3
#define ID_TEX_ITEM_CHAIN		4
#define ID_TEX_ITEM_DAGGER		5
#define ID_TEX_SMALL_CANDLE		6
#define ID_TEX_ZOMBIE			7
#define ID_TEX_ITEM_SMALL_HEART	8
#define ID_TEX_ITEM_AXE			9
#define ID_TEX_ITEM_BOOMERANG	10
#define ID_TEX_ITEM_CROSS		11
#define ID_TEX_ITEM_DOUBLE_SHOT	12
#define ID_TEX_ITEM_FIRE_BOMB	13
#define ID_TEX_ITEM_MONEY_BAG	14
#define ID_TEX_ITEM_PORK_CHOP	15
#define ID_TEX_ITEM_TRIPLE_SHOT	16
#define ID_TEX_ITEM_WATCH		17
#define ID_TEX_LEOPARD			18
#define ID_TEX_BAT				19
#define ID_TEX_GATE				20
#define ID_TEX_EFFECT			21
#define ID_TEX_FIRE_BOMB		22
#define ID_TEX_AXE				23
#define ID_TEX_BOOMERANG		24
#define ID_TEX_GROUND_2			25
#define ID_TEX_GROUND_3			26
#define ID_TEX_GROUND_4			27
#define ID_TEX_FISH_MAN			28
#define ID_TEX_FIRE_BALL		29
#define ID_TEX_BOSS				30
#define ID_TEX_SCORE_BOARD		31
#define ID_TEX_CASTLE			32
#define ID_TEX_MESSAGE			33
#define ID_TEX_HEAL				34
#define ID_TEX_ITEM_BALL		35
#define ID_TEX_ITEM_INVISIBILITY	36
#define ID_TEX_BRICK_DESTROY	37
#define ID_TEX_WATER_EFFECT		38
#define ID_TEX_BOSS_DIE			39
#define ID_TEX_MONEY_BAG_EFFECT	40
#define ID_TEX_BLACKBOARD		41

#pragma endregion

#pragma region __WHIP__

#define NORMAL_WHIP		0
#define SHORT_CHAIN		1
#define LONG_CHAIN		2

#define NORMAL_WHIP_ANI	201
#define SHORT_CHAIN_ANI 202
#define LONG_CHAIN_ANI	203

#pragma endregion

#pragma region __CANDLE__

// state
#define BIG_CANDLE			0
#define SMALL_CANDLE		1
#define CANDLE_DESTROY		2
#define SMALL_CANDLE_FREEZE	3
#define CANDLE_INACTIVE		4

// animation
#define BIG_CANDLE_ANI			301
#define SMALL_CANDLE_ANI		302
#define CANDLE_DESTROY_ANI		303
#define SMALL_CANDLE_FREEZE_ANI	304
#define CANDLE_INACTIVE_ANI		305

#pragma endregion

#pragma region __GROUND__

// state
#define GROUND			0
#define GROUND_2		1
#define	GROUND_3		2
#define GROUND_4		3
#define GROUND_DESTROY	4

// animations
#define GROUND_ANI		401
#define GROUND_2_ANI	402
#define GROUND_3_ANI	403
#define GROUND_4_ANI	404
#define GROUND_DESTROY_ANI	405

#pragma endregion

#pragma region __ITEM__

#define ITEM_GRAVITY	0.2f

//state
// item random
#define ITEM_LARGE_HEART	0	
#define ITEM_CHAIN			1	
#define ITEM_DISAPPEAR		2
#define ITEM_RED_MONEY_BAG	3	
#define ITEM_WHITE_MONEY_BAG	4	
#define ITEM_BLUE_MONEY_BAG		5	
#define ITEM_FLASH_MONEY_BAG	6	
#define ITEM_SMALL_HEART	7	
#define ITEM_CROSS			8
#define ITEM_DOUBLE_SHOT	9
#define ITEM_TRIPLE_SHOT	10
#define ITEM_PORK_CHOP		11
// sub-weapon
#define ITEM_DAGGER			12	
#define ITEM_AXE			13	
#define ITEM_FIRE_BOMB		14	
#define ITEM_WATCH			15	
#define ITEM_BALL			16
#define ITEM_INVISIBILITY	17

// animation
#define LARGE_HEART_ANI	501
#define CHAIN_ANI		502
#define ITEM_DISAPPEAR_ANI	503
#define RED_MONEY_ANI	504
#define WHITE_MONEY_ANI	505
#define BLUE_MONEY_ANI	506
#define FLASH_MONEY_ANI	507
#define SMALL_HEART_ANI	508

#define CROSS_ANI		509
#define DOUBLE_SHOT_ANI	510
#define TRIPLE_SHOT_ANI	511
#define PORK_CHOP_ANI	512

#define DAGGER_ANI		513
#define AXE_ANI			514
#define FIRE_BOMB_ANI	515
#define WATCH_ANI		516
#define BALL_ANI		517
#define INVISIBILITY_ANI	518

#define ITEM_TIME_DISAPPEAR  3000

#pragma endregion

#pragma region __DAGGER__

#define DAGGER_SPEED	0.3f

// state
#define DAGGER_STATE	0

#pragma endregion

#pragma region __FIRE_BALL__

#define FIREBALL			0
#define FIREBALL_FREEZE		1

#define FIREBALL_ANI		1501
#define FIREBALL_ANI_FREEZE	1502

#define FIREBALL_SPEED	0.15f

#pragma endregion

#pragma region __ZOMBIE__

// animation
#define ZOMBIE_ANI_MOVING	601
#define ZOMBIE_ANI_FREEZE	602
#define ZOMBIE_ANI_DESTROY	603
#define ZOMBIE_ANI_INACTIVE	604

// state
#define ZOMBIE_MOVE		0
#define ZOMBIE_FREEZE	1
#define ZOMBIE_DESTROY	2
#define ZOMBIE_INACTIVE	3

#define ZOMBIE_MOVE_SPEED_X		0.1f

#define ZOMBIE_RIGHT_SPAWN_TIME	6000
#define ZOMBIE_LEFT_SPAWN_TIME	10000
#define ENEMY_FREE_TIME			4000

#pragma endregion

#pragma region __STAIR__

#define UP_STAIR	0
#define DOWN_STAIR	1

#pragma endregion

#pragma region __SUB_WEAPON__

// state
#define DAGGER		0
#define AXE			1
#define FIRE_BOMB	2
#define WATCH		3
#define BOOMERANG	4

#pragma endregion

#pragma region __LEOPARD__

#define LEOPARD_SLEEP	0
#define LEOPARD_JUMP	1
#define LEOPARD_DESTROY	2
#define LEOPARD_RUN		3
#define LEOPARD_FREEZE_JUMP	4
#define LEOPARD_FREEZE_RUN	5
#define LEOPARD_INACTIVE	6

#define LEOPARD_ANI_SLEEP	701	
#define LEOPARD_ANI_JUMP	702
#define LEOPARD_ANI_DESTROY	703
#define LEOPARD_ANI_RUN		704
#define LEOPARD_ANI_FREEZE_JUMP	705
#define LEOPARD_ANI_FREEZE_RUN	706
#define LEOPARD_ANI_INACTIVE	707

#define LEOPARD_RUN_SPEED	0.22f
#define LEOPARD_JUMP_SPEED	0.42f
#define LEOPARD_GRAVITY		0.002f

#pragma endregion

#pragma region __BAT__

#define BAT_FLY		0
#define BAT_FREEZE	1
#define BAT_DESTROY	2
#define BAT_INACTIVE	3

#define BAT_ANI_FLY		801
#define BAT_ANI_FREEZE	802
#define BAT_ANI_DESTROY	803
#define BAT_ANI_INACTIVE	804

#define BAT_SPEED_X				0.12f
#define BAT_SPEED_Y				0.06f
#define BAT_SPAWN_TIME			5000

#pragma endregion

#pragma region __GATE__
#define GATE_1	0
#define GATE_2	1

#define GATE_CLOSE		0
#define GATE_OPENING	1
#define	GATE_OPENED		2
#define GATE_INACTIVE	3

#define GATE_ANI_CLOSE		901
#define GATE_ANI_OPENING	902
#define GATE_ANI_OPENED		903
#define GATE_ANI_INACTIVE	904

#pragma endregion

#pragma region __EFFECT__

#define EFFECT		0
#define EFFECT_OFF	1

#define EFFECT_ANI		1001
#define EFFECT_ANI_OFF	1002

#pragma endregion

#pragma region __FIRE_BOMB__

#define FB_THROW	0
#define FB_BURN		1
#define FB_INACTIVE	2

#define FB_ANI_THROW	1101
#define FB_ANI_BURN		1102
#define FB_ANI_INACTIVE	1103

#define FB_FLY_SPEED	0.3f
#define FB_GRAVITY		0.002f
#define FB_BURN_TIME	2000
#pragma endregion

#pragma region __AXE__
#define AXE_THROW		0
#define AXE_INACTIVE	1

#define AXE_ANI_THROW		1201	
#define AXE_ANI_INACTIVE	1202

#define AXE_FLY_SPEED	0.4f
#define AXE_GRAVITY		0.002f
#pragma endregion

#pragma region __BOOMERANG__

#define BOOMERANG_THROW		0
#define BOOMERANG_INACTIVE	1

#define BOOMERANG_ANI_THROW		1301
#define BOOMERANG_ANI_INACTIVE	1302

#define BOOMERANG_FLY_SPEED	0.2f

#pragma endregion

#pragma region __FISHMAN___

#define FISHMAN_MOVE	0
#define FISHMAN_SHOT	1
#define FISHMAN_FREEZE	2
#define FISHMAN_JUMP	3
#define FISHMAN_DESTROY	4
#define FISHMAN_INACTIVE	5

#define FISHMAN_ANI_MOVE	1401
#define FISHMAN_ANI_SHOT	1402
#define FISHMAN_ANI_FREEZE	1403
#define FISHMAN_ANI_JUMP	1404	
#define FISHMAN_ANI_DESTROY	1405
#define FISHMAN_ANI_INACTIVE	1406

#define FISHMAN_SPEED		0.09f
#define FISHMAN_JUMP_SPEED	0.3f
#define FISHMAN_GRAVITY		0.02f
#pragma endregion

#pragma region __BOSS__

#define BOSS_INACTIVE	0
#define	BOSS_FLY		1
#define BOSS_STOP		2
#define BOSS_FREEZE		3
#define BOSS_ATTACK		4
#define BOSS_ATTACK_STRAIGHT 5
#define BOSS_DIE		6
#define BOSS_DISAPPEAR	7

#define BOSS_ANI_INACTIVE	1601
#define BOSS_ANI_FLY		1602
#define BOSS_ANI_STOP		1603
#define BOSS_ANI_FREEZE		1604
#define BOSS_ANI_ATTACK		1605
#define BOSS_ANI_ATTACK_STRAIGHT	1606
#define BOSS_ANI_DIE		1607
#define BOSS_ANI_DISAPPEAR	1608

#define BOSS_SPEED_X_SLOW	0.12f
#define BOSS_SPEED_X_FAST	0.24f
#define BOSS_SPEED_Y		0.1f
#define BOSS_GRAVITY		0.002f

#pragma endregion

#pragma region __SCOREBOARD__
#define SCORE_BOARD_ANI	1701
#define SCORE_BOARD		0
#pragma endregion

#pragma region __GRID__
#define CELL_WIDTH		SCREEN_WIDTH/2
#define CELL_HEIGHT		SCREEN_HEIGHT/2
#pragma endregion

#pragma region __BRICK_DESTROY_EFFECT__
#define BRICK_DESTROY_EFFECT_ANI	1801
#define BRICK_DESTROY_EFFECT	0
#define BRICK_DESTROY_X		0.1f
#define BRICK_DESTROY_Y		0.2f
#define EFFECT_GRAVITY		0.002f
#pragma endregion

#pragma region __WATER_EFFECT__
#define WATER_EFFECT	0
#define WATER_EFFECT_ANI	1901

#define WATER_SPEED_X	0.05f
#define WATER_SPEED_Y	0.2f
#define WATER_GRAVITY	0.002f
#pragma endregion
