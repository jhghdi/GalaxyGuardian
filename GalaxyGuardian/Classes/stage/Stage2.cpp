#include "Stage2.h"

Stage2::Stage2()
{
	time = 0;

	minimum = SEC_TO_TICK(3);

	isLargeEnemy1Died = false;
	isLargeEnemy2Died = false;

	nextStage = new Stage3();

	pathOfBackground = "Images/StageBackground/stage2.png";
	backgroundSound = STAGE2_SOUND;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(backgroundSound);

	message = "STAGE 2 CLEAR!!";

	achievement = "GetAchievementSTAGE2";
}

Stage2::~Stage2()
{
	delete named1;
	delete named2;
}

void Stage2::Update(std::vector<Enemy*> *enemies)
{
	if (checkTime())
		return;

	// 3�� : �¸鿡�� �� 1�� ���� 4
	if (time == SEC_TO_TICK(3)) {
		auto enemy = new Enemy(SMALL_ENEMY_4, Vec2(100, WIN_HEIGHT + 50));
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(4);
	}

	// 4�� : �������� �� 1�� ���� 4
	else if (time == SEC_TO_TICK(4)) {
		auto enemy = new Enemy(SMALL_ENEMY_5, Vec2(250, WIN_HEIGHT + 50) );
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(5);
	}

	// 5�� �������� �� 1�� ���� 4
	else if (time == SEC_TO_TICK(5)) {
		auto enemy = new Enemy(SMALL_ENEMY_6, Vec2(500, WIN_HEIGHT + 50) );
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(7);
	}

	// 7�� : Large enemy 3 ����
	else if (time == SEC_TO_TICK(7) ) {
		auto enemy = new Enemy(LARGE_ENEMY_3, Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT + 50), Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);
		named1 = enemy;

		minimum = SEC_TO_TICK(9);
	
	}
	// 11�� && named1�� ���׾��� : 3�ʸ��� �� ����(���� 1~6)
	else if (time == SEC_TO_TICK(9) && named1->life > 0) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(8);
	}

	// 11�� && named1�� �׾��� : �������� ����
	else if (time == SEC_TO_TICK(11) && named1->life <= 0) {
		delete named1;
		isLargeEnemy1Died = true;
	
		time = SEC_TO_TICK(20);
		minimum = SEC_TO_TICK(22);
	}

	// 22�� :  �÷��̾� �̻���
	else if (time == SEC_TO_TICK(22)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH * 0.9, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(24);
	}

	// 24�� ~ 35�� : ���� ���� �� 2������ ���� 
	else if (time >= SEC_TO_TICK(24) && time <= SEC_TO_TICK(35)) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6), Vec2(WIN_WIDTH * 0.9, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / random(1,8) , -MARGIN) );
		enemies->push_back(enemy);

		enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6), Vec2(100, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / random(1, 8), -MARGIN));
		enemies->push_back(enemy);

		if (time == SEC_TO_TICK(35))
			minimum = SEC_TO_TICK(37);
		else
			minimum = minimum + SEC_TO_TICK(1);
	}

	// ��ź, life ����
	else if (time == SEC_TO_TICK(37)) {
		auto enemy = new Enemy(LIFE_ENEMY, Vec2(100 , WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		enemy = new Enemy(BOMB_ENEMY, Vec2(500, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(40);
	}

	//  40�� : large ���� 4 ���� (1����)
	else if (time == SEC_TO_TICK(40)) {
		auto enemy = new Enemy(LARGE_ENEMY_4, Vec2( WIN_WIDTH /2, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);
		named2 = enemy;

		minimum = SEC_TO_TICK(42);
	}

	// 43�� : 2�ʸ��� �� 1���� ����
	else if (time == SEC_TO_TICK(42) && named2->life > 0 ) {

		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6), Vec2(WIN_WIDTH / random(1, 2), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(41);
	}

	// large 2 ���Ͱ� �׾��� ��� -> �������� �Ѿ���� �ð�����
	else if (time == SEC_TO_TICK(42) && named2->life <= 0) {
		isLargeEnemy2Died = true;
		delete named2;
		
		time = SEC_TO_TICK(45);
		minimum = SEC_TO_TICK(47);
	}

	// �÷��̾� �̻���
	else if (time == SEC_TO_TICK(47)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		sendWarningMessage();

		minimum = SEC_TO_TICK(50);
	}

	// ����
	else if (time == SEC_TO_TICK(50) && isLargeEnemy2Died && isLargeEnemy1Died) {
		boss = new Boss(STAGE2_BOSS);
		enemies->push_back(boss);
	}

	// ���� Ŭ���� üũ
	else if (time > SEC_TO_TICK(55)  && boss->life <= 0)
	{
		isClear = true;
		ConfirmAchievement();
	}

}
