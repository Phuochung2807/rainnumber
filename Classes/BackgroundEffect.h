#ifndef _BACKGROUND_EFFECT_H_
#define _BACKGROUND_EFFECT_H_

#include "cocos2d.h"
USING_NS_CC;

class BackgroundEffect : public Node
{
public:
	CREATE_FUNC(BackgroundEffect);
	virtual bool init();

	void update(float dt);
	void reset();
	void start();
protected:
	float _speed;
	float _initSpeedLine;
	float _initSpeedSky;

	cocos2d::Vector<Sprite*> _skys;
	cocos2d::Vector<Sprite*> _lines;
};

#endif /* _BACKGROUND_EFFECT_H_ */