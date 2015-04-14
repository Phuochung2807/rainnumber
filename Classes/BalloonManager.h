#ifndef _BALLOON_MANAGER_H_
#define _BALLOON_MANAGER_H_

#include "Balloon.h"

class BalloonManager
{
public:
	BalloonManager(cocos2d::Layer* layer, int zOrder);
	virtual ~BalloonManager();
	void reset();
	Balloon* getBalloon();
protected:
	std::vector<Balloon*> _balloons;
	std::vector<Vec2> postionInit;
	int _lastIdxInitPos;
	int _lastIdxBalloonType;
};
#endif /* _BALLOON_MANAGER_H_ */