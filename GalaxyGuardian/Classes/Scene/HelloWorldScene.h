#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "Common\GlobalDefinition.h"
#include "GameScene.h"

class HelloWorldScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	 CREATE_FUNC(HelloWorldScene);
	

private:
	Label* menu;

	// Touch Event
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

};

#endif // __MAIN_SCENE_H__
