#ifndef  __BOSS_H__
#define  __BOSS_H__

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(int index);
	void Collision(int damage);
	~Boss();
private:
	// life sprite
	Sprite* lifeBackground;
	Sprite* lifeImage;
	float initLife;
	float lifeWidth;
};

#endif // ! __SMALLENEMY_H__
