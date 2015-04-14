#ifndef _STACK_MULTIBALLOON_H_
#define _STACK_MULTIBALLOON_H_

#include "MultiBalloon.h"

class StackMultiBalloon : public MultiBalloon
{
public:
	static StackMultiBalloon* create(Layer* layer, int zOrder, int n);
	virtual void init() final;
	virtual int isMatchGesture(int id) final;
	virtual void destroy(int id) final;
	virtual void setActive(bool isActive) final;
	virtual ~StackMultiBalloon();
protected:
	void initSprites();
	void initActions();
	void initValues();
	int getRealIdx(int idx);
	int _idxCurrentBalloon;

	Action* _animate;
};

#endif /* _STACK_MULTIBALLOON_H_ */