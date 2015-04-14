#ifndef _MULTI_BALLOON_H
#define _MULTI_BALLOON_H

#include "cocos2d.h"
USING_NS_CC;

class MultiBalloon
{
public:
	virtual void init();

	inline void doAction(Action* action)
	{
		_node->runAction(action);
	}

	virtual void setActive(bool isActive)
	{
		_isActive = isActive;
		_node->setVisible(_isActive);
		_node->stopAllActions();
		for (auto b : _balloons)
		{
			//b->setVisible(true);
			b->setColor(Color3B::WHITE);
		}
		if (isActive)
		{
			_enemy->stopAllActions();
			_enemy->runAction(_animationEnemy);
		}
	}

	inline bool isActive()
	{
		return _isActive;
	}

	inline Vec2 getPosition()
	{
		return _node->getPosition();
	}

	inline void setPosition(Vec2 pos)
	{
		_node->setPosition(pos);
	}

	virtual bool isNeedRemove();
	virtual int isMatchGesture(int id);
	virtual void destroy(int idx);

	virtual ~MultiBalloon();
	Node* _node;
protected:
	bool _isActive;
	Layer* _layer;

	std::vector<int> _ids;
	std::vector<Sprite*> _balloons;
	Sprite*	_enemy;

	Action*	_destroyBall;
	Action*	_destroyEnemy;
	Action* _animationEnemy;
};

#endif /* _MULTI_BALLOON_H */