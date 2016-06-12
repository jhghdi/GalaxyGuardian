#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(int index, Vec2 startPoint, Vec2 endPoint, Vec2 turnPoint)
{
	// sprite
	std::string spriteName = GetEnemySpriteName(index);
	image = Sprite::createWithSpriteFrameName(GetEnemySpriteName(index));
	image->setScale(2.0f * SCALE_FACTOR);
	this->addChild(image);

	// default setting
	this->index = index;
	SetLife(index);
	SetKindOfEnemy(index);
	SetScaleOfExplosion();
	SetPattern(ENEMY_INDEX + index);
	shotTime=0;

	// move setting
	startPosition = startPoint;
	EndPosition = endPoint;
	TurnPosition = turnPoint;

	// enemy scheduler 등록
	//  this->schedule(schedule_selector(Enemy::Update), 1/60.0f);
}

Enemy::~Enemy()
{
//	delete image;
	image = nullptr;
}

void Enemy::Update(float dt)
{
	++shotTime;
}

void Enemy::Move()
{
	if (index == FINAL_BOSS)
	{
		image->setPosition(startPosition);
		auto moveDowm = MoveTo::create(4.0f, Vec2(random(50, 400), WIN_HEIGHT * 0.2));
		auto moveUp = MoveTo::create(4.0f, Vec2(random(50, 400), WIN_HEIGHT * 0.8));
		auto seq = Sequence::create(moveDowm, moveUp, nullptr);

		image->runAction(RepeatForever::create(seq));

	}
	else if(startPosition == Vec2::ZERO)
	{ 
		image->setPosition(Vec2(random(50, 600), WIN_HEIGHT + MARGIN));
		auto action = MoveTo::create(3.0f, Vec2(random(50, 400), -MARGIN));
		image->runAction(action);
	}
	else if (EndPosition == Vec2::ZERO)
	{

		image->setPosition(startPosition);
		auto action = MoveTo::create(3.0f, Vec2(startPosition.x, -MARGIN));
		image->runAction(action);
	}
	else if (TurnPosition == Vec2::ZERO)
	{ 
		image->setPosition(startPosition);
		auto action = MoveTo::create(1.0f, EndPosition);
		image->runAction(action);
	}
	
}

void Enemy::Collision(const int &damage)
{
}

bool Enemy::IsReadyToShot()
{
	return shotInterval == shotTime;
}

int Enemy::GetPattern()
{
	return weapon;
}

void Enemy::SetPattern(const int &index)

{
	switch (index)
	{
	case ENEMY_PATTERN::SMALL_1:
		weapon = ENEMY_WEAPON::BASIC;
		shotInterval = 10;
		break;
	case ENEMY_PATTERN::SMALL_2:
		weapon = ENEMY_WEAPON::THREE_WAYS;
		shotInterval = 10;
		break;
	case ENEMY_PATTERN::SMALL_3:
		weapon = ENEMY_WEAPON::TO_PLAYER;
		shotInterval = 10;
		break;
	case ENEMY_PATTERN::SMALL_4:
		weapon = ENEMY_WEAPON::SIN;
		shotInterval = 30;
		ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::SIN));
		break;
	case ENEMY_PATTERN::SMALL_5:
		weapon = ENEMY_WEAPON::FOUR_WAYS;
		shotInterval = 10;
		break;
	case ENEMY_PATTERN::SMALL_6:
		weapon = ENEMY_WEAPON::NONE;
		shotInterval = 0;
		break; 
	case ENEMY_PATTERN::SMALL_7:
		weapon = ENEMY_WEAPON::TO_PLAYER;
		shotInterval = 10;
		ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::TO_PLAYER));
		ptnList.push(PtnAndInterval(50, ENEMY_WEAPON::TO_PLAYER));
		break;
	case ENEMY_PATTERN::SMALL_8:
		weapon = ENEMY_WEAPON::SIN_COS;
		shotInterval = 10;
		break;
	case ENEMY_PATTERN::SMALL_9:
		weapon = ENEMY_WEAPON::VOLTEX_4WAYS;
		shotInterval = 10;
		ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::VOLTEX_4WAYS));
		break;

	// 3발, 4발
	case ENEMY_PATTERN::LARGE_1:
		weapon = ENEMY_WEAPON::THREE_WAYS;
		shotInterval = 50;
		ptnList.push(PtnAndInterval(50, ENEMY_WEAPON::FOUR_WAYS));
		ptnList.push(PtnAndInterval(50, ENEMY_WEAPON::THREE_WAYS));
		break;

	// 플레이어 방향으로 연속되는 탄
	case ENEMY_PATTERN::LARGE_2:
		weapon = ENEMY_WEAPON::TO_PLAYER;
		shotInterval = 20;
		ptnList.push(PtnAndInterval(20, ENEMY_WEAPON::TO_PLAYER));
		break;

	// 좌우로 각도를 좁혀가면서 연속 4발
	case ENEMY_PATTERN::LARGE_3:
		weapon = ENEMY_WEAPON::VECTOR_5;
		shotInterval = 50;
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_15));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_25));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_160));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_170));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_180));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_45));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_35));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_55));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_130));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_140));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_150));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_85));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_75));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_65));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_100));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_110));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_120));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_70));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_80));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_90));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_105));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_115));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_95));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_145));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_135));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_125));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_40));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_50));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_60));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_10));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_20));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_30));
		ptnList.push(PtnAndInterval(15, ENEMY_WEAPON::VECTOR_175));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_165));
		ptnList.push(PtnAndInterval(1, ENEMY_WEAPON::VECTOR_155));
		break;

	case ENEMY_PATTERN::LARGE_4:
		weapon = ENEMY_WEAPON::SIN_COS;
		shotInterval = 30;
		ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::SIN_COS));
		break;

	// 회오리탄
	case ENEMY_PATTERN::LARGE_5:
		weapon = ENEMY_WEAPON::NONE;
		shotInterval = 60;
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_355));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_345));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_335));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_325));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_315));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_305));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_295));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_285));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_275));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_265));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_255));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_245));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_235));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_225));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_215));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_205));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_195));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_185));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_175));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_165));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_155));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_145));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_135));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_125));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_115));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_105));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_95));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_85));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_75));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_65));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_55));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_45));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_35));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_25));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_15));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_5));
		break;
	
	// 1초뒤에 분열되는 탄
	case ENEMY_PATTERN::LARGE_6:
		weapon = ENEMY_WEAPON::NONE;
		shotInterval = 10;
		ptnList.push(PtnAndInterval(120, ENEMY_WEAPON::SPREAD_ON_POINT));
		break;

	case ENEMY_PATTERN::STAGE1:
		weapon = ENEMY_WEAPON::THREE_WAYS;
		shotInterval = 10;
		for (int i = 0; i < 5; ++i)
		{
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::FOUR_WAYS));
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::THREE_WAYS));
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::FOUR_WAYS));
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::TO_PLAYER));
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::THREE_WAYS));
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::FOUR_WAYS));
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::THREE_WAYS));
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::TO_PLAYER));
		}
		for (int i = 0; i < 100; ++i)
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::TO_PLAYER_RAND));
		break;

	case ENEMY_PATTERN::STAGE2:
		weapon = ENEMY_WEAPON::FOUR_WAYS_BIG;
		shotInterval = 18;
		for (int i = 0; i < 3; ++i)
		{
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_10));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_175));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_20));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_165));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::THREE_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_30));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_155));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_40));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_145));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::FOUR_WAYS_BIG));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_50));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_135));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_60));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_125));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::THREE_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_70));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_115));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_80));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_105));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::FOUR_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_90));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_95));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_100));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_85));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::THREE_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_110));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_75));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_120));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_65));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::FOUR_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_130));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_55));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_140));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_45));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::THREE_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_150));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_35));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_160));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_25));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::FOUR_WAYS_BIG));
			ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_170));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_15));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_180));
			ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_5));
		}
		for (int i = 0; i < 30; ++i)
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::TO_BIGGER));
		break;

	case ENEMY_PATTERN::STAGE3:
		weapon = ENEMY_WEAPON::WIDE_RAND_EXCEPT;
		shotInterval = 40;
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_5));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_15));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_25));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_35));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_45));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_55));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_65));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_75));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_85));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_95));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::WIDE_RAND_EXCEPT));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_105));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_115));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_125));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_135));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_145));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_155));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_165));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_175));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::WIDE_RAND_EXCEPT));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_165));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_155));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_145));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_135));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_125));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_115));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_105));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::VECTOR_95));
		ptnList.push(PtnAndInterval(2, ENEMY_WEAPON::WIDE_RAND_EXCEPT));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_85));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_75));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_65));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_55));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_45));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_35));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_25));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_15));
		ptnList.push(PtnAndInterval(4, ENEMY_WEAPON::VECTOR_5));
		for (int i = 0; i < 20; ++i)
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::VECTOR_RIGHT_ANGLES));
		break;

	case ENEMY_PATTERN::STAGE4:
		// star(72도 단위, 삼각형 그리기) + 사방
		weapon = ENEMY_WEAPON::VECTOR_WIDE_1;
		shotInterval = 50;
		for (int i = 0; i < 4; ++i)
		{ 
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::STAR_1));
			ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::VECTOR_WIDE_2));
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::STAR_2));
			ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::VECTOR_WIDE_1));
		}
		//// x자 패턴 ? (2 ->1 반복) + 원형
		for (int i = 0; i < 4; ++i)
		{
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::VOLTEX_AROUND_1));
			ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::VECTOR_WIDE_2));
			ptnList.push(PtnAndInterval(5, ENEMY_WEAPON::VOLTEX_AROUND_2));
			ptnList.push(PtnAndInterval(30, ENEMY_WEAPON::VECTOR_WIDE_1));
		}
		// 랜덤 탄막 패턴
		for (int i = 0; i < 50; ++i)
			ptnList.push(PtnAndInterval(10, ENEMY_WEAPON::RANDOM));
		break;
	case ENEMY_PATTERN::FINAL:
		// 느리게 계속 미사일 발사
		weapon = ENEMY_WEAPON::FINAL_PATTERN;
		shotInterval = 20;
		ptnList.push(PtnAndInterval(50, ENEMY_WEAPON::FINAL_PATTERN));
		break;
	default:
		weapon = ENEMY_WEAPON::NONE;
		shotInterval = 0;
		break;
	}
}

void Enemy::SetNextPattern()
{
	auto ptn = ptnList.front();
	shotInterval = ptn.interval;
	weapon = ptn.pattern;
	shotTime = 0;
	ptnList.pop();

	if (kind != ENEMY_KIND::SMALL)
		ptnList.push(ptn);
}

int Enemy::GetPatternCount()
{
	return ptnList.size();
}

void Enemy::SetLife(const int &index)
{
	switch(index)
	{ 
		// Normal mode
		case SMALL_ENEMY_1:
		case SMALL_ENEMY_2:
		case SMALL_ENEMY_3:
		case SMALL_ENEMY_4:
		case SMALL_ENEMY_5:
		case SMALL_ENEMY_7:
		case SMALL_ENEMY_8:
		case SMALL_ENEMY_9:
			life = 15;
			break;
		case SMALL_ENEMY_6:
			life = 50;
			break;

		// Item Enemy
		case 16:
		case 17:
		case 18:
			life = 10;
			break;

		// Large Enemy
		case LARGE_ENEMY_1:
		case LARGE_ENEMY_2:
		case LARGE_ENEMY_3:
		case LARGE_ENEMY_4:
		case LARGE_ENEMY_5:
		case LARGE_ENEMY_6:
			life = 600;
			break;

		// Boss
		case STAGE1_BOSS:
		case STAGE2_BOSS:
		case STAGE3_BOSS:
			life = 1500;
			break;
		case STAGE4_BOSS:
			life = 2000;
			break;
		case FINAL_BOSS:
			life = 1000;
			break;
		default:
			log("%d : 정의되어 있지 않은 값입니다!", index);
			break;
	}
}

void Enemy::SetKindOfEnemy(const int &index)
{
	if (index > 20)
		kind = ENEMY_KIND::LARGE;
	else if(index <= ITEM_ENEMY && index >=BOMB_ENEMY)
		kind = ENEMY_KIND::ITEM;
	else
		kind = ENEMY_KIND::SMALL;
}

std::string Enemy::GetEnemySpriteName(const int &index)
{
	char name[50];

	if(index > 30)
		sprintf(name, "B%d.png", index-30);
	else if(index > 20)
		sprintf(name, "LE%d.png", index-20);
	else
		sprintf(name, "%d.png", index);	

	return name;
}

int Enemy::Getkind()
{
	return kind;
}

int Enemy::GetIndex()
{
	return index;
}

float Enemy::GetScaleOfExplosion()
{
	return explosion;
}

void Enemy::SetScaleOfExplosion()
{
	if (kind == ENEMY_KIND::BOSS)
		explosion = 8.0f;
	else if (kind == ENEMY_KIND::LARGE)
		explosion = 4.0f;
	else
		explosion = 2.0f;
}


