#include "Stage.h"



void Stage::Update(std::vector<Enemy*>* enemies)
{
	
}

std::string Stage::GetBackgroundImagePath()
{
	return pathOfBackground;
}

int Stage::GetScrollSpeed()
{
	return scrollSpeed;
}

int Stage::GetTime()
{
	return time;
}

void Stage::PlayBackgroundSound()
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(backgroundSound, true);
}

void Stage::StopBackgroundSound()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}

std::string Stage::GetMessage()
{
	return message;
}

bool Stage::checkTime()
{
	// tick ����
	++time;

	return time < minimum;
}

void Stage::ConfirmAchievement()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	/*
	JniHelper�� ���� org.cocos2dx.cpp�� �ִ�
	AppActivity class�� �Ķ���ͷ� ���� string �̸��� �Լ� ������ �����´�.
	*/
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx/cpp/AppActivity", achievement.c_str(), "()V"))
	{
		// �Լ�ȣ��
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//Release
		t.env->DeleteLocalRef(t.classID);
	}
#endif

}

void Stage::sendWarningMessage()
{
	SimpleAudioEngine::getInstance()->playEffect(WARNING_SOUND, false, 1.5f);
	char *warning = new char[2];
	sprintf(warning, "%d", WARNING);
	String* popParam = String::create(warning);
	NotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);
	return;
}


