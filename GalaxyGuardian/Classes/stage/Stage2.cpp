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

	// 3초 : 좌면에서 적 1명 패턴 4
	if (time == SEC_TO_TICK(3)) {
		auto enemy = new Enemy(SMALL_ENEMY_4, Vec2(100, WIN_HEIGHT + 50));
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(4);
	}

	// 4초 : 우측에서 적 1명 패턴 4
	else if (time == SEC_TO_TICK(4)) {
		auto enemy = new Enemy(SMALL_ENEMY_5, Vec2(250, WIN_HEIGHT + 50) );
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(5);
	}

	// 5초 우측에서 적 1명 패턴 4
	else if (time == SEC_TO_TICK(5)) {
		auto enemy = new Enemy(SMALL_ENEMY_6, Vec2(500, WIN_HEIGHT + 50) );
		enemies->push_back(enemy);
		minimum = SEC_TO_TICK(7);
	}

	// 7초 : Large enemy 3 생성
	else if (time == SEC_TO_TICK(7) ) {
		auto enemy = new Enemy(LARGE_ENEMY_3, Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT + 50), Vec2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);
		named1 = enemy;

		minimum = SEC_TO_TICK(9);
	
	}
	// 11초 && named1이 안죽었다 : 3초마다 적 생성(패턴 1~6)
	else if (time == SEC_TO_TICK(9) && named1->life > 0) {
		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(8);
	}

	// 11초 && named1이 죽었다 : 다음으로 진행
	else if (time == SEC_TO_TICK(11) && named1->life <= 0) {
		delete named1;
		isLargeEnemy1Died = true;
	
		time = SEC_TO_TICK(20);
		minimum = SEC_TO_TICK(22);
	}

	// 22초 :  플레이어 미사일
	else if (time == SEC_TO_TICK(22)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH * 0.9, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(24);
	}

	// 24초 ~ 35초 : 매초 마다 적 2마리씩 등장 
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

	// 폭탄, life 등장
	else if (time == SEC_TO_TICK(37)) {
		auto enemy = new Enemy(LIFE_ENEMY, Vec2(100 , WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		enemy = new Enemy(BOMB_ENEMY, Vec2(500, WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		minimum = SEC_TO_TICK(40);
	}

	//  40초 : large 몬스터 4 등장 (1마리)
	else if (time == SEC_TO_TICK(40)) {
		auto enemy = new Enemy(LARGE_ENEMY_4, Vec2( WIN_WIDTH /2, WIN_HEIGHT + 50), Vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.8));
		enemies->push_back(enemy);
		named2 = enemy;

		minimum = SEC_TO_TICK(42);
	}

	// 43초 : 2초마다 적 1마리 등장
	else if (time == SEC_TO_TICK(42) && named2->life > 0 ) {

		auto enemy = new Enemy(random(SMALL_ENEMY_1, SMALL_ENEMY_6), Vec2(WIN_WIDTH / random(1, 2), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		time = SEC_TO_TICK(41);
	}

	// large 2 몬스터가 죽었을 경우 -> 다음으로 넘어가도록 시간조정
	else if (time == SEC_TO_TICK(42) && named2->life <= 0) {
		isLargeEnemy2Died = true;
		delete named2;
		
		time = SEC_TO_TICK(45);
		minimum = SEC_TO_TICK(47);
	}

	// 플레이어 미사일
	else if (time == SEC_TO_TICK(47)) {
		auto enemy = new Enemy(ITEM_ENEMY, Vec2(WIN_WIDTH / (5 - random(1, 3)), WIN_HEIGHT + 50));
		enemies->push_back(enemy);

		sendWarningMessage();

		minimum = SEC_TO_TICK(50);
	}

	// 보스
	else if (time == SEC_TO_TICK(50) && isLargeEnemy2Died && isLargeEnemy1Died) {
		boss = new Boss(STAGE2_BOSS);
		enemies->push_back(boss);
	}

	// 보스 클리어 체크
	else if (time > SEC_TO_TICK(55)  && boss->life <= 0)
	{
		isClear = true;
		ConfirmAchievement();
	}

}
