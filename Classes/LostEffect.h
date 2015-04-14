#ifndef _LOSTEFFECT_H_
#define _LOSTEFFECT_H_

#include "cocos2d.h"
USING_NS_CC;

typedef std::function<void()> endActionShakeCallback;

class LostEffect : public Sprite
{
public:
	CREATE_FUNC(LostEffect);
	virtual bool init();
	void doActionTarget(Node* target);

protected:
	Action* _shake;
	Action* _animation;
	CC_SYNTHESIZE(endActionShakeCallback, endActionCallback, EndActionCallback);
	void createActions();
};

#endif /* _LOSTEFFECT_H_ */