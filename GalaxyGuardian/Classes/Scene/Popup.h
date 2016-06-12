#pragma once
#ifndef __POPUP_H__
#define __POPUP_H__

#include "Common\GlobalDefinition.h"
#include "Scene\MainScene.h"


class Popup : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Popup);

	void doClose(Ref* sender);

	void doResume(Ref* sender);
};


#endif // !__POPUP_H__

