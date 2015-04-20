#include "MultiballoonManager.h"
#include "RectMultiBalloon.h"
#include "StackMultiBalloon.h"
#include "Config.h"
#include "VisibleRect.h"

MultiballoonManager::MultiballoonManager(Layer *layer, int zOrder)
{
	for (int i = 0; i < TOTAL_TIMELINE_MULTIBALLOONS - 1; i++)
	{
		if (TIMELINE_MULTIBALLOONS[i] == 0)//stack
		{
			auto m = StackMultiBalloon::create(layer, zOrder, TIMELINE_TYPE_MULTIBALLOONS[i]);
			_objs.push_back(m);
			Vec2 pos = (VisibleRect::leftTop() + Vec2(ENEMY_WIDTH + RandomHelper::random_int(0, 1) * ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2((i % 4) * ENEMY_WIDTH * 2, 0));
			_initPositions.push_back(pos);
		}	
		else//rect
		{
			auto m = RectMultiBalloon::create(layer, zOrder, TIMELINE_TYPE_MULTIBALLOONS[i]);
			int tmp = i % 4;
			if (TIMELINE_TYPE_MULTIBALLOONS[i] >= 3)
			{
				if (tmp <= 1)
				{
					tmp = RandomHelper::random_int(2, 3);
				}
			}
			Vec2 pos = (VisibleRect::leftTop() + Vec2(ENEMY_WIDTH + RandomHelper::random_int(0, 1) * ENEMY_WIDTH, ENEMY_HEIGHT) + Vec2((tmp) * ENEMY_WIDTH * 2, 0));
			_objs.push_back(m);
			_initPositions.push_back(pos);
		}
	}
}

void MultiballoonManager::reset()
{
	for (auto m : _objs)
	{
		m->setActive(false);
	}
	_idxNext = 0;
}

MultiBalloon* MultiballoonManager::getObjectNext()
{
	auto obj = _objs.at(_idxNext);
	if (obj->isActive())
	{
		return NULL;
	}
	obj->setPosition(_initPositions.at(_idxNext));
	obj->setActive(true);
	_idxNext = (_idxNext + 1) % _objs.size();
	return obj;
}

MultiballoonManager::~MultiballoonManager()
{

}
