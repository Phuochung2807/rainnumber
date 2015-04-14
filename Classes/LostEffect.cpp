#include "LostEffect.h"
#include "Config.h"
#include "ShakeAction.h"

bool LostEffect::init()
{
	if (!Sprite::initWithSpriteFrameName("die01.png"))
	{
		return false;
	}
	this->setAnchorPoint(Vec2(0.5f, 0));
	this->createActions();
	this->setOpacity(250);
	setVisible(false);
	return true;
}

void LostEffect::createActions()
{
	auto ani = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		auto name = StringUtils::format("die%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		ani->addSpriteFrame(frame);
	}
	ani->setDelayPerUnit(0.1f);
	ani->setRestoreOriginalFrame(true);
	_animation = RepeatForever::create(Animate::create(ani));
	this->runAction(_animation);

	auto shake = ShakeAction::create(2.0f, 2, 3);

	//auto spawn = Spawn::create(animation, NULL);

	_shake = Sequence::create(shake, CallFunc::create(endActionCallback), NULL);
	_shake->retain();
}

void LostEffect::doActionTarget(Node* target)
{
	Vec2 pos = target->getPosition();
	pos.y -= (BACKGROUND_OFFSET - 10);
	this->setPosition(pos);
	this->setVisible(true);
	this->runAction(_shake);
}
