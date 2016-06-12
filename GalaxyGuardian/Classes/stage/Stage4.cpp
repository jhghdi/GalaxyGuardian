#include "Stage4.h"

Stage4::Stage4()
{
	time = 0;

	minimum = SEC_TO_TICK(3);

	isLargeEnemy1Died = false;
	isLargeEnemy2Died = false;

	nextStage = nullptr;

	pathOfBackground = "Images/StageBackground/stage4.png";
	backgroundSound = STAGE4_SOUND;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(backgroundSound);

	message = "Congraturations! \nALL STAGE CLEAR!!";

	achievement = "GetAchievementSTAGE4";
}

Stage4::~Stage4()
{
	delete named1;
	delete named2;
}

void Stage4::Update(std::vector<Enemy*> *enemies)
{
	if (checkTime())
		return;

	// 3�� : ���
	if (time == SEC_TO_TICK(3)) {
		sendWarningMessage();
		minimum = SEC_TO_TICK(6);
	}

	// 6�� : ����
	if (time == SEC_TO_TICK(6)) {
		boss = new Boss(STAGE4_BOSS);
		enemies->push_back(boss);
		named1 = boss;

		minimum = SEC_TO_TICK(9);
	}

	// 9�� : ���� Ŭ���� Ȯ��
	else if (time == SEC_TO_TICK(9)) {
		if(named1->life > 0)
			time = SEC_TO_TICK(8);
		else {
			ConfirmAchievement();
			achievement = "GetAchievementFINAL";
			minimum = SEC_TO_TICK(12);
		}
			
	}

	// 12�� ������
	else if (time == SEC_TO_TICK(12)) {
		auto enemy = new Enemy(LIFE_ENEMY, Vec2(WIN_WIDTH * 0.3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);
		sendWarningMessage();

		minimum = SEC_TO_TICK(13);
	}

	// 9�� ��ź
	else if (time == SEC_TO_TICK(13)) {
		auto enemy = new Enemy(BOMB_ENEMY, Vec2(WIN_WIDTH / 3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(15);
	}

	// 11�� ��������
	else if (time == SEC_TO_TICK(15) ) {
		boss = new Boss(FINAL_BOSS);
		enemies->push_back(boss);
		named2 = boss;

		minimum = SEC_TO_TICK(18);
	}
	// ���� Ŭ���� üũ
	else if (time == SEC_TO_TICK(18) && (boss->life > 0))
		time = SEC_TO_TICK(16);
	else if(time == SEC_TO_TICK(18) && (boss->life <= 0))
	{ 
		isClear = true;
		ConfirmAchievement();
	}
}
