#include "Bullet.h"

Bullet::Bullet(std::string frameName, int power, int weapon,  float bulletAngle, BulletSpeed bulletSpeed)
{
	image = Sprite::createWithSpriteFrameName(frameName);
	image->setScale(2.0f * SCALE_FACTOR);
	this->addChild(image);
	damage = power;
	pattern = weapon;
	angle = bulletAngle;
	speed = BulletSpeed(bulletSpeed.x, bulletSpeed.y);
	time = 0;
}

Bullet::~Bullet()
{
	
}

Bullet * Bullet::create(std::string frameName, int damage, int pattern, BulletSpeed speed, float angle)
{
	Bullet* bullet = new Bullet(frameName, damage, pattern, angle, speed);
	return bullet;
}

int Bullet::GetDamage()
{
	return damage;
}

int Bullet::GetPattern()
{
	return pattern;
}

float Bullet::GetAngle()
{
	return angle;
}

BulletSpeed Bullet::GetSpeed()
{
	return speed;
}

