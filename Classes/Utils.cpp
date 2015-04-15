#include "Utils.h"
#include "Config.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "NDKHelper/NDKHelper.h"
#endif
#include "Manage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "CSUtils.h"
#endif

#if USE_GAME_SHARING
#include "GameSharing.h"
#endif //USE_GAME_SHARING

using namespace cocos2d;
using namespace cocos2d::experimental;

int Utils::backgroundSoundId = -1;

void Utils::playEffect(const char* path){
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	if (Manage::getInstance()->isPlaySound())
		AudioEngine::play2d(path);
}

void Utils::playBackgroundMusic(const char* path, bool isLoop){
	if (Manage::getInstance()->isPlayMusic())
	{
		if (backgroundSoundId == -1)
		{
			backgroundSoundId = AudioEngine::play2d(path, isLoop, 0.6f);
		}
		else
			resumeBackgroundMusic();
	}
		
}

void Utils::stopBackgroundMusic(){
	AudioEngine::pause(backgroundSoundId);
}

void Utils::resumeBackgroundMusic()
{
	AudioEngine::resume(backgroundSoundId);
}

void Utils::loadAd(){
	if(!Manage::getInstance()->isShowAd()) return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ValueMap valueMap;
	valueMap["ad_mob_id"] = AD_MOB_ID;
	valueMap["ad_mob_inter_id"] = AD_MOB_INTER_ID;
	Value parameters = Value(valueMap);
	sendMessageWithParams("loadAd", parameters);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->loadAd();
#endif
}

void Utils::showAd(){	
	if(!Manage::getInstance()->isShowAd()) return;
	CCLOG("showAd");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Value parameters = Value();
	sendMessageWithParams("showAd", parameters);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->showAd();
#endif
}

void Utils::showAdInter()
{
	if (!Manage::getInstance()->isShowAd()) return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Value parameters = Value();
	sendMessageWithParams("showAdInter", parameters);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->showAd();
#endif
}

void Utils::hideAd(){	
	if(!Manage::getInstance()->isShowAd()) return;
	CCLOG("hideAd");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Value parameters = Value();
	sendMessageWithParams("hideAd", parameters);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->hideAd();
#endif
}

void Utils::endGame(){

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Value parameters = Value();
	sendMessageWithParams("exit", parameters);
	exit(0);
#endif
}

void Utils::rate(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->rate();
#else
	Application::getInstance()->openURL(LINK_STORE);
#endif
}

void Utils::openStore(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->openStore();
#else
	Application::getInstance()->openURL(LINK_STORE);
#endif
}

char* Utils::encodeInt(int score){
	char *out;
	__String * str = __String::createWithFormat("%d", score);
	size_t ret = 10;
	base64Encode((unsigned char*)str->getCString(), (unsigned int)ret, &out);
	char *_out = new char[18];
	_out[0] = out[0];
	_out[1] = 'q';
	_out[2] = 'K';
	for (int i = 3; i < 18; i++)
		_out[i] = out[i - 2];
	return _out;
}

int Utils::decodeInt(const char* out){
	char *_out = new char[16];
	_out[0] = out[0];
	for (int i = 1; i < 16; i++)
		_out[i] = out[i + 2];
	unsigned char * decodedData = nullptr;
	int decodedDataLen = base64Decode((unsigned char*)_out, (unsigned int)strlen(_out), &decodedData);
	if (!is_number((char*)decodedData)) return 0;
	return atoi((char*)decodedData);
}

bool Utils::is_number(char * s)
{
	if (strlen(s) <= 0) return false;

	for (int i = 0; i < strlen(s); i++)
	if (s[i] < -1 && s[i] > 255 && !isdigit(s[i])) return false;


	return true;
}

int Utils::storeNum(int n){
	return n + 13;
}
	
int Utils::displayNum(int n){
	return n - 13;
}

void Utils::shareDefault(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ValueMap valueMap;
	valueMap["SHARE_BODY"] = SHARE_BODY;
	valueMap["SHARE_SUBJECT"] = SHARE_SUBJECT;
	Value parameters = Value(valueMap);
	sendMessageWithParams("shareDefault", parameters);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CSUtils::Instance->shareDefault();
#endif
}

int Utils::getRandInt(int from, int to){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return arc4random_uniform(to - from + 1)+from;
#else
	kTime++;
	if (kTime > 100) kTime = 0;
	srand(time(NULL));
	int k = rand();
	srand((kTime + k+31215*to+101)%102131);
	return rand()%(to - from) + from;
#endif
}

#if USE_GAME_SHARING
void Utils::showLeaderboard(){
	CCLOG("showLeaderboard");
	GameSharing::ShowLeaderboards();
}

void Utils::submitScore(int score){
	CCLOG("submitScore");
	GameSharing::SubmitScore(score);
}

#endif //USE_GAME_SHARING