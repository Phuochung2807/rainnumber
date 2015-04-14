#include "Character.h"


Character* Character::create()
{
	auto character = new Character();
	if (character && character->init())
	{
		character->autorelease();
		return character;
	}
	CC_SAFE_DELETE(character);
	return NULL;
}

bool Character::init()
{
	if (!Sprite::initWithSpriteFrameName("nv01.png"))
	{
		return false;
	}

	createAnimation();

	return true;
}

void Character::createAnimation()
{
	auto ani = Animation::create();
	for (int i = 1; i < 6; i++)
	{
		auto name = StringUtils::format("nv%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		ani->addSpriteFrame(frame);
	}
	ani->setDelayPerUnit(0.1f);
	ani->setRestoreOriginalFrame(true);
	auto animationEnemy = RepeatForever::create(Animate::create(ani));
	
	this->runAction(animationEnemy);
}

Character::~Character()
{

}
