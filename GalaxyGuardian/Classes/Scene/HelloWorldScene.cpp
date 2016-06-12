#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorldScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorldScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorldScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	auto cache = SpriteFrameCache::getInstance();
	// enemy의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Enemy/Small/Enimies.plist");
	// 플레이어의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Player/Player.plist");
	// player shoot 스프라이트 시트의 정보파일 읽기
	cache->addSpriteFramesWithFile("Images/Bullet/PlayerShoot.plist");
	// enemy shoot 스프라이트 시트의 정보파일 읽기
	cache->addSpriteFramesWithFile("Images/Bullet/EnemyShoot.plist");



	// background
	auto back = Sprite::create("Images/StageBackground/main.png");
	back->setPosition(Vec2(1100, 900));
	back->setScale(2.0f);
	this->addChild(back);

	// background action 
	auto action = Sequence::create(MoveTo::create(10.0f, Vec2(150, 200)), MoveTo::create(10.0f, Vec2(1100,900)),  nullptr);
	auto repeat = RepeatForever::create(action);
	back->runAction(repeat);

	// title
	auto title = Label::create("nGaurdian", "Marker Felt", 30);
	title->setScale(3.0f);
	title->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.7));
	this->addChild(title);

	// start
	//menu = LabelBMFont::create("Press Start", "font/futura-48.fnt");
	menu = Label::create("Press Start", "Marker Felt", 40);
	menu->setScale(2.0f);
	menu->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.3));
	this->addChild(menu);
	
	// menu action
	auto menuAction = Sequence::create(MoveBy::create(1.0f, Vec2(0, 50)), MoveBy::create(1.0f, Vec2(0, -50)), nullptr);
	auto menuRepeat = RepeatForever::create(menuAction);
	menu->runAction(menuRepeat);

	// touch event 들록
	// 터치 이벤트 등록
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorldScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorldScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorldScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool HelloWorldScene::onTouchBegan(Touch * touch, Event * event)
{
	if (menu->getBoundingBox().containsPoint(touch->getLocation()))
	{
		menu->setOpacity(180);
	}
	return true;
}

void HelloWorldScene::onTouchMoved(Touch * touch, Event * event)
{
	if (!menu->getBoundingBox().containsPoint(touch->getLocation()))
	{
		menu->setOpacity(255);
	}
	else
		menu->setOpacity(180);
}

void HelloWorldScene::onTouchEnded(Touch * touch, Event * event)
{
	if (!menu->getBoundingBox().containsPoint(touch->getLocation()))
	{
		menu->setOpacity(255);
	}
	else
	{
		auto scene = TransitionFade::create(2.0f, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
}



