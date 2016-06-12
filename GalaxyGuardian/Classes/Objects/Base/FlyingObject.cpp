#include "FlyingObject.h"


void FlyingObject::Move()
{ }

void FlyingObject::Collision(int damage)
{
	life -= damage;

	if (life <= 0 )
	{
		SimpleAudioEngine::getInstance()->playEffect(LARGE_DESTROY_SOUND, false);
		image->stopAllActions();
		image->setVisible(false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(ENEMY_COLLISION_SOUND, false);
		auto seq = Sequence::createWithTwoActions(TintTo::create(0.02f, Color3B::BLUE), TintTo::create(0.02f, Color3B::WHITE));
		image->runAction(seq);	
	}
}

Rect FlyingObject::GetBoundingBoxOfImage()
{
	auto width = image->getBoundingBox().size.width;
	auto height = image->getBoundingBox().size.height;
	return Rect(width *0.4, height * 0.4, width*0.5, height* 0.5);
}



