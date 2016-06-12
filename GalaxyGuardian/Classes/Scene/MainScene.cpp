#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
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

	// set default volume
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MAIN_SOUND);

	// background
	auto back = Sprite::create("Images/StageBackground/main.png");
	//back->setPosition(Vec2(1100, 900));
	back->setScale(4.0f);
	this->addChild(back);

	// background action 
	auto action = Sequence::create(MoveTo::create(10.0f, Vec2(150, 200)), MoveTo::create(10.0f, Vec2(1100,900)),  nullptr);
	auto repeat = RepeatForever::create(action);
	back->runAction(repeat);

	// title
	auto title = LabelBMFont::create("Galaxy \nGuardian", "font/futura-48.fnt");
	title->setScale(SCALE_FACTOR* 2.0f);
	title->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.7));
	this->addChild(title);

	// start
	menu = LabelBMFont::create("Press Start", "font/futura-48.fnt");
	menu->setScale(SCALE_FACTOR * 1.8f);
	menu->setPosition(Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.3));
	this->addChild(menu);
	
	// achievement
	achievement = LabelBMFont::create("Achievement", "font/futura-48.fnt");
	achievement->setScale(SCALE_FACTOR );
	achievement->setPosition(Vec2(WIN_WIDTH *0.4, WIN_HEIGHT * 0.15));
	this->addChild(achievement);


	// menu action
	auto menuAction = Sequence::create(MoveBy::create(1.0f, Vec2(0, 50)), MoveBy::create(1.0f, Vec2(0, -50)), nullptr);
	auto menuRepeat = RepeatForever::create(menuAction);
	menu->runAction(menuRepeat);

	// etc 
	playTime = 0;

	// preload sounds
	SimpleAudioEngine::getInstance()->preloadEffect(PLAYER_SHOT_SOUND);
	SimpleAudioEngine::getInstance()->preloadEffect(PLAYER_DAMAGE_SOUND);
	SimpleAudioEngine::getInstance()->preloadEffect(STAGE_CLEAR_SOUND);
	SimpleAudioEngine::getInstance()->preloadEffect(SMALL_DESTROY_SOUND);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_SOUND, true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.4f);
	return true;
}


bool MainScene::onTouchBegan(Touch * touch, Event * event)
{
	if (menu->getBoundingBox().containsPoint(touch->getLocation()))
		menu->setOpacity(180);
	else if (achievement->getBoundingBox().containsPoint(touch->getLocation()))
		achievement->setOpacity(180);
	else
	{
		menu->setOpacity(255);
		achievement->setOpacity(255);
	}
	return true;
}

void MainScene::onTouchMoved(Touch * touch, Event * event)
{
	if (menu->getBoundingBox().containsPoint(touch->getLocation()))
		menu->setOpacity(180);
	else if(achievement->getBoundingBox().containsPoint(touch->getLocation()))
		achievement->setOpacity(180);
	else
	{ 
		menu->setOpacity(255);
		achievement->setOpacity(255);
	}	
}

void MainScene::onTouchEnded(Touch * touch, Event * event)
{
	if (menu->getBoundingBox().containsPoint(touch->getLocation()))
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto scene = TransitionFade::create(2.0f, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
	else if (achievement->getBoundingBox().containsPoint(touch->getLocation()))
	{
		#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		/*
		JniHelper를 통해 org.cocos2dx.cpp에 있는
		AppActivity class의 파라미터로 들어온 string 이름의 함수 정보를 가져온다.
		*/
		std::string str = "ShowAchievement";
		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx/cpp/AppActivity", str.c_str(), "()V"))
		{
			// 함수호출
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			//Release
			t.env->DeleteLocalRef(t.classID);
		}
		#endif	
	}
	else
	{
		menu->setOpacity(255);
		achievement->setOpacity(255);
	}
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		Director::getInstance()->end();
}

void MainScene::onExit()
{
	_eventDispatcher->removeEventListener(listener);
	_eventDispatcher->removeEventListener(keyListener);

	Layer::onExit();
}

void MainScene::onEnter()
{
	Layer::onEnter();
	// touch event 들록
	// 터치 이벤트 등록
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// key event 등록
	this->setKeypadEnabled(true);
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}


