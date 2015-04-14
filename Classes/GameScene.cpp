#include "GameScene.h"
#include "Config.h"
#include "VisibleRect.h"
#include "GestureDefines.h"
#include "Balloon.h"
#include "GestureDefines.h"
#include "BalloonManager.h"
#include "RectMultiBalloon.h"
#include "StackMultiBalloon.h"
#include "MultiballoonManager.h"
#include <algorithm>
#include "Utils.h"
#include "ShaderLayer.h"
#include "ShakeAction.h"
#include "BackgroundEffect.h"
#include <cmath>
#include "LostEffect.h"
#include "Manage.h"

USING_NS_CC;
using namespace cocos2d::experimental;
Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto gamelayer = GameScene::create();
	scene->addChild(gamelayer, kGame);

	//auto shakelayer = ShaderLayer::create(shake_fsh, shake_vsh);
	//scene->addChild(shakelayer, kShader);

	//auto background = Sprite::createWithSpriteFrameName(maingame_bg);
	//background->setPosition(VisibleRect::center());
	//shakelayer->addChild(background, kBackground);

	UserDefault::getInstance()->setBoolForKey(KEY_IS_TUTORIAL, false);
	return scene;
}

GameScene* GameScene::create()
{
	auto scene = new GameScene();
	if (scene->init())
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_gameMode = GameMode::Init;

	initGestures();
	initBackground();
	initControls();
	initMenu();

	//startGame();
	Utils::playBackgroundMusic(music_background, true);
	Utils::showAd();
	return initTouch();
}

void GameScene::startGame()
{
	bool isTutorial = UserDefault::getInstance()->getBoolForKey(KEY_IS_TUTORIAL, false);
	if (isTutorial)
	{
		initGame();
	}
	else
	{
		initTutorial();
	}
}

void GameScene::initGame()
{
	this->initValues();
	this->initActions();
	_background->start();
}

void GameScene::initTutorial()
{
	getChildByName("menucontrol")->setVisible(false);

	_b1 = Balloon::create(this, kBalloon, 0);
	_b1->setPosition(VisibleRect::leftTop() + Vec2(ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2(ENEMY_WIDTH * 2, 0));
	_b1->setActive(true);
	
	auto moveto = MoveBy::create(2.0f, Vec2(0, -_screenHeight / 2.0f));
	auto seq = Sequence::create(moveto, CallFunc::create([this](){
		_layerShadow->setVisible(true);
		_drawer = Sprite::createWithSpriteFrameName("tutorial_down_arrow-0.png");
		_drawer->setScale(2.5f);
		_drawer->setPosition(VisibleRect::center());
		this->addChild(_drawer, kGesture);
		auto ani = Animation::create();
		for (int i = 0; i < 15; i++)
		{
			auto name = StringUtils::format("tutorial_down_arrow-%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
			ani->addSpriteFrame(frame);
		}
		ani->setDelayPerUnit(0.15f);
		ani->setRestoreOriginalFrame(true);
		auto _animationEnemy = RepeatForever::create(Animate::create(ani));
		_drawer->runAction(_animationEnemy);
		_gameMode = GameMode::Tutorial;
		_idBalloonTutorial = 0;
	}), NULL);
	_b1->doAction(seq);
}

void GameScene::initValues()
{
	_gameMode = GameMode::Playing;
	_score = 0;

	_balloonInterval = BALLOON_INTERVAL;
	_balloonSpeed = TIMEDROP_INIT;
	_balloonTimer = 0;
	_isNext = true;

	_increaseDifficultyInterval = TIME_increaseDifficulty;
	_increaseDifficultyTimer = 0;

	_lb->setString(StringUtils::toString<int>(_score));

	if (_balloonManager != NULL)
	{
		_balloonManager->reset();
	}
	if (_multiballoonManager != NULL)
	{
		_multiballoonManager->reset();
	}
	_isNeedParticle = true;
	_idxParticle = 0;

	_multiballoonSpeed = 7.5f;

	this->scheduleBalloons();
	this->scheduleMultiballoons();

	getChildByName("menucontrol")->setVisible(true);
}

void GameScene::initGestures()
{
	createGesture(gesture1, sizeof(gesture1) / sizeof(float), 0);
	createGesture(gesture2, sizeof(gesture2) / sizeof(float), 1);
	createGesture(gesture3, sizeof(gesture3) / sizeof(float), 2);
	createGesture(gesture4, sizeof(gesture4) / sizeof(float), 3);
	createGesture(gesture5, sizeof(gesture5) / sizeof(float), 4);
	createGesture(gesture6, sizeof(gesture6) / sizeof(float), 5);
	createGesture(gesture7, sizeof(gesture7) / sizeof(float), 6);
	createGesture(gesture8, sizeof(gesture8) / sizeof(float), 7);

	_gesture = new ofxGesture();
	_screenHeight = Director::getInstance()->getVisibleSize().height;

	_balloonManager = new BalloonManager(this, kBalloon);
	_multiballoonManager = new MultiballoonManager(this, kBalloon);

	_gestureDraw = DrawNode::create();
	this->addChild(_gestureDraw, kGesture);

	//init particles
	//for (int i = 0; i < MAX_PARTICLES; i++)
	//{
	//	auto tmp = ParticleSystemQuad::create("brush.plist");
	//	tmp->setAutoRemoveOnFinish(true);
	//	_particles.pushBack(tmp);
	//}
}

void GameScene::createGesture(float* gesture, int n, int id)
{
	auto g = new ofxGesture();
	g->id = id;
	for (int i = 0, imax = n / 2; i < imax; i++)
	{
		g->addPoint(gesture[2 * i], gesture[2 * i + 1]);
	}
	_dollar.addGesture(g);
}

void GameScene::initBackground()
{
	TTFConfig config;
	config.fontFilePath = FONT;
	config.fontSize = 222;
	_lb = Label::createWithTTF(config, "0");
	_lb->setColor(Color3B::YELLOW);
	_lb->setPosition(VisibleRect::center().x, VisibleRect::center().y);
	this->addChild(_lb, kScore);

	_background = BackgroundEffect::create();
	this->addChild(_background, kBackground);
	_background->setPosition(VisibleRect::leftTop());

	auto sprite = Sprite::createWithSpriteFrameName(bg_com_store);
	this->addChild(sprite, kBalloon);
	sprite->setPosition(VisibleRect::leftBottom());
	sprite->setAnchorPoint(Vec2(0, 0));

	_character = Character::create();
	this->addChild(_character, kScore);
	_character->setPosition(VisibleRect::center().x / 2.0f, BACKGROUND_OFFSET);

	_lostEffect = LostEffect::create();
	this->addChild(_lostEffect, kScore);

	TTFConfig config2;
	config2.fontFilePath = FONT;
	config2.fontSize = 125;

	_ready = Sprite::createWithSpriteFrameName("ready.png");
	_ready->setPosition(VisibleRect::center());
	this->addChild(_ready, kControl);
	_ready->setVisible(false);

	_go = Sprite::createWithSpriteFrameName("go.png");
	_go->setPosition(VisibleRect::center());
	this->addChild(_go, kControl);
	_go->setVisible(false);

	_lbPause = Label::createWithTTF(config2, "Paused");
	_lbPause->setPosition(VisibleRect::center());
	this->addChild(_lbPause, kControl);
	_lbPause->setVisible(false);

	_lbCombo = Label::createWithTTF(config2, "Combo X2");
	_lbCombo->setPosition(VisibleRect::center());
	this->addChild(_lbCombo, kControl);
	_lbCombo->setVisible(false);

	_background->start();
}

void GameScene::initControls()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//build menu control
	auto pausedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(sprite_bt_paused), NULL);
	auto resumeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(sprite_bt_resume), NULL);
	auto togglePause = MenuItemToggle::createWithCallback([this](Ref* ref){
		auto bt = (MenuItemToggle*)ref;
		int idx = bt->getSelectedIndex();
		log("idx %d", idx);
		if (idx == 0)//paused -> playing
		{
			_gameMode = _lastState;
			resumeGame();
		}
		else if (idx == 1)//playing -> paused
		{
			_lastState = _gameMode;
			_gameMode = GameMode::Paused;
			pausedGame();
		}
	}, pausedItem, resumeItem, NULL);
	
	togglePause->setPosition(VisibleRect::rightTop() - Vec2(40, 40));

	auto onSoundItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(sprite_bt_sound), NULL);
	auto offSoundItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(sprite_bt_sound_down), NULL);
	auto toggleSound = MenuItemToggle::createWithCallback([this](Ref* ref){
		Manage::getInstance()->setPlayMusic(!Manage::getInstance()->isPlayMusic());
		auto bt = (MenuItemToggle*)ref;
		int idx = bt->getSelectedIndex();
		if (idx == 1)
		{
			Utils::stopBackgroundMusic();
		}
		else
		{
			Utils::playBackgroundMusic(music_background, true);
		}

	}, onSoundItem, offSoundItem, NULL);

	if (!Manage::getInstance()->isPlayMusic())
	{
		toggleSound->setSelectedIndex(1);
	}
	toggleSound->setPosition(VisibleRect::leftTop() - Vec2(-40, 40));
	auto menu = Menu::create(togglePause, toggleSound, NULL);

	menu->setPosition(0, 0);
	this->addChild(menu, kControl, "menucontrol");
}

void GameScene::initMenu()
{
	//create menu start
	TTFConfig config;
	config.fontFilePath = FONT;
	config.fontSize = 50;
	config.outlineSize = 2;

	getChildByName("menucontrol")->setVisible(false);
	_layerShadow = LayerColor::create(Color4B(150, 150, 150, 170), VisibleRect::getVisibleRect().size.width, VisibleRect::getVisibleRect().size.height);
	this->addChild(_layerShadow, kShadow);

	_menuStart = Sprite::createWithSpriteFrameName(sprite_menu_bg);
	this->addChild(_menuStart, kControl);
	_menuStart->setPosition(VisibleRect::center() + Vec2(0, 1064));

	int bscore = UserDefault::getInstance()->getIntegerForKey(KEY_BEST_SCORE, 0);
	std::string str;
	if (bscore == 0)
	{
		str = "WelcomeTo \n MagicTick!";
	}
	else
	{
		str = StringUtils::format("BestScore: %d", bscore);
	}
	
	auto tBestscore = Label::createWithTTF(config, str);
	_menuStart->addChild(tBestscore);
	tBestscore->setPosition(300, 280);

	auto btPlay = addButton(sprite_bt_play, sprite_bt_play_down, sprite_bt_play_down, [this](Ref* ref){
		auto scale = EaseBackInOut::create(ScaleTo::create(0.5f, 1.5));
		auto fadeOut = FadeOut::create(1.0f);
		auto spawn = Spawn::create(scale, fadeOut, NULL);
		auto seq = Sequence::create(spawn, CallFuncN::create([this](Node* node){
			_background->reset();
			_layerShadow->setVisible(false);
			startGame();
			node->removeFromParentAndCleanup(true);
		}), NULL);
		_menuStart->runAction(seq);
	});
	btPlay->setPosition(300, 90);
	//btPlay->setScale(1.2f);

	auto menu = Menu::create(btPlay, NULL);
	menu->setPosition(0, 0);
	_menuStart->addChild(menu);

	auto delay = DelayTime::create(0.8f);
	auto moveTo = MoveBy::create(0.8f, Vec2(0, -1000));
	auto seq = Sequence::create(delay, moveTo, NULL);
	_menuStart->runAction(seq);

	//create menu result
	_menuResult = Sprite::createWithSpriteFrameName(sprite_menu_bg);
	this->addChild(_menuResult, kControl);
	_menuResult->setPosition(VisibleRect::center() + Vec2(0, 1064));
	_menuResult->setVisible(false);
	//_menuResult->runAction(MoveBy::create(0.8f, Vec2(0, -1000)));
	
	auto txtBestscore = Label::createWithTTF(config, "BestScore: ");
	_menuResult->addChild(txtBestscore);
	txtBestscore->setPosition(190, 350);

	auto txtScore = Label::createWithTTF(config, "Score:     ");
	_menuResult->addChild(txtScore);
	txtScore->setPosition(txtBestscore->getPosition() + Vec2(0, -120));

	TTFConfig config2;
	config2.fontFilePath = FONT;
	config2.fontSize = 120;

	auto lbBestscore = Label::createWithTTF(config2, "0");
	_menuResult->addChild(lbBestscore, 1, "lbbestscore");
	lbBestscore->setPosition(txtBestscore->getPosition() + Vec2(190, 0));
	
	auto lbScore = Label::createWithTTF(config2, "0");
	_menuResult->addChild(lbScore, 1, "lbscore");
	lbScore->setPosition(txtScore->getPosition() + Vec2(190, 0));

	auto btRetry = addButton(sprite_bt_retry, sprite_bt_retry_down, sprite_bt_retry_down, [this](Ref* ref){
		auto scale = EaseBackInOut::create(ScaleTo::create(0.5f, 1.5));
		auto fadeOut = FadeOut::create(1.0f);
		auto spawn = Spawn::create(scale, fadeOut, NULL);
		auto seq = Sequence::create(spawn, CallFuncN::create([this](Node* node){
			getChildByName("menucontrol")->setVisible(true);
			_background->reset();
			_layerShadow->setVisible(false);
			initGame();
			node->setVisible(false);
			node->setPosition(VisibleRect::center() + Vec2(0, 1064));
			node->stopAllActions();
			node->setScale(1);
			node->setOpacity(255);
		}), NULL);
		_menuResult->runAction(seq);
	});
	btRetry->setPosition(300, 60);
	auto menu2 = Menu::create(btRetry, NULL);
	menu2->setPosition(0, 0);
	_menuResult->addChild(menu2);
}

void GameScene::initActions()
{
	float s = (_screenHeight);
	auto actionMove = MoveBy::create(_balloonSpeed, Vec2(0, -s));
	_actionMovedown = Sequence::create(actionMove, CallFuncN::create([this](Node* node){
		onLostGame(node);
	}), NULL);
	_actionMovedown->retain();

	auto move = MoveBy::create(_multiballoonSpeed, Vec2(0, -s));
	_acMoveRect = Sequence::create(move, CallFuncN::create([this](Node* node){
		onLostGame(node);
	}), NULL);
	_acMoveRect->retain();
}

bool GameScene::initTouch()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void GameScene::scheduleBalloons()
{
	float timer = TIME_INIT_BALLOON;
	int nz = sizeof(TIME_INIT_BALLOONS) / sizeof(float);
	_idxScheduleMultiballoon = 0;

	for (int i = 0; i < nz; i++)
	{
		timer += TIME_INIT_BALLOONS[i];
		this->scheduleOnce([this](float dt){
			this->spawnBalloon();
		}, timer, StringUtils::format("keyz%02d", i));
	}
}

void GameScene::scheduleMultiballoons()
{
	_timeScheduleMultiballoon = TIME_INIT_MULTIBALLOON;
	_nScheduleMultiballoon = sizeof(TIME_INIT_MULTIBALLOONS) / sizeof(float);
	_idxScheduleMultiballoon = 0;

	for (int i = 0; i < _nScheduleMultiballoon; i++)
	{
		_timeScheduleMultiballoon += TIME_INIT_MULTIBALLOONS[i];
		this->scheduleOnce([this](float dt){
			this->spawnMultiballoon();
		}, _timeScheduleMultiballoon, StringUtils::format("key%02d", i));
	}
	//float t = _timeScheduleMultiballoon;
}

void GameScene::pausedGame()
{
	for (auto n : this->getChildren())
	{
		if (n->getTag() == 99)
		{
			n->pause();
		}
	}
	this->pause();
	_layerShadow->setVisible(true);

	_lbPause->setVisible(true);
	_lbPause->setOpacity(255);
	_lbPause->setScale(3.0f);
	_lbPause->setTextColor(Color4B::YELLOW);
	auto scale = EaseBackInOut::create(ScaleTo::create(0.9f, 1.0));
	_lbPause->runAction(scale);
}

void GameScene::resumeGame()
{
	_lbPause->setVisible(false);
	_go->setVisible(true);
	_go->setOpacity(255);
	_go->setScale(3.0f);
	auto scale = EaseBackInOut::create(ScaleTo::create(0.5f, 1.0));
	auto delay = DelayTime::create(0.5f);
	auto scaleOut = EaseOut::create(ScaleTo::create(0.5f, 3.0f), 2);
	auto fadeOut = FadeOut::create(0.5);
	auto spawn = Spawn::create(scaleOut, fadeOut, NULL);
	auto seq = Sequence::create(scale, delay, spawn, CallFunc::create([this](){
		for (auto n : this->getChildren())
		{
			if (n->getTag() == 99)
			{
				n->resume();
			}
		}
		this->resume();
		_layerShadow->setVisible(false);
	}), NULL);
	_go->runAction(seq);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	if (_gameMode == GameMode::Playing || _gameMode == GameMode::Tutorial)
	{
		_gesture->reset();
		_gesture->addPoint(_screenHeight - touch->getLocation().x, touch->getLocation().y);
		_gestureDraw->drawPoint(touch->getLocation(), 2, Color4F::ORANGE);
	}
	
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	if (_gameMode == GameMode::Playing || _gameMode == GameMode::Tutorial)
	{
		_gesture->addPoint(_screenHeight - touch->getLocation().x, touch->getLocation().y);
		_gestureDraw->drawSegment(touch->getPreviousLocation(), touch->getLocation(), 5, Color4F::ORANGE);
		//if (_isNeedParticle)
		//{
		//	_isNeedParticle = false;
		//	this->addNewParticle(touch->getLocation());
		//	this->scheduleOnce([this](float deltaTime){
		//		_isNeedParticle = true;
		//	}, 0.005f, "key");
		//}
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	_gesture->addPoint(_screenHeight - touch->getLocation().x, touch->getLocation().y);
	_endPointCache = touch->getLocation();

	double score = 0.0;
	bool isNeedMoveCharacter = false;
	ofxGesture* match = _dollar.match(_gesture, &score);

	if (_gameMode == GameMode::Tutorial)
	{
		if (match != NULL && score > 0.7f)
		{
			if (match->id == _idBalloonTutorial)
			{
				if (_idBalloonTutorial == 0)
				{
					_gameMode = GameMode::Init;
					_drawer->stopAllActions();
					_drawer->setVisible(false);
					_b1->destroy();
					this->scheduleOnce([this](float dt){
						_b2 = Balloon::create(this, kBalloon, 1);
						_b2->setPosition(VisibleRect::leftTop() + Vec2(ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2(3 * ENEMY_WIDTH * 2, 0));
						_b2->setActive(true);
						_layerShadow->setVisible(false);
						//remove _b1
	
						auto moveto = MoveBy::create(1.5f, Vec2(0, -_screenHeight / 2.0f));
						auto seq = Sequence::create(moveto, CallFunc::create([this](){
							_layerShadow->setVisible(true);
							_gameMode = GameMode::Tutorial;
							_idBalloonTutorial = 1;
							_drawer->setVisible(true);

							auto ani = Animation::create();
							for (int i = 0; i < 15; i++)
							{
								auto name = StringUtils::format("tutorial_up_arrow-%d.png", i);
								auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
								ani->addSpriteFrame(frame);
							}
							ani->setDelayPerUnit(0.15f);
							ani->setRestoreOriginalFrame(true);
							auto _animationEnemy = RepeatForever::create(Animate::create(ani));
							_drawer->runAction(_animationEnemy);

						}), NULL);
						_b2->doAction(seq);
					}, 0.3f, "tutorial2");
				}
				else if (_idBalloonTutorial == 1)
				{
					_b2->destroy();
					_drawer->stopAllActions();
					_drawer->setVisible(false);

					this->scheduleOnce([this](float dt){
						_ready->setVisible(true);
						_ready->setScale(3.0f);
						auto scale = EaseInOut::create(ScaleTo::create(0.5f, 1.0), 3);
						auto delay = DelayTime::create(0.8f);
						auto scaleOut = EaseOut::create(ScaleTo::create(0.8f, 3.0f), 2);
						auto fadeOut = FadeOut::create(0.5);
						auto spawn = Spawn::create(scaleOut, fadeOut, NULL);
						auto seq = Sequence::create(scale, delay, spawn, CallFunc::create([this](){
							_go->setVisible(true);
							_go->setOpacity(255);
							_go->setScale(3.0f);
							auto scale = EaseBackInOut::create(ScaleTo::create(0.5f, 1.0));
							auto delay = DelayTime::create(0.5f);
							auto scaleOut = EaseOut::create(ScaleTo::create(0.5f, 3.0f), 2);
							auto fadeOut = FadeOut::create(0.5);
							auto spawn = Spawn::create(scaleOut, fadeOut, NULL);
							auto seq = Sequence::create(scale, delay, spawn, CallFunc::create([this](){
								doReleaseAllTutorial();
								//_layerShadow->setVisible(false);
							}), NULL);
							_go->runAction(seq);
						}), NULL);
						_ready->runAction(seq);
					}, 0.8f, "tutorial3");

				}
			}
		}
		_gesture->reset();
		_gestureDraw->clear();
		return;
	}

	if (match != NULL) {
		if (score > 0.7f && _isNext)
		{
			_isNext = false;
			for (auto balloon : _balloons)
			{
				if (balloon->isActive() && balloon->_id == match->id)
				{
					if (balloon->getPosition().y < _screenHeight)
					{
						_balloonsRemove.push_back(balloon);
						_score++;
						_lb->setString(StringUtils::format("%d", _score));
						isNeedMoveCharacter = true;
					}
				}
			}

			for (auto m : _multiballoons)
			{
				int z = m->isMatchGesture(match->id);
				if (m->isActive() && z > -1)
				{
					if (m->getPosition().y < _screenHeight)
					{
						Utils::playEffect(sound_stack_balls_explosion);
						m->destroy(z);
						_score++;
						_lb->setString(StringUtils::format("%d", _score));
						isNeedMoveCharacter = true;
						if (std::find(_multiballoonsRemove.begin(), _multiballoonsRemove.end(), m) != _multiballoonsRemove.end())
						{
							_multiballoonsRemove.push_back(m);
						}
					}
				}
			}

			if (_balloonsRemove.size() > 0)
			{
				if (_balloonsRemove.size() > 1)
				{
					Utils::playEffect(sound_combo);
				}
				else
				{
					Utils::playEffect(sound_ball_explosion);
				}
				doRemoveBalloon();
				//this->runAction(ShakeAction::create(0.3f, 6.0f));
			}

			if (_multiballoonsRemove.size() > 0)
			{
				Utils::playEffect(sound_ball_explosion);
				doRemoveMultiballoon();
			}
			else{
				_isNext = true;
			}

			if (isNeedMoveCharacter)
			{
				auto move = MoveTo::create(0.5f, Vec2( clampf(_endPointCache.x, 74, 600), _character->getPositionY()));
				_character->runAction(move);
			}
		}
		else
		{
		}
	}
	else
	{
	}
	_gesture->reset();
	_gestureDraw->clear();
}

void GameScene::update(float deltaTime)
{
	if (_gameMode != GameMode::Playing)
	{
		return;
	}

	//_balloonTimer += deltaTime;
	//if (_balloonTimer > _balloonInterval)
	//{
	//	_balloonTimer -= _balloonInterval;
	//	this->spawnBalloon();
	//	//this->spawnMultiballoon();
	//}

	//_increaseDifficultyTimer += deltaTime;
	//if (_increaseDifficultyTimer > _increaseDifficultyInterval)
	//{
	//	_increaseDifficultyTimer -= _increaseDifficultyInterval;
	//	//this->doIncreaseDifficulty();
	//}
}

void GameScene::removeBalloon(Balloon *balloon)
{
	for (std::vector<Balloon*>::iterator it = _balloons.begin(); it != _balloons.end(); it++)
	{
		if (*it == balloon)
		{
			_balloons.erase(it);
			break;
		}
	}
}

void GameScene::removeMultiballoon(MultiBalloon* a)
{
	for (std::vector<MultiBalloon*>::iterator it = _multiballoons.begin(); it != _multiballoons.end(); it++)
	{
		if (*it == a)
		{
			_multiballoons.erase(it);
			break;
		}
	}

	for (std::vector<MultiBalloon*>::iterator it = _multiballoonsRemove.begin(); it != _multiballoonsRemove.end(); it++)
	{
		if (*it == a)
		{
			_multiballoonsRemove.erase(it);
			break;
		}
	}
}

void GameScene::spawnBalloon()
{
	auto b = _balloonManager->getBalloon();
	_balloons.push_back(b);
	b->doAction(_actionMovedown->clone());
}

void GameScene::spawnMultiballoon()
{
	auto b = _multiballoonManager->getObjectNext();
	if (b == NULL)
	{
		return;
	}
	_multiballoons.push_back(b);
	b->doAction(_acMoveRect->clone());
}

void GameScene::doRemoveBalloon()
{
	for (auto b : _balloonsRemove)
	{
		b->destroy();
		removeBalloon(b);
	}
	_balloonsRemove.clear();
	_isNext = true;
}

void GameScene::doRemoveMultiballoon()
{
	for (auto a : _multiballoonsRemove)
	{
		if (a->isNeedRemove())
		{
			removeMultiballoon(a);
		}
	}
	//_multiballoonsRemove.clear();
	_isNext = true;
}

void GameScene::addNewParticle(Vec2 position)
{
	auto p = _particles.at(_idxParticle);
	this->addChild(p, kControl);
	p->setPosition(position);

	_idxParticle = (_idxParticle++) % MAX_PARTICLES;
}

void GameScene::doIncreaseDifficulty()
{
	if (_balloonInterval > 1.2f)
	{
		_balloonInterval -= (increaseDifficulty - 0.05f);
	}

	if (_balloonSpeed > 1.5f)
	{
		_balloonSpeed = _balloonSpeed * 0.9f;
	}

	CC_SAFE_RELEASE_NULL(_actionMovedown);

	this->initActions();
}

void GameScene::onLostGame(Node* node)
{
	_gameMode = GameMode::Init;
	this->unscheduleUpdate();
	this->unscheduleAllCallbacks();
	Utils::playEffect(sound_lost);
	_lostEffect->doActionTarget(node);
	this->runAction(ShakeAction::create(1.5f, 3.0f));
	for (auto b : _balloons)
	{
		b->setActive(false);
	}
	_balloons.clear();
	_balloonsRemove.clear();

	for (auto b : _multiballoons)
	{
		b->setActive(false);
	}
	_multiballoons.clear();
	_multiballoonsRemove.clear();

	_background->reset();
	this->scheduleOnce([this](float dt){
		_lostEffect->setVisible(false);
		getChildByName("menucontrol")->setVisible(false);
		showRetryMenu();
	}, 1.5f, "lostgamek");
}

void GameScene::showRetryMenu()
{
	_layerShadow->setVisible(true);

	auto moveTo = MoveBy::create(0.8f, Vec2(0, -1000));
	_menuResult->setVisible(true);
	_menuResult->runAction(moveTo);

	auto lbscore = (Label*)_menuResult->getChildByName("lbscore");
	auto lbbestscore = (Label*)_menuResult->getChildByName("lbbestscore");

	int bscore = UserDefault::getInstance()->getIntegerForKey(KEY_BEST_SCORE, 0);
	if (_score > bscore)//new best score
	{
		UserDefault::getInstance()->setIntegerForKey(KEY_BEST_SCORE, _score);
		lbscore->setString(StringUtils::toString(_score));
		lbbestscore->setString(StringUtils::toString(_score));
		//tao 1 so action
	}
	else
	{
		lbscore->setString(StringUtils::toString(_score));
		lbbestscore->setString(StringUtils::toString(bscore));
	}
}

void GameScene::doReleaseAllTutorial()
{
	_layerShadow->setVisible(false);
	_drawer->removeFromParentAndCleanup(true);
	_b1->_node->removeFromParentAndCleanup(true);
	_b2->_node->removeFromParentAndCleanup(true);
	_idBalloonTutorial = -1;
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(TUTORIAL_ATLAS);

	//UserDefault::getInstance()->setBoolForKey(KEY_IS_TUTORIAL, true);
	getChildByName("menucontrol")->setVisible(true);

	this->initGame();
}

MenuItemSprite* GameScene::addButton(std::string up, std::string dn, std::string dis, ccMenuCallback callback)
{
	Sprite* itemUp, *itemDn, *itemDis;

	itemUp = Sprite::createWithSpriteFrameName(up);
	itemDn = Sprite::createWithSpriteFrameName(dn);
	itemDis = Sprite::createWithSpriteFrameName(dis);

	return MenuItemSprite::create(itemUp, itemDn, itemDis, callback);
}

GameScene::~GameScene()
{
	if (UserDefault::getInstance()->getBoolForKey(KEY_IS_TUTORIAL, false))
	{
		CC_SAFE_DELETE(_gesture);
		CC_SAFE_RELEASE_NULL(_actionMovedown);
		CC_SAFE_DELETE(_balloonManager);
		CC_SAFE_DELETE(_multiballoonManager);
	}
}
