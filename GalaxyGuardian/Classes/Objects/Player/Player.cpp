#include "Player.h"


Player::Player()
{
	// �÷��̾� �⺻ image
	image = Sprite::createWithSpriteFrameName("default.png");
	image->setPosition(Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.2));
	image->setScale(SCALE_FACTOR);
	this->addChild(image);

	// ��ġ �̺�Ʈ ���
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Player::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Player::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Player::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ���̽�ƽ ���
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

	// �����ٷ� ���
	this->schedule(schedule_selector(Player::Update), 1/60.0f);
}

Player::~Player()
{
	delete[] image;
	delete[] joystick;
}

void Player::Move()
{
	// ȭ�� ������ ������ �ʵ��� ��ġ ����
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

	// x�� �����ӿ� ���� sprite ����
	if(joystick->getVelocity().x > 0)
		image->setSpriteFrame("left.png");
	else if(joystick->getVelocity().x < 0)
		image->setSpriteFrame("right.png");

	image->setPosition(Vec2(posX, posY));
}

void Player::Collision(int damage)
{
	// ȸ�ǻ��� -> return
	if (isAvoiding)
		return;

	// ü�°���
	--life;

	// effect sound ���
	SimpleAudioEngine::getInstance()->playEffect(PLAYER_DAMAGE_SOUND, false);

	// ��ź ���� ����
	bombCount = 1;

	// ���׾��� -> life sprite 1�� ����, �����ð����� ����, ��¦�̴� ȿ��
	if(life>0 && !isAvoiding)
	{
		ReducePlayerLife();
		notDamaged();
	}

	// �׾��� -> ���� ����Ʈ �� ���� ��� ������ �̵�
	else if (life <= 0 && !isAvoiding)
	{
		// player ������ ����
		this->unschedule(schedule_selector(Player::Update));

		// ���� Animation run
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
	// ������ ���� ����
	isMoving = true;
}

void Player::onTouchesEnded(const std::vector<Touch*>&, Event* event)
{
	image->setSpriteFrame("default.png");
	// ������ ���� ����
	isMoving = false;
}

void Player::SetAvoidingStatus()
{
	isAvoiding = !isAvoiding;
}

void Player::Update(float dt)
{
	// �� frame ���� player ������ ����
	if (isMoving)
		Move();

	// �ð����� �÷��̾��� �Ѿ��� �����Ѵ�.
	if(++shotInterval == 10)
	{ 
		// ���ο� �Ѿ��� ����
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

	// �÷��̾��� �Ѿ��� ��ġ�� �����Ѵ�.
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


