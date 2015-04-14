#include "Balloon.h"
#include "Config.h"

Balloon* Balloon::create(Layer* layer, int zOrder, int id)
{
	auto balloon = new Balloon();
	balloon->_layer = layer;
	balloon->_node = Node::create();
	balloon->_node->setTag(99);
	layer->addChild(balloon->_node, zOrder);
	balloon->_id = id;
	if (balloon && balloon->init())
	{
		return balloon;
	}
	CC_SAFE_DELETE(balloon);
	return NULL;
}

bool Balloon::init()
{
	_ball = Sprite::createWithSpriteFrameName(BALLOONS[_id]);
	_enemy = Sprite::createWithSpriteFrameName(enemy_sprite);

	_enemy->setPositionY(ENEMY_POSITION_OFFSET_Y);
	_node->addChild(_enemy);
	_node->addChild(_ball);

	_isActive = false;
	_node->setVisible(_isActive);

	_node->setUserData(this);

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

	auto changecolor = TintTo::create(0.1f, BALLOON_COLORS[_id]);

	auto spawn2 = Spawn::createWithTwoActions(animate, changecolor);
	_destroyBall = Sequence::create(spawn2, CallFunc::create([this](){
		_ball->setVisible(false);
		_enemy->runAction(_destroyEnemy);
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
		_ball->setVisible(true);
		_ball->setColor(Color3B::WHITE);
		_enemy->setScale(1.0f);
		_enemy->setOpacity(255);
	}), NULL);
	_destroyEnemy->retain();

	return true;
}

void Balloon::destroy()
{
	_isActive = false;
	_node->stopAllActions();
	_ball->stopAllActions();
	_enemy->stopAllActions();
	_ball->runAction(_destroyBall);
}

Balloon::~Balloon()
{
	CC_SAFE_RELEASE_NULL(_destroyBall);
	CC_SAFE_RELEASE_NULL(_destroyEnemy);
	CC_SAFE_RELEASE_NULL(_animationEnemy);
}
