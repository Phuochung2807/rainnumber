#include "MultiBalloon.h"
#include "Config.h"

void MultiBalloon::init()
{
	_enemy = Sprite::createWithSpriteFrameName(enemy_sprite);
	_enemy->setPositionY(ENEMY_POSITION_OFFSET_Y);
	_node->addChild(_enemy);

	for (int i = 0, imax = _ids.size(); i < imax; i++)
	{
		auto sprite = Sprite::createWithSpriteFrameName(BALLOONS[_ids.at(i)]);
		_balloons.push_back(sprite);
		_node->addChild(sprite);
	}

	_isActive = false;
	_node->setVisible(_isActive);
	_node->setUserData(this);
	_node->setTag(99);
}

bool MultiBalloon::isNeedRemove()
{
	for (auto sprite : _balloons)
	{
		if (sprite->isVisible())
		{
			return false;
		}
	}
	return true;
}

int MultiBalloon::isMatchGesture(int id)
{
	for (int i = 0, imax = _ids.size(); i < imax; i++)
	{
		if (_balloons.at(i)->isVisible() && _ids.at(i) == id)
		{
			return i;
		}
	}
	return -1;
}


void MultiBalloon::destroy(int idx)
{
	auto sprite = _balloons.at(idx);
	if (sprite->isVisible())
	{
		sprite->setColor(BALLOON_COLORS[_ids.at(idx)]);
		sprite->runAction(_destroyBall->clone());
	}
}

MultiBalloon::~MultiBalloon()
{
	CC_SAFE_RELEASE_NULL(_destroyBall);
	CC_SAFE_RELEASE_NULL(_destroyEnemy);
	CC_SAFE_RELEASE_NULL(_animationEnemy);
}
