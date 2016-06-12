#ifndef __PLAYER_H__
#define __PLAYER_H__

#define DEFAULT_BOMBCOUNT 1
#define MAXIMUM_BOMBCOUNT 3
#define PLAYER_DEFAULT_SPEED 6.0

#include "Objects\Base\FlyingObject.h"
#include "Joystick\Joystick.h"
#include "Objects\Bullet\Pattern\Pattern.h"


class Player : public FlyingObject
{
public:
	Player();
	~Player();

	// player�� �浹ó���� �����Ѵ�.
	void Collision(int damage);

	// player's Bullet
	std::vector<Bullet*> bullets; 

	 // bomb count
	int bombCount;

	// set player's weapon
	void SetWeapon(int weapon);

	// increase player life
	void GetLife();

	// scheduler 
	void Update(float dt);

	// �ǰ����� Ȯ��
	Rect GetBoundingBoxOfImage();

	// ȸ�ǻ��¸� ��ȯ�Ѵ�.
	bool GetAvoidingStatus();

	// 2�ʰ� ��������
	void notDamaged();

protected:
	
private:
	// player�� �̵���Ų��
	void Move();
	// ȸ�ǻ��¸� �����Ѵ�.
	void SetAvoidingStatus();

	// Touch Event
	bool onTouchesBegan(const std::vector<Touch*>&, Event* event);
	void onTouchesMoved(const std::vector<Touch*>&, Event* event);
	void onTouchesEnded(const std::vector<Touch*>&, Event* event);

	// moving status
	bool isMoving;	

	// avoiding status
	bool isAvoiding;

	// moving speed
	float moveSpeed;

	// player X position
	float posX;	

	// player Y position
	float posY;	

	// joystick
	Joystick* joystick;

	// playerLife Sprites
	std::stack<Sprite*> playerLife;

	// reduce playerLife 
	void ReducePlayerLife();

	
};

#endif // __PLAYER_H__
