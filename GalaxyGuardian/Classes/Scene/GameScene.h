#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Objects\Player\Player.h"
#include "Objects\Enemies\Enemy.h"
#include "Popup.h"
#include "ResultScene.h"
#include "Common\GlobalDefinition.h"
#include "stage\Stage1.h"
#include "stage\Stage.h"

enum ZORDER { BACKGROUND, PLAYER, ENEMY, EFFECTS};


class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
  
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	// stage의 내용으로 현재 화면 초기화
	void InitByStage();

	void onEnter();

	void onExit();

	// player를 부활시킨다.
	void RevivePlayer();


private:
	// explosion image 생성 함수
	void Explosion(Vec2 position, float scale);
	
	//  explosion sprite 제거 함수 
	void RemoveSprite(Node *node);
	
	// touch method
	bool onTouchBegan(Touch *touch, Event* event);
	// back 버튼 처리
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	// Player Object
	Player* player;

	// Enemies
	std::vector<Enemy*> enemies;

	// enemyBullet 
	std::vector<Bullet*> enemyBullet; // enemies Bullet

	// game loop
	void Update(float dt);

	// change isEnemyBulletCreated status
	// it is only used to CallFunc
	void SetIsEnemyBulletCreated();

	// timer
	int time;

	// is Enemy bullet created
	bool isEnemyBulletCreated;

	// bomb button
	Sprite* bomb;

	// Pause Button
	Sprite* pause;

	// bomb Label
	LabelBMFont* bombCount;
	//Label* bombCount;

	// bakcground
	Sprite* backGround;
	Sprite* backGround2;

	// background scroll speed
	int backgroundSpeed;

	// stage
	Stage* stage;

	// Item을 얻는다
	void GetItems(int index);

	// 게임을 종료한다.
	void EndGame();

	// 플레이어 부활유무를 물어본다.
	void ShowMenu();

	// Player 부활메뉴
	Menu* menu;

	// popup Scene
	Scene* popup;

	// notification method
	void doNotification(Object* obj);

	// warning sprite
	Sprite* warning;

	// warning action
	Sequence* warningSeq;

	EventListenerTouchOneByOne* listener;
	EventListenerKeyboard* keyListener;
};

#endif // __GAME_SCENE_H__


