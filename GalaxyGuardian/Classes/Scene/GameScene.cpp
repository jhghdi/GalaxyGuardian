#include "GameScene.h"

USING_NS_CC;

static GameScene *scene = NULL;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }

	auto cache = SpriteFrameCache::getInstance();
	// large enemy의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Enemy/Large/LargeEnemies.plist");
	// enemy의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Enemy/Small/Enimies.plist");
	// 플레이어의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Player/Player.plist");
	// player shoot 스프라이트 시트의 정보파일 읽기
	cache->addSpriteFramesWithFile("Images/Bullet/PlayerShoot.plist");
	// enemy shoot 스프라이트 시트의 정보파일 읽기
	cache->addSpriteFramesWithFile("Images/Bullet/EnemyShoot.plist");
	// boss의 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Enemy/Boss/Boss.plist");
	// Item enemy 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("Images/Enemy/Items/Item.plist");

	// enemy, bullet 공간 할당
	enemies.reserve(50);
	enemyBullet.reserve(200);

	// 스테이지 초기화
	stage = new Stage1();
	InitByStage();

	// player 추가
	player = new Player();
	this->addChild(player, 4);
	player->image->runAction(MoveBy::create(1.0f, Vec2(0,100)));

	// bomb image
	bomb = Sprite::create("Images/Items/Bomb.png");
	bomb->setPosition(Vec2(WIN_WIDTH* 0.85, WIN_HEIGHT * 0.4));
	bomb->setOpacity(100);
	bomb->setScale(3.0f * SCALE_FACTOR);
	this->addChild(bomb, ZORDER::EFFECTS);

	// bomb label
	 bombCount = LabelBMFont::create("1", "font/futura-48.fnt");
	// bombCount = Label::create("Press Start", "Marker Felt", 40);
	bombCount->setString("1");
	bombCount->setPosition(Vec2(WIN_WIDTH* 0.85, WIN_HEIGHT * 0.48));
	bombCount->setScale(SCALE_FACTOR);
	bombCount->setOpacity(100);
	this->addChild(bombCount, ZORDER::EFFECTS);

	// Pause Image 추가
	pause = Sprite::create("Images/Items/Pause.png");
	pause->setPosition(Vec2(WIN_WIDTH* 0.85, WIN_HEIGHT * 0.9));
	pause->setScale(SCALE_FACTOR);
	pause->setOpacity(100);
	this->addChild(pause, ZORDER::EFFECTS);

	// 스케줄러 등록
	this->schedule(schedule_selector(GameScene::Update), 1/ 60.0f);

	//노티피케이션 추가
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::doNotification),
		"notification", NULL);

	// etc setting...
	isEnemyBulletCreated = true;
	time = 0;

    return true;
}

void GameScene::Explosion(Vec2 position, float scale)
{
	static Animate* animate;
	static Texture2D* texture;
	static CallFunc* removeFunc;
	static float width;
	static float height;

	if(!animate)
	{ 
		auto batch = SpriteBatchNode::create(EXP_IMG_PATH, 2);
		texture = batch->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		
		width = texture->getContentSize().width *0.25f;
		height = texture->getContentSize().height * 0.5f;

		for (int i = 0; i < 8; ++i)
		{
			// 첫째 줄에 4개의 프레임이 잇고, 5번째부터는 두 번째 줄에 있으므로
			// 5번째(i=4)부터는 y좌표의 값을 증가시켜야 한다
			int column = i % 4;
			int row = i / 4;

			animation->addSpriteFrameWithTexture(texture, Rect(column * width, row * height, width, height));
		}
		animate = Animate::create(animation);
		animate->retain();
	}

	auto sprite = Sprite::createWithTexture(texture, Rect(0, 0, width, height));
	
	sprite->setPosition(position);
	sprite->setScale(scale);
	this->addChild(sprite);
	auto sequence = Sequence::create(
		animate, 
		CallFunc::create(CC_CALLBACK_0(GameScene::RemoveSprite, this, sprite)),
		nullptr );
	sprite->runAction(sequence);

}

void GameScene::RemoveSprite(Node *node)
{
	this->removeChild(node);
	node = nullptr;
}

bool GameScene::onTouchBegan(Touch * touch, Event * event)
{
	if (!player)
		return false;

#pragma region Bomb Button
	if(bomb->getBoundingBox().containsPoint(touch->getLocation()) && player->bombCount > 0)
	{ 
		//player bomb Count감소, bomb label 수정
		char bombCnt[10];
		player->bombCount = --(player->bombCount);
		sprintf(bombCnt, "%d", player->bombCount);
		bombCount->setString(bombCnt);

		// enemy 총알 제거
		for (size_t i = 0; i < enemyBullet.size(); ++i)
			this->removeChild(enemyBullet[i]);

		enemyBullet.clear();

		auto batch = SpriteBatchNode::create(BOMB_IMG_PATH, 2);
		auto texture = batch->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.05f);
		
		auto size = Sprite::create(BOMB_IMG_PATH)->getContentSize().width;
		float margin = size / 4;

		for (int i = 0; i < 16; ++i)
		{
			// 첫째 줄에 6개의 프레임이 잇고, 7번째부터는 두 번째 줄에 있으므로
			// 5번째(i=6)부터는 y좌표의 값을 증가시켜야 한다
			int column = i % 4;
			int row = i / 4;

			animation->addSpriteFrameWithTexture(texture, Rect(column * margin, row * margin, margin, margin));
		}
		auto animate = Animate::create(animation);

		auto sprite = Sprite::createWithTexture(texture, Rect(0, 0, margin, margin));
		sprite->setPosition(Vec2(WIN_WIDTH /2 , WIN_HEIGHT /2));
		sprite->setScale(8.0f);

		this->addChild(sprite);
		auto sequence = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(GameScene::SetIsEnemyBulletCreated, this)),
			animate,
			CallFunc::create(CC_CALLBACK_0(GameScene::RemoveSprite, this, sprite)),
			CallFunc::create(CC_CALLBACK_0(GameScene::SetIsEnemyBulletCreated, this)),
			nullptr);
		SimpleAudioEngine::getInstance()->playEffect(BOMB_SOUND, false);
		sprite->runAction(sequence);
	}
#pragma endregion

#pragma region Pause Button
	else if (pause->getBoundingBox().containsPoint(touch->getLocation()))
	{
		Director::getInstance()->pause();
		popup = Popup::createScene();
		this->addChild(popup,200,200);
	}
#pragma endregion

	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK) 
	{
		if(!popup)
		{
		Director::getInstance()->pause();
		popup = Popup::createScene();
		this->addChild(popup, 200, 200);
		}
	}
}

void GameScene::Update(float dt)
{
	++time;

	//stage update
	if (isInit)
	{
		InitByStage();
		isInit = false;
	}

	if (!player)
		return;

	#pragma region Background Scrolling
	backGround->setPositionY(backGround->getPositionY() - backgroundSpeed);
	backGround2->setPositionY(backGround2->getPositionY() - backgroundSpeed);


	if (backGround2->getPositionY() <= 0 && backGround->getPositionY() <= 0)
	{
		backGround->setPositionY(backGround2->getPositionY());
		backGround2->setPositionY(backGround->getContentSize().height + backGround2->getPositionY());
	}
#pragma endregion
	#pragma region player와 enemy의 bullet간의 충돌 판정 처리
	for (std::vector<Bullet*>::iterator iter = enemyBullet.begin(); iter != enemyBullet.end();)
	{
		auto bullet = (Bullet*)(*iter);

		if (!(player->GetAvoidingStatus()) && 
			bullet->image->getBoundingBox().containsPoint(player->image->getPosition()) )
		{
			player->Collision(DAMAGE_TO_PLAYER);
			char bombCnt[10];
			sprintf(bombCnt, "%d", player->bombCount);
			bombCount->setString(bombCnt);

			this->removeChild(bullet);
			iter = enemyBullet.erase(iter);
		}
		// 화면 밖으로 나갈 경우 제거
		else if (CHECK_IMAGE_IS_OUT_THE_WINDOW(bullet->image->getPositionY()))
		{
			this->removeChild(bullet);
			iter = enemyBullet.erase(iter);
			bullet->release();
			bullet = nullptr;
		}
		else
		{
			Pattern::Move(bullet);
			++iter;
		}
	}
	#pragma endregion 
	for (std::vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end();)
	{
		auto enemy = (Boss*)(*iter);

		#pragma region Player와 적과의 angle을 구한다
		Vec2 shootVector = enemy->image->getPosition() - player->image->getPosition();
		float shootAngle = shootVector.getAngle();
		float cocosAngle = CC_RADIANS_TO_DEGREES(shootAngle);
		angleBetweenPlayerAndEnemy = cocosAngle;
		#pragma endregion
		#pragma region 적 기체가 화면 밖으로 나갈경우 제거
		if (CHECK_IMAGE_IS_OUT_THE_WINDOW(enemy->image->getPositionY()))
		{
			if(enemy->image)
				this->removeChild(enemy);
			iter = enemies.erase(iter);
			enemy->release();
			enemy = nullptr;
			continue;
		}
		#pragma endregion
		#pragma region enemy 총알 생성
		++(enemy->shotTime);
		if (enemy->IsReadyToShot())
		{
			auto bullets = Pattern::Create(enemy->GetPattern());
			
			int size = bullets.size();
			while (size > 0)
			{
				auto bullet = bullets.at(size - 1);
				if(bullet->image->getPosition() == Vec2::ZERO)
					bullet->image->setPosition(enemy->image->getPosition());	
				enemyBullet.push_back(bullet);
				this->addChild(bullet, ZORDER::ENEMY);
				--size;
			}
			
			if (enemy->GetPatternCount() > 0)
				enemy->SetNextPattern();
		}
		#pragma endregion
		#pragma region player가 폭탄사용중일 경우 적 미사일 제거
		if (!isEnemyBulletCreated)
		{ 
			for (auto bullet : enemyBullet)
				this->removeChild(bullet);
			enemyBullet.clear();
		}
		#pragma endregion
		#pragma region 적 개체와 player의  bomb, bullet 충돌 체크
		// 폭탄 체크
		if (!isEnemyBulletCreated)
			enemy->Collision(BOMB_DAMAGE);
		
		// bullet 충돌 체크
		for (std::vector<Bullet*>::iterator shotIter = player->bullets.begin(); shotIter != player->bullets.end();)
		{
			auto bullet = (Bullet*)(*shotIter);
			if (enemy->image->getBoundingBox().intersectsRect(bullet->image->getBoundingBox()))
			{
				enemy->Collision(bullet->GetDamage());
				player->removeChild(bullet);
				shotIter = player->bullets.erase(shotIter);
				bullet->release();
			}
			else
				++shotIter;
		}
		#pragma endregion
		#pragma region player와 enemy 충돌 체크
		if (!(player->GetAvoidingStatus()) && enemy->GetBoundingBoxOfImage().intersectsRect(player->GetBoundingBoxOfImage()))
		{
			player->Collision(DAMAGE_TO_PLAYER);
			char bombCnt[10];
			sprintf(bombCnt, "%d", player->bombCount);
			bombCount->setString(bombCnt);

			enemy->Collision(EXPLOSION_DAMAGE_OF_ENEMY);
		}
		#pragma endregion
		#pragma region life에 따른 explosion 처리
		if (enemy->life <= 0)
		{
			Explosion(enemy->image->getPosition(), enemy->GetScaleOfExplosion());

			// 적에따라 무기, 폭탄, 생명력을 얻을 수 있다.
			if (enemy->Getkind() == Enemy::ENEMY_KIND::ITEM)
				GetItems(enemy->GetIndex());

			removeChild(enemy);
			iter = enemies.erase(iter);
		}
		else if (player->life <= 0)
		{
			Explosion(player->image->getPosition(), 2.0f);
			removeChild(player);
			player = nullptr;
		
			auto sequence = Sequence::create(
				DelayTime::create(2.0f), 
				CallFunc::create(CC_CALLBACK_0(GameScene::ShowMenu, this)), 
				nullptr);

			this->runAction(sequence);
			
			return;
		}
		else
			++iter;
		#pragma endregion
	}
	#pragma region 해당 스테이지 맞는 적 생성
	std::vector<Enemy*> newEnemies;
	stage->Update(&newEnemies);
	if (newEnemies.size() > 0)
	{ 
		for (auto enemy : newEnemies)
		{ 
			this->addChild(enemy, ZORDER::ENEMY);
			enemy->Move();
			enemies.push_back(enemy);
		}
	}
	#pragma endregion
	#pragma region 스테이지 클리어시 다음스테이지로 넘어간다.
	if (stage->isClear)
	{
		for (auto enemy : enemies)
		{
			this->removeChild(enemy);
			enemy = nullptr;
		}
		enemies.clear();

		for (auto bullet : enemyBullet)
		{
			this->removeChild(bullet);
			bullet = nullptr;
		}
		enemyBullet.clear();

		playTime += time / 60;
		header = stage->GetMessage();

		stage->StopBackgroundSound();
		auto resultScene = TransitionFade::create(1.0f, ResultScene::createScene());
		Director::getInstance()->pushScene(resultScene);
		if(stage->nextStage != nullptr)
		{ 
			stage = stage->nextStage;
			stage->isClear = false;
			isInit = false;
		}
	}
	#pragma endregion
}

void GameScene::SetIsEnemyBulletCreated()
{
	isEnemyBulletCreated = !isEnemyBulletCreated;
}

void GameScene::GetItems(int index)
{
	switch (index)
	{
	case ITEM_ENEMY:
		player->SetWeapon(random((int)PLAYER_WEAPON::DEFAULT,(int)PLAYER_WEAPON::AUTO));
		SimpleAudioEngine::getInstance()->playEffect(ITEM_GAIN_SOUND, false);
		break;
	case BOMB_ENEMY:
		//player bomb Count증가
		char bombCnt[10];
		sprintf(bombCnt, "%d", ++(player->bombCount));
		bombCount->setString(bombCnt);
		SimpleAudioEngine::getInstance()->playEffect(BOMB_GAIN_SOUND, false);
		break;
	case LIFE_ENEMY:
		player->GetLife();
		SimpleAudioEngine::getInstance()->playEffect(LIFE_GAIN_SOUND, false);
		break;
	default:
		break;
	}

}

void GameScene::RevivePlayer()
{	
	this->removeChild(menu);
	player = new Player();
	this->addChild(player, 4);
	
	player->image->runAction(MoveBy::create(1.0f, Vec2(0, 100)));
	player->notDamaged();
	Director::getInstance()->resume();
	playTime = 0;
}

void GameScene::EndGame()
{
	Director::getInstance()->resume();
	playTime += time / 60;
	header = "STAGE FAILED";
	stage->StopBackgroundSound();
	auto resultScene = TransitionFade::create(1.0f, ResultScene::createScene());
	Director::getInstance()->pushScene(resultScene);
}

void GameScene::ShowMenu()
{
	Director::getInstance()->pause();

	auto question = MenuItemFont::create("Continue?");

	auto revive = MenuItemFont::create("YES", CC_CALLBACK_0(GameScene::RevivePlayer, this));
	auto end = MenuItemFont::create("NO", CC_CALLBACK_0(GameScene::EndGame, this));
	menu = Menu::create(question, revive, end, nullptr);
	menu->alignItemsVertically();
	this->addChild(menu, 6);
}

void GameScene::doNotification(Object * obj)
{
	String *pParam = (String*)obj;

	switch (pParam->intValue())
	{
	case GAIN_PLAYER_LIFE:
		if (player->life >= 4)
			return;
		player->GetLife();
		break;
	case WARNING:
		// warning sprite 초기화
		warning = Sprite::create(WARNING_IMAGE);
		warningSeq = Sequence::create(FadeIn::create(0.3f), FadeOut::create(0.3f), FadeIn::create(0.3f), FadeOut::create(0.3f), FadeIn::create(0.3f), FadeOut::create(0.3f), nullptr);
		warning->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.6));
		this->addChild(warning);
		warning->runAction(warningSeq);
		break;
	case POPUP:
		// warning sprite 초기화
		this->removeChild(popup, true);
		popup = nullptr;
		break;
	default:
		break;
	}
}

void GameScene::InitByStage()
{
	// 초기화유무 처리
	isInit = false;

	// 초기화
	for (auto bullet : enemyBullet)
		this->removeChild(bullet);
	enemyBullet.clear();

	// background
	backGround = Sprite::create(stage->GetBackgroundImagePath());
	backGround->setAnchorPoint(Vec2(0.5f, 0));
	backGround->setPositionY(0);
	backGround->setScaleX(2.0f * SCALE_FACTOR);
	this->addChild(backGround, ZORDER::BACKGROUND);

	backGround2 = Sprite::create(stage->GetBackgroundImagePath());
	backGround2->setAnchorPoint(Vec2(0.5f, 0));
	backGround2->setScaleX(2.0f * SCALE_FACTOR);
	backGround2->setPositionY(backGround->getContentSize().height);
	this->addChild(backGround2, ZORDER::BACKGROUND);

	// background scrolling speed
	backgroundSpeed = stage->GetScrollSpeed();

	if(player != nullptr)
		player->image->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.2));

	stage->PlayBackgroundSound();

	time = 0;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	// touchEvent 등록
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// key listener 등록
	this->setKeypadEnabled(true);
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

}

void GameScene::onExit()
{
	_eventDispatcher->removeEventListener(listener);
	_eventDispatcher->removeEventListener(keyListener);
	Layer::onExit();
}




