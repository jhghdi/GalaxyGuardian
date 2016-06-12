#include "Stage1.h"

Stage1::Stage1()
{
	nextStage = new Stage2();

	minimum = SEC_TO_TICK(3);

	isLargeEnemy1Died = false;
	isLargeEnemy2Died = false;


	pathOfBackground = "Images/StageBackground/stage1.png";

	backgroundSound = STAGE1_SOUND;

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(backgroundSound);

	scrollSpeed = 5;

	message = "STAGE 1 CLEAR!!";

	achievement = "GetAchievementSTAGE1";

	time = 0;
}

Stage1::~Stage1()
{
	delete named1;
	delete named2;
}

void Stage1::Update(std::vector<Enemy*> *enemies)
{
	if (checkTime())
		return;

	// 3�� : �¸鿡�� �� 3�� ���� 1
	if (time == SEC_TO_TICK(3)) {
		for (int i = 0; i < 3; ++i){
			auto enemy = new Enemy(SMALL_ENEMY_1, Vec2(100 * (1 + i), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}

		minimum = SEC_TO_TICK(4);
	}

	// 4�� : �������� �� 3�� ���� 2
	else if (time == SEC_TO_TICK(4)) {
		for (int i = 0; i < 3; ++i) {
			auto enemy = new Enemy(SMALL_ENEMY_2, Vec2(WIN_WIDTH - (100 * (1 + i)), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}
		minimum = SEC_TO_TICK(5);
	}

	// 5�� �������� �� 3�� ���� 3
	else if (time == SEC_TO_TICK(5)) {
		for (int i = 0; i < 3; ++i) {
			auto enemy = new Enemy(SMALL_ENEMY_3, Vec2((WIN_WIDTH - 100) / (3 - i), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}
		minimum = SEC_TO_TICK(7);
	}

	// 7��~15�� �� 0.3�ʸ��� �� ���� ����1~3
	else if (time >= SEC_TO_TICK(7) && time <= SEC_TO_TICK(15) && time % 20 == 0) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_3));
		enemies->push_back(enemy);

		if (time == SEC_TO_TICK(15))
			minimum = SEC_TO_TICK(18);
		else
			minimum += 20;
	}

	// �÷��̾� �̻���
	else if (time == SEC_TO_TICK(18)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2((WIN_WIDTH - 100) / 3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(20);
	}

	// large ���� 1 
	else if (time == SEC_TO_TICK(20)) {
		auto enemy = new Enemy(LARGE_ENEMY_1, Vec2(WIN_WIDTH / 2, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);

		named1 = enemy;

		minimum = SEC_TO_TICK(23);
	}

	// large 1 ���Ͱ� ���׾��� ��� -> + 1�ʸ��� �� 1���� ����
	else if (time == SEC_TO_TICK(23) && !isLargeEnemy1Died) {
		if (named1->life <= 0)
			isLargeEnemy1Died = true;

		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_3), Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(22);
	}

	// large 1 ���Ͱ� �׾��� ��� -> �������� �Ѿ���� �ð�����
	else if (time == SEC_TO_TICK(23) && isLargeEnemy1Died) {
		time = SEC_TO_TICK(45);
		minimum = SEC_TO_TICK(48);
	}

	// �÷��̾� ��ź ����
	else if (time == SEC_TO_TICK(48)) {
		auto enemy = new Enemy(BOMB_ENEMY, Vec2(WIN_WIDTH / 3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(51);
	}

	// large ���� 2 ����
	else if (time == SEC_TO_TICK(51)) {
		auto enemy = new Enemy(LARGE_ENEMY_2, Vec2(WIN_WIDTH / 2, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / 3, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);

		named2 = enemy;

		minimum = SEC_TO_TICK(54);
	}

	// 1�ʸ��� �� 1���� ����
	else if (time == SEC_TO_TICK(54) && !isLargeEnemy2Died ) {
		if (named2->life <= 0)
			isLargeEnemy2Died = true;

		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_3), Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(53);
	}

	// large 2 ���Ͱ� �׾��� ��� -> �������� �Ѿ���� �ð�����
	else if (time == SEC_TO_TICK(54) && isLargeEnemy2Died) {
		time = SEC_TO_TICK(56);
		minimum = SEC_TO_TICK(58);
	}

	// �÷��̾� �̻���
	else if (time == SEC_TO_TICK(58)){
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		sendWarningMessage();

		minimum = SEC_TO_TICK(60);
	}

	// ����
	else if (time == SEC_TO_TICK(60) && isLargeEnemy2Died && isLargeEnemy1Died) {
		boss = new Boss(STAGE1_BOSS);
		enemies->push_back(boss);

		minimum = SEC_TO_TICK(61);
	}
	// ���� Ŭ���� üũ
	else if (time > SEC_TO_TICK(61) && boss->life <= 0)
	{
		isClear = true;
		ConfirmAchievement();

	}
	
}
