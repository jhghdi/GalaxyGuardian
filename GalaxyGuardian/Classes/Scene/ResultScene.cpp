
#include "ResultScene.h"


USING_NS_CC;

Scene* ResultScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ResultScene::create();


	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ResultScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	// 현재 scene 투명도 설정
	//this->setOpacity(10);

	// sound
	SimpleAudioEngine::getInstance()->preloadEffect(STAGE_CLEAR_SOUND);

	// bakcground
	auto back = Sprite::create("Images/StageBackground/Result.png");
	back->setAnchorPoint(Vec2(0.0f, 0.0f));
	back->setScale(1.5f * SCALE_FACTOR);
	this->addChild(back);

	// title
	auto title = Label::create(header, "Marker Felt", 40);

	title->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.8));
	this->addChild(title);

	// content
	char str[30];
	sprintf(str, "Play time : %dsec", playTime);
	auto time = Label::create(str, "Marker Felt",30);
	time->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.6));
	this->addChild(time);

	auto next = Label::create("Touch to next stage!", "Marker Felt", 30);
	next->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.3));
	this->addChild(next);
	if (header == "STAGE FAILED" || header == "Congraturations! \nALL STAGE CLEAR!!")
		next->setString("Touch to Main");
	else
		SimpleAudioEngine::getInstance()->playEffect(STAGE_CLEAR_SOUND, false);
	
	if (header == "STAGE FAILED" || header == "Congraturations! \nALL STAGE CLEAR!!")
	{
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//		JniMethodInfo t;
//		/*
//		JniHelper를 통해 org.cocos2dx.cpp에 있는
//		AppActivity class의 파라미터로 들어온 string 이름의 함수 정보를 가져온다.
//		*/
//		std::string str = "GetAchievement_STAGE1";
//		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx/cpp/AppActivity", str.c_str(), "()V"))
//		{
//			// 함수호출
//			t.env->CallStaticVoidMethod(t.classID, t.methodID);
//			//Release
//			t.env->DeleteLocalRef(t.classID);
//		}
//#endif	
		next->setString("Touch to Main");
	}
		else
	{
		// ad
		isViewAd = false;
		ad = Label::create("Show Advertisement(get a 1 life)", "Marker Felt", 30);
		ad->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.4));
		this->addChild(ad);
	}






	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ResultScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
}

bool ResultScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void ResultScene::onTouchEnded(Touch * touch, Event * event)
{	
	
	if (ad && ad->getBoundingBox().containsPoint(touch->getLocation()) && !isViewAd )
	{	
		ShowAd();
		isViewAd = true;
		ad->setVisible(false);

		char *pram = new char[2];
		sprintf(pram, "%d", GAIN_PLAYER_LIFE);
		String* popParam = String::create(pram);
		NotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);
	
		return;
	}

	if (header == "STAGE FAILED" || header == "Congraturations! \nALL STAGE CLEAR!!")
	{
		auto scene = MainScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	else
	{ 
		isInit = true;
		Director::getInstance()->popScene();
	}
}

void ResultScene::ShowAd()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	/*
	JniHelper를 통해 org.cocos2dx.cpp에 있는
	AppActivity class의 파라미터로 들어온 string 이름의 함수 정보를 가져온다.
	*/
	std::string str = "ShowAd";
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx/cpp/AppActivity", str.c_str(), "()V"))
	{
		// 함수호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//Release
		t.env->DeleteLocalRef(t.classID);
	}
#endif	
}

void ResultScene::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}


