#include "LoadingScene.h"
#include "Config.h"
#include "GameScene.h"
#include "VisibleRect.h"
#include "audio/include/AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "Utils.h"

using namespace cocos2d::experimental;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	auto loading = LoadingScene::create();
	scene->addChild(loading);

	return scene;
}

LoadingScene* LoadingScene::create()
{
	auto scene = new LoadingScene();
	if (scene->init())
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool LoadingScene::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	Utils::loadAd();

	auto logo = Sprite::create(sprite_loading_logo);
	this->addChild(logo);
	logo->setPosition(VisibleRect::center() + Vec2(0, logo->getContentSize().height));
	logo->setScale(2.0f);

	auto scaleTo = EaseBackInOut::create(ScaleTo::create(2.0f, 1.0f));
	auto seq = Sequence::create(scaleTo, CallFunc::create([this](){
		this->scheduleUpdate();
	}), NULL);
	logo->runAction(seq);

	auto bg = Sprite::create(sprite_bg_loading);
	this->addChild(bg);
	bg->setPosition(VisibleRect::center() + Vec2(0, -100));

	_progressTimer = ProgressTimer::create(Sprite::create(sprite_loading));
	_progressTimer->setType(ProgressTimer::Type::BAR);
	_progressTimer->setMidpoint(Vec2(0, 0));
	_progressTimer->setBarChangeRate(Vec2(1, 0));
	_progressTimer->setPercentage(0);
	this->addChild(_progressTimer);
	_progressTimer->setPosition(VisibleRect::center() + Vec2(0, -100));
	_idxLoaded = 0;
	_nNeedLoad = 5;
	_per = 100.0f / 5.0f;
	return true;
}

void LoadingScene::update(float dt)
{
	_idxLoaded++;
	if (_idxLoaded <= _nNeedLoad)
	{
		loadResource(_idxLoaded);
		_progressTimer->setPercentage(_idxLoaded * _per);
	}
	if (_idxLoaded > _nNeedLoad)
	{
		this->unscheduleUpdate();
		auto fadeout = FadeOut::create(0.2f);
		auto facein = FadeIn::create(0.2f);
		auto seq = Sequence::createWithTwoActions(fadeout, facein);
		auto repeat = RepeatForever::create(seq);

		_progressTimer->runAction(repeat);

		this->scheduleOnce([this](float dt){
			_progressTimer->stopAllActions();
			switchScene();
		}, 1.0f, "loadingkey");
	}
}

void LoadingScene::loadResource(int idx)
{
	switch (idx)
	{
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(UI_ATLAS);
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(LOST_EFFECT_ATLAS);
		break;
	case 3:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAINGAME_ATLAS);
		break;
	case 4:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TUTORIAL_ATLAS);
		//Sleep(500.0f);
		break;
	case 5:
		//preload music
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_background);

		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sound_ball_explosion);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sound_stack_balls_explosion);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sound_combo);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sound_lost);
		break;
	default:
		break;
	}
}

void LoadingScene::switchScene()
{
	auto game = GameScene::createScene();
	auto trans = TransitionFadeBL::create(1.5f, game);
	Director::getInstance()->replaceScene(trans);
}

