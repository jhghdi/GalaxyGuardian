#include "Boss.h"

Boss::Boss(int index)
{
	// Boss sprite
	std::string spriteName = GetEnemySpriteName(index);
	image = Sprite::createWithSpriteFrameName(GetEnemySpriteName(index));
	image->setScale(SCALE_FACTOR);
	this->addChild(image);

	startPosition = Vec2(Vec2(WIN_WIDTH / 2, WIN_HEIGHT + 100));
	EndPosition = Vec2(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.7));

	// Boss life Sprite
	lifeBackground = Sprite::create(BOSS_LIFE_BG_IMG_PATH);
	lifeBackground->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.95));
	lifeBackground->setScaleX(SCALE_FACTOR);
	this->addChild(lifeBackground);

	lifeImage = Sprite::create(BOSS_LIFE_IMG_PATH);
	//lifeImage->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.95));
	lifeImage->setScaleX(SCALE_FACTOR);
	lifeImage->setAnchorPoint(Vec2(-0.01, -0.15f));
	lifeBackground->addChild(lifeImage);

	// default setting
	this->index = index;
	SetLife(index);
	SetPattern(ENEMY_INDEX + index);
	shotTime = 0;
	kind = ENEMY_KIND::BOSS;
	SetScaleOfExplosion();
	initLife = life;
	lifeWidth = lifeImage->getPositionX();

}

void Boss::Collision(int damage)
{
	life -= damage;

	if (life <= 0 && image)
	{
		image->stopAllActions();
		image->setVisible(false);
	}

	auto seq = Sequence::createWithTwoActions(TintTo::create(0.02f, Color3B::BLUE), TintTo::create(0.02f, Color3B::WHITE));
	image->runAction(seq);

	float reduce = life / initLife;

	float reduceWidth = (damage / initLife) * lifeWidth * 0.98;

	lifeImage->setScaleX(reduce);
}

Boss::~Boss()
{

}
