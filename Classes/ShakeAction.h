#ifndef _SHAKE_ACTION_H_
#define _SHAKE_ACTION_H_

#include "cocos2d.h"

USING_NS_CC;

class ShakeAction : public ActionInterval
{
public:
	ShakeAction();
	static ShakeAction* create(float d, float strength);
	static ShakeAction* create(float d, float strength_x, float strength_y);
	bool initWithDuration(float d, float strength_x, float strength_y);

	virtual ShakeAction* clone() const override;
	virtual ShakeAction* reverse(void) const override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;
	virtual void stop(void);

protected:
	float _initial_x, _initial_y;
	float _strength_x, _strength_y;
};

#endif /* _SHAKE_ACTION_H_ */