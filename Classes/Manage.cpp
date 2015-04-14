#include "Manage.h"
#include "Config.h"
#include "cocos2d.h"

using namespace cocos2d;

Manage* Manage::instance= nullptr;

Manage::Manage()
{
	showAd = IS_LOAD_AD;
	playMusic = UserDefault::getInstance()->getBoolForKey(KEY_PLAY_MUSIC, true);
	playSound = UserDefault::getInstance()->getBoolForKey(KEY_PLAY_SOUND, true);
}

Manage* Manage::getInstance()
{
	if (instance== nullptr) {
		instance = new Manage();
	}
	return instance;
}

bool Manage::isShowAd(){
	return showAd;
}

bool Manage::isPlayMusic(){
	return playMusic;
}
void Manage::setPlayMusic(bool playMusic){
	this->playMusic = playMusic;
	UserDefault::getInstance()->setBoolForKey(KEY_PLAY_MUSIC, playMusic);
}
bool Manage::isPlaySound(){
	return playSound;
}
void Manage::setPlaySound(bool playSound){
	this->playSound = playSound;
	UserDefault::getInstance()->setBoolForKey(KEY_PLAY_SOUND, playSound);
}