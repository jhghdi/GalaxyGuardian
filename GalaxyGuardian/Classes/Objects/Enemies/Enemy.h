#ifndef  __ENEMY_H__
#define  __ENEMY_H__

#include "Objects\Base\FlyingObject.h"

class Enemy : public FlyingObject
{

typedef struct PtnAndInterval
{
	PtnAndInterval(int inter, int ptn)
	{
		interval = inter;
		pattern = ptn;
	}
	int interval;
	int pattern;
}PtnAndInterval;

public:
	// 적 구분
	enum ENEMY_KIND { SMALL,ITEM, LARGE, BOSS };

	// 생성자
	Enemy();
	Enemy(int index,Vec2 startPoint = Vec2::ZERO, Vec2 endPoint = Vec2::ZERO, Vec2 turnPoint = Vec2::ZERO );

	// 소멸자
	~Enemy();

	// 적의 움직임
	void Move();

	// 충돌처리
	void Collision(const int &damage);

	// 총알 발사주기와 시간 확인
	bool IsReadyToShot();

	// 현재 패턴을 반환
	int GetPattern();

	// 적 index에 따른 패턴 생성 후 queue에 넣는다.
	void SetPattern(const int &index);
	
	// 다음 패턴을 설정
	void SetNextPattern();

	// Pattern의 갯수를 반환
	int GetPatternCount();

	// 적의 종류를 반환
	int Getkind();

	// 적의 index를 반환
	int GetIndex();

	// 적 기체의 폭발 크기를 반환
	float GetScaleOfExplosion();

	// 적 종류에 따른 폭발 크기 설정
	void SetScaleOfExplosion();

	// bullet을 발사하는 시간
	int shotTime;
	
protected:
	// index에 따라 생명력 정의
	void SetLife(const int &index);

	// 적의 종류(large, small, boss)
	int kind;

	// 적의 idnex에 따라 sprite name을 가져온다
	std::string GetEnemySpriteName(const int &index);

	// pattern list of bullet	
	std::queue<PtnAndInterval> ptnList;

	// scheduler update method
	void Update(float dt);

	// StartPosition  of enemy
	Vec2 startPosition;

	// Destination of enemy
	Vec2 EndPosition;

	// TurnPosition
	Vec2 TurnPosition;

	// scale of explosion
	float explosion;

	// index
	int index;
private:
	// 적의 종류를 초기화
	void SetKindOfEnemy(const int &index);

	
};

#endif // ! __SMALLENEMY_H__
