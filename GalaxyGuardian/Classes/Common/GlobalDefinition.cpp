#include "GlobalDefinition.h"

float angleBetweenPlayerAndEnemy = 90.0f;
bool isInit = false;
std::string header = "STAGE FAILED";
int playTime = 0;

BulletSpeed::BulletSpeed(float posX, float posY)
{
	x = posX;
	y = posY;
}

BulletSpeed::BulletSpeed()
{
}

BulletSpeed::~BulletSpeed()
{
}

static void AddGlowEffect(Sprite* sprite, const Color3B& colour, const Size& size)
{
	Vec2 pos = ccp(sprite->getContentSize().width / 2,
		sprite->getContentSize().height / 2);

	Sprite* glowSprite = Sprite::createWithSpriteFrameName("Images/Effects/fire.png");
	glowSprite->setColor(colour);
	glowSprite->setPosition(pos);
	glowSprite->setRotation(sprite->getRotation());

	BlendFunc f = { GL_ONE, GL_ONE };

	glowSprite->setBlendFunc(f);
	sprite->addChild(glowSprite, -1);

	// Run some animation which scales a bit the glow
	Sequence* s1 = Sequence::createWithTwoActions(
		ScaleTo::create(0.9f, size.width, size.height),
		ScaleTo::create(0.9f, size.width*0.75f, size.height*0.75f));

	CCRepeatForever* r = CCRepeatForever::create(s1);
	glowSprite->runAction(r);
}




