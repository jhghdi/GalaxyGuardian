#include "Player.h"


Player::Player()
{
	// 플레이어 기본 image
	image = Sprite::createWithSpriteFrameName("default.png");
	image->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.2));
	image->setScale(SCALE_FACTOR);
	this->addChild(image);

	// 터치 이벤트 등록
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Player::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Player::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Player::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 조이스틱 등록
	joystick = Joystick::create();
	joystick->init();
	this->addChild(joystick);

	// default setting
	life = 3;
	weapon = PLAYER_WEAPON::DEFAULT;
	isMoving = false;
	moveSpeed = 8.0f;
	isAvoiding = false;
	shotInterval = 0;
	bombCount = DEFAULT_BOMBCOUNT;

	// player life count sprite
	for (int i = 0; i < 2; ++i)
	{
		auto player = Sprite::createWithSpriteFrameName("default.png");
		player->setPosition(Vec2((WIN_WIDTH *0.15) + (i * image->getContentSize().width)+ 10, WIN_HEIGHT * 0.9));
		player->setOpacity(180);
		
		this->addChild(player);
		playerLife.push(player);
	}

	// sound 
	SimpleAudioEngine::getInstance()->preloadEffect(PLAYER_SHOT_SOUND);
	SimpleAudioEngine::getInstance()->preloadEffect(PLAYER_DAMAGE_SOUND);

	// 스케줄러 등록
	this->schedule(schedule_selector(Player::Update), 1/60.0f);
}

Player::~Player()
{
	delete[] image;
	delete[] joystick;
}

void Player::Move()
{
	// 화면 밖으로 나가지 않도록 위치 조정
	posX = image->getPositionX() + (joystick->getVelocity().x * moveSpeed);
	if (posX > WIN_WIDTH - MARGIN)
		posX = WIN_WIDTH - MARGIN;
	else if (posX < MARGIN)
		posX = MARGIN;

	posY = image->getPositionY() + (joystick->getVelocity().y * moveSpeed);
	if (posY > WIN_HEIGHT - MARGIN)
		posY = WIN_HEIGHT - MARGIN;
	else if (posY < MARGIN)
		posY = MARGIN;

	// x축 움직임에 따른 sprite 변경
	if(joystick->getVelocity().x > 0)
		image->setSpriteFrame("left.png");
	else if(joystick->getVelocity().x < 0)
		image->setSpriteFrame("right.png");

	image->setPosition(Vec2(posX, posY));
}

void Player::Collision(int damage)
{
	// 회피상태 -> return
	if (isAvoiding)
		return;

	// 체력감소
	--life;

	// effect sound 출력
	SimpleAudioEngine::getInstance()->playEffect(PLAYER_DAMAGE_SOUND, false);

	// 폭탄 갯수 조정
	bombCount = 1;

	// 안죽었다 -> life sprite 1개 제거, 일정시간동안 무적, 반짝이는 효과
	if(life>0 && !isAvoiding)
	{
		ReducePlayerLife();
		notDamaged();
	}

	// 죽었다 -> 폭발 이펙트 후 게임 결과 씬으로 이동
	else if (life <= 0 && !isAvoiding)
	{
		// player 스케줄 제거
		this->unschedule(schedule_selector(Player::Update));

		// 폭발 Animation run
		image->setVisible(false);

		SetAvoidingStatus();
	}
}

bool Player::onTouchesBegan(const std::vector<Touch*>&, Event* event)
{
	return true;
}

void Player::onTouchesMoved(const std::vector<Touch*>&, Event* event)
{
	// 움직임 상태 변경
	isMoving = true;
}

void Player::onTouchesEnded(const std::vector<Touch*>&, Event* event)
{
	image->setSpriteFrame("default.png");
	// 움직임 상태 변경
	isMoving = false;
}

void Player::SetAvoidingStatus()
{
	isAvoiding = !isAvoiding;
}

void Player::Update(float dt)
{
	// 매 frame 마다 player 움직임 제어
	if (isMoving)
		Move();

	// 시간마다 플레이어의 총알을 생성한다.
	if(++shotInterval == 10)
	{ 
		// 새로운 총알을 생성
		auto node = this->getParent();

		std::vector<Bullet*> newBullets = Pattern::Create(weapon);
		int size = newBullets.size();

		while (size > 0)
		{
			// insert player's bullet vactor and addchild player
			auto bullet = newBullets.at(size - 1);
			bullet->image->setPosition(this->image->getPosition());
			this->addChild(bullet);


			bullets.push_back(newBullets.at(size-1));
			--size;
		}

		newBullets.clear();
		shotInterval = 0;
	}

	// 플레이어의 총알의 위치를 변경한다.
	int size = bullets.size();
	while (size > 0)
	{
		Pattern::Move(bullets[size - 1]);
		--size;
	}
}

Rect Player::GetBoundingBoxOfImage()
{
	auto width = image->getBoundingBox().size.width;
	auto height = image->getBoundingBox().size.height;
	return Rect( (width *0.5)-5, (height * 0.5)-5, 5, 5);
}

bool Player::GetAvoidingStatus()
{
	return isAvoiding;
}

void Player::notDamaged()
{
	auto setAvoid = CallFunc::create(CC_CALLBACK_0(Player::SetAvoidingStatus, this));
	auto repeat = Repeat::create(Sequence::create(FadeOut::create(0.2f), FadeIn::create(0.2f), nullptr), 5);
	auto action = Sequence::create(setAvoid, repeat, setAvoid, nullptr);
	image->runAction(action);
}

void Player::ReducePlayerLife()
{
	if (playerLife.empty())
		return;

	auto sprite = playerLife.top();
	this->removeChild(sprite);
	playerLife.pop();
	sprite = nullptr;
}

void Player::SetWeapon(int weaponIdx)
{
	weapon = weaponIdx;
}

void Player::GetLife()
{
	auto player = Sprite::createWithSpriteFrameName("default.png");
	auto size = playerLife.size();
	player->setPosition(Vec2((WIN_WIDTH *0.15) + (size * image->getContentSize().width ) + 10, WIN_HEIGHT * 0.9));
	player->setOpacity(180);
	this->addChild(player);
	playerLife.push(player);
}


