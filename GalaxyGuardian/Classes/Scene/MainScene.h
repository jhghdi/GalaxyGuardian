#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "Common\GlobalDefinition.h"
#include "Scene\GameScene.h"

class MainScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	 CREATE_FUNC(MainScene);
	

private:
	LabelBMFont* menu;

	LabelBMFont* achievement;

	// Touch Event
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	// key Event
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void onExit();

	void onEnter();

	EventListenerTouchOneByOne* listener;
	EventListenerKeyboard* keyListener;
};

#endif // __MAIN_SCENE_H__
