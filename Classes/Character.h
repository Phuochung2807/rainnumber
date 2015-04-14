#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
USING_NS_CC;

class Character : public Sprite
{
public:
	static Character* create();
	virtual bool init();

	virtual ~Character();
	void createAnimation();
protected:

};

#endif /* _CHARACTER_H_ */