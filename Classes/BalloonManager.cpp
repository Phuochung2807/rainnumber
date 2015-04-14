#include "BalloonManager.h"
#include "Balloon.h"
#include "Config.h"
#include "VisibleRect.h"
BalloonManager::BalloonManager(cocos2d::Layer* layer, int zOrder)
{
	for (int i = 0; i < TOTAL_BALLOONS; i++)
	{
		for (int j = 0; j < MAX_BALLOON_PER_TYPE; j++)
		{
			auto balloon = Balloon::create(layer, zOrder, i);
			_balloons.push_back(balloon);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		Vec2 pos = (VisibleRect::leftTop() + Vec2(ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2(i * ENEMY_WIDTH * 2, 0));
		postionInit.push_back(pos);
		Vec2 pos2 = (VisibleRect::leftTop() + Vec2(ENEMY_WIDTH + ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2(i * ENEMY_WIDTH * 2, 0));
		postionInit.push_back(pos2);
	}

	this->reset();
}

void BalloonManager::reset()
{
	_lastIdxInitPos = -1;
	_lastIdxBalloonType = -1;
}

Balloon* BalloonManager::getBalloon()
{
	int idxNext = (_lastIdxInitPos + RandomHelper::random_int(2, 3)) % TOTAL_INIT_POSITION;
	_lastIdxInitPos = idxNext;
	int idxNextType = (_lastIdxBalloonType + RandomHelper::random_int(1, 2)) % TOTAL_BALLOONS;
	_lastIdxBalloonType = idxNextType;
	Vec2 pos = postionInit.at(idxNext);

	int idx = MAX_BALLOON_PER_TYPE * TIMELINE_BALLOON[idxNextType];
	while (_balloons.at(idx)->isActive() && idx < _balloons.size())
	{
		idx++;
	}

	auto balloon = _balloons.at(idx);
	balloon->setPosition(pos);
	balloon->setActive(true);

	return balloon;
}

BalloonManager::~BalloonManager()
{
	for (auto balloon : _balloons)
	{
		CC_SAFE_DELETE(balloon);
	}
}
