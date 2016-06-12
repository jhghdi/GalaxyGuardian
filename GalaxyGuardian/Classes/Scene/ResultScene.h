#pragma once
#pragma once
#ifndef __RESULT_H__
#define __RESULT_H__

#include "Common\GlobalDefinition.h"
#include "Scene\MainScene.h"
#include "GameScene.h"

class ResultScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ResultScene);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void ShowAd();

	void onExit();

	// advertisement label
	Label* ad;

	// is view ad
	bool isViewAd;
};


#endif // !__RESULT_H__

