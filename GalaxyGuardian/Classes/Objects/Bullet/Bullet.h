
#ifndef  __Bullet_H__
#define __Bullet_H__

// #include "Objects\Base\FlyingObject.h"
#include "cocos2d.h"
#include "Common\GlobalDefinition.h"
USING_NS_CC;



class Bullet : public Node
{
public:
	// bullet image
	Sprite* image;

	Bullet(std::string frameName, int damage, int pattern, float angle, BulletSpeed speed);
	~Bullet();
	static Bullet* create(std::string frameName, int damage, int pattern, BulletSpeed speed, float angle = 90.0f);
	
	// get bullet's damage
	int GetDamage();

	// get bullet's pattern
	int GetPattern();

	// 나중에 지울것
	float GetAngle();
	BulletSpeed GetSpeed();
	Vec2 position;

	// angle of Bullet
	float angle;

	// using for enemy bullet pattern(spread_on_point)
	int time;
	
	// speed of Bullet
	BulletSpeed speed;
private:
	// damage of Bullet
	int damage;

	// pattern of Bullet Moving
	int pattern;

	
	
};

#endif // ! __Bullet_H__


