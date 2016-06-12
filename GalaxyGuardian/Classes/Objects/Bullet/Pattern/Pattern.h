#pragma once
#ifndef __PATTERN_H__
#define __PATTERN_H__

#define DEFAULT_SPEED_PLAYER BulletSpeed(PLAYER_BULLET_SPEED, PLAYER_BULLET_SPEED)
#define DEFAULT_SPEED_ENEMY BulletSpeed(ENEMY_BULLET_SPEED, ENEMY_BULLET_SPEED)

#define SPREAD_TIME 40

#include "Objects\Bullet\Bullet.h"

enum BULLET_PATTERN { STRAIGHT, VECTOR, CURVE_SIN, CURVE_COS, ARC, ARC_REVERSE, CIRCLE, VOLTEX, VOLTEX_REVERSE, RIGHT_ANGLE , BIGGER, SPREAD};

class Pattern
{
public:
	// ���Ͽ����� �Ѿ��� �����Ѵ�,
	static std::vector<Bullet*> Create(const int &patternIndex);

	// ���Ͽ����� �Ѿ��� ��ġ�� �����Ѵ�.
	static void Move(Bullet *bullet);
};
#endif // ! __PATTERN_H__
