#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include "Common\GlobalDefinition.h"
#include "Objects\Enemies\Boss.h"

#define DEFAULT_SCROLL_SPEED 5

class Stage
{
public:
	virtual void Update(std::vector<Enemy*> *enemies);

	// pointer of next Stage
	Stage* nextStage;
	
	// �������� Ŭ���� ����
	bool isClear = false;

	// get background path
	std::string GetBackgroundImagePath();
	
	// get bakcground scroll speed
	int GetScrollSpeed();

	// get time
	int GetTime();

	void PlayBackgroundSound();

	void StopBackgroundSound();

	std::string GetMessage();
protected:
	// ���� ���࿡ �ʿ��� �ð�
	int time;

	// �ð�üũ
	int minimum;

	// �ð��� ���� ����Ȯ��
	bool checkTime();

	// background image path
	std::string pathOfBackground;

	// boss Sprite
	Boss* boss;

	// scrolling speed of background
	int scrollSpeed = DEFAULT_SCROLL_SPEED;

	char* backgroundSound;

	// clear message
	std::string message;

	// achievement value
	std::string achievement;

	// jni Method(using for confirm achevement)
	void ConfirmAchievement();

	void sendWarningMessage();
};
#endif // ! __STAGE_H__

