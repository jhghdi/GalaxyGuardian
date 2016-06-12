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
	// tick 증가
	++time;

	return time < minimum;
}

void Stage::ConfirmAchievement()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	/*
	JniHelper를 통해 org.cocos2dx.cpp에 있는
	AppActivity class의 파라미터로 들어온 string 이름의 함수 정보를 가져온다.
	*/
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx/cpp/AppActivity", achievement.c_str(), "()V"))
	{
		// 함수호출
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


