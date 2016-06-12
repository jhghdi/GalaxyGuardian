#include "Stage3.h"

Stage3::Stage3()
{
	time = 0;

	minimum = SEC_TO_TICK(3);

	isLargeEnemy1Died = false;
	isLargeEnemy2Died = false;

	nextStage = new Stage4();

	pathOfBackground = "Images/StageBackground/stage3.png";
	backgroundSound = STAGE3_SOUND;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(backgroundSound);

	message = "STAGE 3 CLEAR!!";

	achievement = "GetAchievementSTAGE3";
}

Stage3::~Stage3()
{
	delete named1;
	delete named2;
}

void Stage3::Update(std::vector<Enemy*> *enemies)
{
	if (checkTime())
		return;

	// 3초 : 좌면에서 적 3명 패턴 1
	if (time == SEC_TO_TICK(3)) {
		for (int i = 0; i < 3; ++i) {
			auto enemy = new Enemy(SMALL_ENEMY_7, Vec2(100 * (1 + i), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}
		minimum = SEC_TO_TICK(4);
	}

	// 4초 : 우측에서 적 3명 패턴 2
	else if (time == SEC_TO_TICK(4)) {
		for (int i = 0; i < 3; ++i) {
			auto enemy = new Enemy(SMALL_ENEMY_8, Vec2(WIN_WIDTH - (100 * (1 + i)), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}
		minimum = SEC_TO_TICK(5);
	}

	// 5초 우측에서 적 3명 패턴 3
	else if (time == SEC_TO_TICK(5)) {
		for (int i = 0; i < 3; ++i) {
			auto enemy = new Enemy(SMALL_ENEMY_9, Vec2((WIN_WIDTH - 100) / (3 - i), WIN_HEIGHT + 50));
			enemies->push_back(enemy);
		}
		minimum = SEC_TO_TICK(7);
	}

	// 7초~15초 약 0.3초마다 적 생성 패턴1~3
	else if (time >= SEC_TO_TICK(7) && time <= SEC_TO_TICK(15)) {
		auto enemy = new Enemy(random(SMALL_ENEMY_7, SMALL_ENEMY_9));
		enemies->push_back(enemy);

		if (time == SEC_TO_TICK(15))
			minimum = SEC_TO_TICK(18);
		else
			minimum += 20;
	}

	// 플레이어 미사일
	else if (time == SEC_TO_TICK(18)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2((WIN_WIDTH - 100) / 3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(20);
	}

	// large 몬스터 1 
	else if (time == SEC_TO_TICK(20)) {
		auto enemy = new Enemy(LARGE_ENEMY_1, Vec2(WIN_WIDTH *0.1, WIN_HEIGHT + 50), Vec2(WIN_WIDTH *0.1, WIN_HEIGHT * 0.7));
		enemies->push_back(enemy);

		named1 = enemy;

		enemy = new Enemy(LARGE_ENEMY_5, Vec2(WIN_WIDTH *0.8, WIN_HEIGHT + 50), Vec2(WIN_WIDTH *0.8, WIN_HEIGHT * 0.7));
		enemies->push_back(enemy);

		named2 = enemy;

		minimum = SEC_TO_TICK(24);
	}

	// large 1 몬스터가 죽었을 경우 -> 다음으로 넘어가도록 시간조정
	else if (time == SEC_TO_TICK(24) && (named1->life > 0 || named2->life > 0) ) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(22);
	}

	// 11초 && named1이 죽었다 : 다음으로 진행
	else if (time == SEC_TO_TICK(24) && named1->life <= 0 && named2->life <= 0) {
		delete named1;
		delete named2;
		isLargeEnemy1Died = true;

		time = SEC_TO_TICK(25);
		minimum = SEC_TO_TICK(27);
	}

	// 플레이어 폭탄 등장
	else if (time == SEC_TO_TICK(27)) {
		auto enemy = new Enemy(BOMB_ENEMY, Vec2(WIN_WIDTH / 3, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(29);
	}

	// large 몬스터 2 등장
	else if (time == SEC_TO_TICK(29)) {
		auto enemy = new Enemy(LARGE_ENEMY_6, Vec2(WIN_WIDTH / 2, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / 3, WIN_HEIGHT * 0.7));
		enemies->push_back(enemy);

		named2 = enemy;

		minimum = SEC_TO_TICK(32);
	}

	// 1초마다 적 1마리 등장
	else if (time == SEC_TO_TICK(32) && named2->life > 0) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_3), Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(30);
	}

	// large 2 몬스터가 죽었을 경우 -> 다음으로 넘어가도록 시간조정
	else if (time == SEC_TO_TICK(32) && named2->life <= 0) {
		delete named2;
		named2 = nullptr;
		isLargeEnemy2Died = true;

		time = SEC_TO_TICK(34);
		minimum = SEC_TO_TICK(35);
	}

	// 플레이어 미사일
	else if (time == SEC_TO_TICK(35)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		sendWarningMessage();

		minimum = SEC_TO_TICK(38);
	}

	// 보스
	else if (time == SEC_TO_TICK(38) && isLargeEnemy2Died && isLargeEnemy1Died) {
		boss = new Boss(STAGE3_BOSS);
		enemies->push_back(boss);
	}
	// 보스 클리어 체크
	else if (boss->life <= 0)
	{
		isClear = true;
		ConfirmAchievement();
	}

}
