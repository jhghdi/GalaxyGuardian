#pragma once
#ifndef __GLOBALDEFINITION_H__
#define __GLOBALDEFINITION_H__

#include "cocos2d.h"
#include <memory>
#include "SimpleAudioEngine.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"
#endif

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

// glow effects
 static void AddGlowEffect(Sprite* sprite, const Color3B& colour, const Size& size);

// 화면 가로 크기
#define WIN_WIDTH Director::getInstance()->getWinSize().width	

// 화면 세로 크기
#define WIN_HEIGHT Director::getInstance()->getWinSize().height	

// 화면 배율
#define SCALE_FACTOR  Director::getInstance()->getContentScaleFactor()

// Boss life image path
#define BOSS_LIFE_BG_IMG_PATH "Images/Enemy/Boss/Life_bg.png" 
#define BOSS_LIFE_IMG_PATH "Images/Enemy/Boss/life.png" 

// Warning Image fiel path
#define WARNING_IMAGE "Images/Effects/Warning.png"

// 초를 tick(1/60.0f)단위로 변환
#define SEC_TO_TICK(x) x * 60

// Bomb Image Path
#define BOMB_IMG_PATH "Images/Effects/Bomb.png"

// Bomb Damage
#define BOMB_DAMAGE 5

// 화면과 image간의 간격 
#define MARGIN 50	

// 플레이어가 받는 데미지
#define DAMAGE_TO_PLAYER 1 

// 기체간 충돌시 Ememy가 받는 데미지
#define EXPLOSION_DAMAGE_OF_ENEMY 15 

// 플레이어 인덱스
#define PLAYER_INDEX 10

// 적 기체 시작 인덱스
#define ENEMY_INDEX 100 

// 아이템을 가지고 있는 적 기체 시작 인덱스
#define ITEM_ENEMY_INDEX 115

// 중간 크기의 적 기체 시작 인덱스
#define LARGE_ENEMY_INDEX 120 

// 보스 기체 시작 인덱스
#define BOSS_INDEX 130 

// 화면 밖으로 나갔는지에 대한 check
#define CHECK_IMAGE_IS_OUT_THE_WINDOW(y) y < 0 
#define CHECK_X_IS_IN_THE_WINDOW(x) x > 0

// 화면 밖
#define OUT -200

// 삼각함수 -> bullet 다음 이동위치를 구할때 사용
#define COS(angle ,speed) { cos(angle * M_PI / 180) * speed }
#define SIN(angle ,speed) { sin(angle * M_PI / 180) * speed }
#define TAN(angle ,speed) { tan(angle * M_PI / 180) * speed }

// notification value
#define POPUP 1
#define GAIN_PLAYER_LIFE 2
#define WARNING 3


#pragma region explosion setting

// 폭발 image path
#define EXP_IMG_PATH "Images/Effects/Explode.png"	

// 폭발 image SIZE( WIDTH, HEIGHT 동일) 
#define EXP_SIZE 128	

// gameScene Tag
#define GAMESCENE_TAG 5

#pragma endregion

#pragma region definition about player weapon 

// bullet pattenr index using player
enum PLAYER_WEAPON { DEFAULT = 31, WIDE = 32, AUTO = 33};

// weapon damage classification of player
enum PLAYER_WEAPON_DMG { DEFAULT_DMG = 10, WIDE_DMG = 6, AUTO_DMG = 8 };

// player bullet speed
#define PLAYER_BULLET_SPEED 50.0f

// player weapon image path
#define PLAYER_DEFAULT_IMG "PS1.png"
#define PLAYER_WIDE_LEFT_IMG "PS21.png"
#define PLAYER_WIDE_CENTER_IMG "PS22.png"
#define PLAYER_WIDE_RIGHT_IMG "PS23.png"
#define PLAYER_AUTO_IMG "PS3.png"

#pragma endregion

#pragma region definition about enemy weapon

enum ENEMY_PATTERN {SMALL_1 = 101, SMALL_2, SMALL_3, SMALL_4, SMALL_5, SMALL_6, SMALL_7, SMALL_8, SMALL_9, SMALL_10,
					LARGE_1 = 121, LARGE_2, LARGE_3, LARGE_4, LARGE_5, LARGE_6,
					STAGE1 = 131, STAGE2, STAGE3, STAGE4, FINAL};

// bullet pattenr index using player
enum ENEMY_WEAPON { 
					BASIC = 101, THREE_WAYS, TO_PLAYER, SIN, CIRCIES, NONE,
					BASIC_THREE_TIMES, FOUR_WAYS, TO_PLAYER_THREE_TIMES, SIN_COS,
					VOLTEX_4WAYS, ARCS, TO_PLAYER_RAND, FINAL_PATTERN,
					TWO_ARC = 140, TWO_CIRCIES, TO_BIGGER, THREE_WAYS_BIG, FOUR_WAYS_BIG, WIDE_RAND_EXCEPT, VECTOR_RIGHT_ANGLES, 
					SPREAD_ON_POINT, HOLE, STAR_1, STAR_2, VECTOR_WIDE_1, VECTOR_WIDE_2, VOLTEX_AROUND_1, VOLTEX_AROUND_2, RANDOM,
					VECTOR_5=170,VECTOR_10, VECTOR_15, VECTOR_20, VECTOR_25, VECTOR_30, VECTOR_35, VECTOR_40, VECTOR_45, VECTOR_50,
					VECTOR_55, VECTOR_60, VECTOR_65, VECTOR_70, VECTOR_75, VECTOR_80, VECTOR_85, VECTOR_90, VECTOR_95, VECTOR_100,
					VECTOR_105, VECTOR_110, VECTOR_115, VECTOR_120, VECTOR_125, VECTOR_130, VECTOR_135, VECTOR_140, VECTOR_145,
					VECTOR_150, VECTOR_155, VECTOR_160, VECTOR_165, VECTOR_170, VECTOR_175, VECTOR_180, VECTOR_185, VECTOR_195,
					VECTOR_205, VECTOR_215, VECTOR_225, VECTOR_235, VECTOR_245, VECTOR_255, VECTOR_265, VECTOR_275 , VECTOR_285,
					VECTOR_295, VECTOR_305, VECTOR_315, VECTOR_325, VECTOR_335, VECTOR_345, VECTOR_355
					};

// enemy bullet speed
class BulletSpeed
{
public:
	BulletSpeed(float posX, float posY);
	BulletSpeed();
	~BulletSpeed();
	float x;
	float y;
};
#define ENEMY_BULLET_SPEED -10.0f

#define RANDOM_BULLET_SPEED random(-7, -3)

// enemy weapon image path
#define ENEMY_BULLET_IMG1 "ES1.png"
#define ENEMY_BULLET_IMG2 "ES2.png"
#define ENEMY_BULLET_IMG3 "ES3.png"
#define ENEMY_BULLET_IMG4 "ES4.png"
#define ENEMY_BULLET_IMG5 "ES5.png"
#define ENEMY_BULLET_IMG6 "ES6.png"
#define ENEMY_BULLET_IMG7 "ES7.png"
#define ENEMY_BULLET_IMG8 "ES8.png"
#define ENEMY_BULLET_IMG9 "ES9.png"
#define ENEMY_BULLET_IMG10 "ES10.png"
#define ENEMY_BULLET_IMG11 "ES11.png"
#define ENEMY_BULLET_IMG12 "ES12.png"
#pragma endregion

#pragma region enemy index

#define SMALL_ENEMY_1 1
#define SMALL_ENEMY_2 2
#define SMALL_ENEMY_3 3
#define SMALL_ENEMY_4 4
#define SMALL_ENEMY_5 5
#define SMALL_ENEMY_6 6
#define SMALL_ENEMY_7 7
#define SMALL_ENEMY_8 8
#define SMALL_ENEMY_9 9
#define SMALL_ENEMY_10 10
#define SMALL_ENEMY_11 11
#define SMALL_ENEMY_12 12

#define BOMB_ENEMY 16
#define LIFE_ENEMY 17
#define ITEM_ENEMY 18

#define LARGE_ENEMY_1 21
#define LARGE_ENEMY_2 22
#define LARGE_ENEMY_3 23
#define LARGE_ENEMY_4 24
#define LARGE_ENEMY_5 25
#define LARGE_ENEMY_6 26
#define LARGE_ENEMY_7 27
#define LARGE_ENEMY_8 28

#define STAGE1_BOSS 31
#define STAGE2_BOSS 32
#define STAGE3_BOSS 33
#define STAGE4_BOSS 34
#define FINAL_BOSS 35


#pragma endregion 

#pragma region Global variable declare

	extern float angleBetweenPlayerAndEnemy;

	// 스테이지 초기화 여부
	extern bool isInit;

	// header or resultScene
	extern std::string header;

	// play time
	extern int playTime;
#pragma endregion

#pragma region soundfile path and Volume setting

#define BOMB_SOUND "Sounds/Effects/Bomb.wav"
#define BOSS_DESTROY_SOUND "Sounds/Effects/Boss_enemy_destroy.wav"
#define LARGE_DESTROY_SOUND "Sounds/Effects/Large_enemy_destroy.wav"
#define SMALL_DESTROY_SOUND "Sounds/Effects/Small_enemy_explosion.wav"
#define ENEMY_COLLISION_SOUND "Sounds/Effects/Collision.wav" 
#define BOMB_GAIN_SOUND "Sounds/Effects/Bomb_gain.wav"
#define LIFE_GAIN_SOUND "Sounds/Effects/Life_gain.wav"
#define ITEM_GAIN_SOUND "Sounds/Effects/Item_gain.wav"
#define PLAYER_SHOT_SOUND "Sounds/Effects/Player_shot.wav"
#define PLAYER_DAMAGE_SOUND "Sounds/Effects/Player_damage.wav"
#define STAGE_CLEAR_SOUND "Sounds/Effects/Player_shot.wav" 
#define WARNING_SOUND "Sounds/Effects/Prepare_boss.wav"

#define MAIN_SOUND "Sounds/background/main.wav"
#define STAGE1_SOUND "Sounds/background/stage1_back.wav"
#define STAGE2_SOUND "Sounds/background/stage2_back.wav"
#define STAGE3_SOUND "Sounds/background/stage3_back.wav"
#define STAGE4_SOUND "Sounds/background/stage4_back.wav"

	

#pragma endregion


#endif