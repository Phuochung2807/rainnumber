#ifndef _MULTI_BALLOON_MANAGER_H
#define _MULTI_BALLOON_MANAGER_H

#include "MultiBalloon.h"
#include "cocos2d.h"
USING_NS_CC;

class MultiballoonManager
{
public:
	MultiballoonManager(Layer *layer, int zOrder);

	void reset();
	MultiBalloon* getObjectNext();

	virtual ~MultiballoonManager();
protected:
	std::vector<MultiBalloon*> _objs;
	std::vector<Vec2> _initPositions;
	int _idxNext;
};

#endif /* _MULTI_BALLOON_MANAGER_H */