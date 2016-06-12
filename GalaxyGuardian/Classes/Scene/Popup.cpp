
#include "Popup.h"


USING_NS_CC;

Scene* Popup::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Popup::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Popup::init()
{
	//////////////////////////////
	// 1. super init first

	if (!LayerColor::initWithColor(ccc4(0, 0, 0, 30)))
	{
		return false;
	}

	// 메뉴 아이템 생성 및 초기화
	auto item1 = MenuItemFont::create(
		"Resume",
		CC_CALLBACK_1(Popup::doResume, this));
	item1->setColor(Color3B::WHITE);
	item1->setPositionY(item1->getPositionY() + 50);

	auto item2 = MenuItemFont::create(
		"Go to the Main menu",
		CC_CALLBACK_1(Popup::doClose, this));
	item2->setColor(Color3B::WHITE);
	item2->setPositionY(item1->getPositionY() - 50);

	// 메뉴 생성
	auto menu = Menu::create(item1, item2, nullptr);

	// 메뉴 위치
	menu->setPosition(Vec2(WIN_WIDTH /2 ,WIN_HEIGHT /2));
	this->addChild(menu);

	return true;
}

void Popup::doClose(Ref* sender)
{
	Director::getInstance()->resume();
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Popup::doResume(Ref* sender)
{
	Director::getInstance()->resume();
	this->removeFromParentAndCleanup(true);

	char *pram = new char[2];
	sprintf(pram, "%d", POPUP);
	String* popParam = String::create(pram);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);
}
