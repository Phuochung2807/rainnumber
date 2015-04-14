#include "RectMultiBalloon.h"
#include "MultiBalloon.h"
#include "Config.h"

RectMultiBalloon* RectMultiBalloon::create(Layer* layer, int zOrder, int n)
{
	auto obj = new RectMultiBalloon();
	obj->_layer = layer;
	obj->_node = Node::create();
	obj->_node->setTag(99);
	layer->addChild(obj->_node, zOrder);

	int idx = (n - 2) % TOTAL_MULTIBALLOON;
	int key = RandomHelper::random_int(1, 5);
	for (int i = 0; i < n; i++)
	{
		obj->_ids.push_back(Multi_Balloons[idx][ (key + i) % (n + 2) ]);
	}
	obj->init();
	return obj;
}

void RectMultiBalloon::init()
{
	initLines();
	MultiBalloon::init();
	initPositions();
	initActions();
}

void RectMultiBalloon::initLines()
{
	int idx = _ids.size() - 2;
	for (int i = 0, imax = _ids.size(); i < imax; i++)
	{
		auto sprite = Sprite::createWithSpriteFrameName(LINES[idx][i]);
		_node->addChild(sprite);
		_lines.push_back(sprite);
		sprite->setPosition(Position_Lines[idx][i]);
	}
}

void RectMultiBalloon::initPositions()
{
	int idx = _ids.size() - 2;

	for (int i = 0, imax = _ids.size(); i < imax; i++)
	{
		_balloons.at(i)->setPosition(Position_Multiballoons[idx][i]);
		_balloons.at(i)->setUserData(_lines.at(i));
	}
}

void RectMultiBalloon::initActions()
{
	auto ani = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		auto name = StringUtils::format("enemy_a_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		ani->addSpriteFrame(frame);
	}
	ani->setDelayPerUnit(0.1f);
	ani->setRestoreOriginalFrame(true);
	_animationEnemy = RepeatForever::create(Animate::create(ani));
	_animationEnemy->retain();

	auto animation = Animation::create();
	for (int i = 1; i < 10; i++)
	{
		auto name = StringUtils::format("ge_ballon_pop_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.03f);
	animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(animation);

	_destroyBall = Sequence::create(animate, CallFuncN::create([this](Node* ball){
		ball->setVisible(false);
		auto line = (Sprite*)ball->getUserData();
		line->setVisible(false);
		if (this->isNeedRemove())
		{
			_enemy->stopAllActions();
			_enemy->runAction(_destroyEnemy);
		}

	}), NULL);
	_destroyBall->retain();

	auto fadeout = FadeOut::create(0.4f);
	auto scale = ScaleTo::create(0.4f, 2.0f);
	auto animationEnemyDestroy = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		auto name = StringUtils::format("enemy_destroy_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animationEnemyDestroy->addSpriteFrame(frame);
	}
	animationEnemyDestroy->setDelayPerUnit(0.4f / 4.0f);
	animationEnemyDestroy->setRestoreOriginalFrame(true);
	auto animateEnemyDestroy = Animate::create(animationEnemyDestroy);

	auto spawn = Spawn::create(animateEnemyDestroy, fadeout, scale, NULL);
	_destroyEnemy = Sequence::create(spawn, CallFunc::create([this](){
		this->setActive(false);
		for (auto b : _balloons)
		{
			b->setVisible(true);
		}
		for (auto l : _lines)
		{
			l->setVisible(true);
		}
		_enemy->setScale(1.0f);
		_enemy->setOpacity(255);
		_enemy->setSpriteFrame(enemy_sprite);
	}), NULL);
	_destroyEnemy->retain();
}

void RectMultiBalloon::setActive(bool isActive)
{
	MultiBalloon::setActive(isActive);

	int i = 0;
	for (auto b : _balloons)
	{
		b->setVisible(true);
		b->setSpriteFrame(BALLOONS[_ids.at(i)]);
		i++;
	}
	for (auto l : _lines)
	{
		l->setVisible(true);
	}
	_enemy->setScale(1.0f);
	_enemy->setOpacity(255);
	_enemy->setSpriteFrame(enemy_sprite);
}

