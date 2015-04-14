#include "BackgroundEffect.h"
#include "Config.h"
#include "VisibleRect.h"

enum kBackgroundEffect
{
	be_background,
	be_sky,
	be_tower,
	be_weapon,
};

bool BackgroundEffect::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto mainbg = Sprite::create(maingame_bg);
	this->addChild(mainbg, be_background);
	mainbg->setAnchorPoint(Vec2(0, 1));
	mainbg->setPosition(0, 0);

	auto sky1 = Sprite::createWithSpriteFrameName(bg_sky_01);
	this->addChild(sky1, be_sky);
	sky1->setPosition(DESIGN_RESOLUTION_WIDTH * 0.4f, -DESIGN_RESOLUTION_HEIGHT * RandomHelper::random_real(0.6f, 0.7f));
	_skys.pushBack(sky1);

	auto sky2 = Sprite::createWithSpriteFrameName(bg_sky_02);
	this->addChild(sky2, be_sky);
	sky2->setPosition(DESIGN_RESOLUTION_WIDTH * 0.7f, -DESIGN_RESOLUTION_HEIGHT * RandomHelper::random_real(0.2f, 0.3f));
	_skys.pushBack(sky2);

	auto line1 = Sprite::createWithSpriteFrameName(bg_line_02);
	this->addChild(line1, be_sky);
	line1->setPosition(DESIGN_RESOLUTION_WIDTH * 0.83f, -DESIGN_RESOLUTION_HEIGHT * 0.8f);
	_lines.pushBack(line1);

	auto line2 = Sprite::createWithSpriteFrameName(bg_line_03);
	this->addChild(line2, be_sky);
	line2->setPosition(DESIGN_RESOLUTION_WIDTH * 0.3f, -DESIGN_RESOLUTION_HEIGHT * 0.55f);
	_lines.pushBack(line2);

	auto line3 = Sprite::createWithSpriteFrameName(bg_line_01);
	this->addChild(line3, be_sky);
	line3->setPosition(DESIGN_RESOLUTION_WIDTH * 0.6f, -DESIGN_RESOLUTION_HEIGHT * 0.1f);
	_lines.pushBack(line3);

	auto lefttower = Sprite::createWithSpriteFrameName(bg_com_tower_left);
	this->addChild(lefttower, be_tower);
	lefttower->setAnchorPoint(Vec2(0, 0));
	lefttower->setPosition(0, -VisibleRect::getVisibleRect().size.height);

	auto righttower = Sprite::createWithSpriteFrameName(bg_com_tower_right);
	this->addChild(righttower, be_tower);
	righttower->setAnchorPoint(Vec2(1, 0));
	righttower->setPosition(VisibleRect::getVisibleRect().size.width, -VisibleRect::getVisibleRect().size.height);

	auto weapon = Sprite::createWithSpriteFrameName(bg_com_weapon);
	this->addChild(weapon, be_weapon);
	weapon->setPosition(VisibleRect::getVisibleRect().size.width / 2.0f, -VisibleRect::getVisibleRect().size.height + BACKGROUND_OFFSET);

	_initSpeedLine = 15.0f;
	_initSpeedSky = 10.0f;

	this->schedule(schedule_selector(BackgroundEffect::update), 0.5f);

	this->reset();
	return true;
}

void BackgroundEffect::update(float dt)
{
	for (auto sky : _skys)
	{
		float x = sky->getPositionX();
		if (x > DESIGN_RESOLUTION_WIDTH + sky->getContentSize().width / 2.0f)
		{
			x -= (DESIGN_RESOLUTION_WIDTH + sky->getContentSize().width);
			sky->setPositionX(x);
		}
		sky->runAction(MoveBy::create(0.5f, Vec2(_initSpeedSky + _speed + RandomHelper::random_int(1, 2), 0)));
	}

	for (auto line : _lines)
	{
		float x = line->getPositionX();
		if (x > DESIGN_RESOLUTION_WIDTH * 2 + line->getContentSize().width / 2.0f)
		{
			x -= (DESIGN_RESOLUTION_WIDTH * 2 + line->getContentSize().width);
			line->setPositionX(x);
		}
		line->runAction(MoveBy::create(0.5f, Vec2(_initSpeedLine + _speed + RandomHelper::random_int(1, 5), 0)));
	}
	_speed += dt * 1.2f;
}

void BackgroundEffect::reset()
{
	this->unscheduleAllSelectors();
	_speed = 5.0f;
}

void BackgroundEffect::start()
{
	this->schedule(schedule_selector(BackgroundEffect::update), 0.5f);
}

