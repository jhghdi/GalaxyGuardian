#ifndef  __FLYINGOBJECT_H__
#define __FLYINGOBJECT_H__
#include "Common\GlobalDefinition.h"


class FlyingObject : public Node
{
public:
	virtual void Move();
	virtual void Collision(int damage);

	Rect GetBoundingBoxOfImage();
	Sprite* image;
	int life;
protected:
	int weapon;
	int shotInterval; // shot delay
};
#endif // ! __FLYINGOBJECT_H__