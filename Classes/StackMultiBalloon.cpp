#include "StackMultiBalloon.h"
#include "Config.h"

StackMultiBalloon* StackMultiBalloon::create(Layer* layer, int zOrder, int n)
{
	auto obj = new StackMultiBalloon();
	obj->_layer = layer;
	obj->_node = Node::create();
	obj->_node->setTag(99);
	layer->addChild(obj->_node, zOrder);
	int idx = RandomHelper::random_int(0, TOTAL_SQUARE - 1);
	int step = RandomHelper::random_int(1, TOTAL_SQUARE - 3);
	for (int i = 0; i < n; i++)
	{
		obj->_ids.push_back(StackBalloonsIndex[idx]);
		idx = (idx + step) % TOTAL_SQUARE;
	}
	obj->init();
	return obj;
}

void StackMultiBalloon::init()
{
	this->initSprites();
	this->initActions();
}

void StackMultiBalloon::initSprites()
{
	_enemy = Sprite::createWithSpriteFrameName("item_chest_hit_01.png");
	_node->addChild(_enemy);

	for (int i = 0, imax = _ids.size(); i < imax; i++)
	{
		auto idx = _ids.at(i);
		idx = getRealIdx(idx);
		auto sprite = Sprite::createWithSpriteFrameName(Square_Sprite[idx]);
		sprite->setPosition(0, -78.0f);
		_node->addChild(sprite);
		_balloons.push_back(sprite);
	}
	_isActive = false;
	_node->setVisible(_isActive);
	_node->setUserData(this);

	this->initValues();
}

void StackMultiBalloon::initValues()
{
	_idxCurrentBalloon = _ids.size() - 1;
	_enemy->setSpriteFrame("item_chest_hit_01.png");
}

void StackMultiBalloon::initActions()
{
	auto ani = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		auto name = StringUtils::format("item_chest_hit_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		ani->addSpriteFrame(frame);
	}
	ani->setDelayPerUnit(0.1f);
	ani->setRestoreOriginalFrame(true);
	_animationEnemy = RepeatForever::create(Animate::create(ani));
	_animationEnemy->retain();

	auto fadeout = EaseIn::create(FadeOut::create(0.35f), 2);
	auto zoom = EaseOut::create(ScaleTo::create(0.35f, 2.5f), 2);
	auto spawn = Spawn::createWithTwoActions(fadeout, zoom);
	_destroyBall = Sequence::create(spawn, CallFuncN::create([this](Node* node){
		if (_idxCurrentBalloon == 0)
		{
			_enemy->stopAllActions();
			_enemy->runAction(_destroyEnemy);
		}
		else
		{
			_idxCurrentBalloon--;
			node->setVisible(false);
		}
	}), NULL);
	_destroyBall->retain();

	auto fadeout2 = FadeOut::create(0.3f);
	auto scale = ScaleTo::create(0.3f, 1.5f);
	auto animationEnemyDestroy = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		auto name = StringUtils::format("enemy_destroy_2_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animationEnemyDestroy->addSpriteFrame(frame);
	}
	animationEnemyDestroy->setDelayPerUnit(.1f);
	animationEnemyDestroy->setRestoreOriginalFrame(true);
	auto animateEnemyDestroy = Animate::create(animationEnemyDestroy);

	auto spawn2 = Spawn::create(animateEnemyDestroy, fadeout2, scale, NULL);

	_destroyEnemy = Sequence::create(spawn2, CallFunc::create([this](){
		this->setActive(false);
		//for (auto b : _balloons)
		//{
		//	b->setVisible(true);
		//	b->setScale(1);
		//	b->setOpacity(255);
		//}
		//_enemy->setScale(1.0f);
		//_enemy->setOpacity(255);
		//this->initValues();
	}), NULL);
	_destroyEnemy->retain();
}

int StackMultiBalloon::isMatchGesture(int id)
{
	if (_ids.at(_idxCurrentBalloon) == id)
	{
		return _ids.at(_idxCurrentBalloon);
	}
	return -1;
}

void StackMultiBalloon::destroy(int id)
{
	if (_idxCurrentBalloon >= 0)
	{
		_balloons.at(_idxCurrentBalloon)->runAction(_destroyBall->clone());
	}
}

StackMultiBalloon::~StackMultiBalloon()
{
	CC_SAFE_RELEASE_NULL(_animate);
}

int StackMultiBalloon::getRealIdx(int idx)
{
	switch (idx)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 3:
		return 2;
	case 5:
		return 3;
	case 7:
		return 4;
	default:
		return 0;
	}
}

void StackMultiBalloon::setActive(bool isActive)
{
	MultiBalloon::setActive(isActive);
	if (!isActive)
	{
		for (auto b : _balloons)
		{
			b->setVisible(true);
			b->setScale(1);
			b->setOpacity(255);
		}
		_enemy->setScale(1.0f);
		_enemy->setOpacity(255);
		this->initValues();
	}
}
