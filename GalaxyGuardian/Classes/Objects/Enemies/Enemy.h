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
	// �� ����
	enum ENEMY_KIND { SMALL,ITEM, LARGE, BOSS };

	// ������
	Enemy();
	Enemy(int index,Vec2 startPoint = Vec2::ZERO, Vec2 endPoint = Vec2::ZERO, Vec2 turnPoint = Vec2::ZERO );

	// �Ҹ���
	~Enemy();

	// ���� ������
	void Move();

	// �浹ó��
	void Collision(const int &damage);

	// �Ѿ� �߻��ֱ�� �ð� Ȯ��
	bool IsReadyToShot();

	// ���� ������ ��ȯ
	int GetPattern();

	// �� index�� ���� ���� ���� �� queue�� �ִ´�.
	void SetPattern(const int &index);
	
	// ���� ������ ����
	void SetNextPattern();

	// Pattern�� ������ ��ȯ
	int GetPatternCount();

	// ���� ������ ��ȯ
	int Getkind();

	// ���� index�� ��ȯ
	int GetIndex();

	// �� ��ü�� ���� ũ�⸦ ��ȯ
	float GetScaleOfExplosion();

	// �� ������ ���� ���� ũ�� ����
	void SetScaleOfExplosion();

	// bullet�� �߻��ϴ� �ð�
	int shotTime;
	
protected:
	// index�� ���� ����� ����
	void SetLife(const int &index);

	// ���� ����(large, small, boss)
	int kind;

	// ���� idnex�� ���� sprite name�� �����´�
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
	// ���� ������ �ʱ�ȭ
	void SetKindOfEnemy(const int &index);

	
};

#endif // ! __SMALLENEMY_H__
