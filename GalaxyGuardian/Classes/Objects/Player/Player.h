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

	// player의 충돌처리를 수행한다.
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

	// 피격판정 확인
	Rect GetBoundingBoxOfImage();

	// 회피상태를 반환한다.
	bool GetAvoidingStatus();

	// 2초간 무적상태
	void notDamaged();

protected:
	
private:
	// player를 이동시킨다
	void Move();
	// 회피상태를 변경한다.
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
