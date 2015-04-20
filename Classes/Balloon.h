#ifndef _BALLOON_H_
#define _BALLOON_H_

#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;

class Balloon
{
public:
	static Balloon* create(Layer* layer, int zOrder, int id);
	virtual bool init();
	~Balloon();

	int _id;

	inline void doAction(Action* action)
	{
		_node->runAction(action);
	}

	inline void setActive(bool isActive)
	{
		_isActive = isActive;
		_node->setVisible(_isActive);
		_node->stopAllActions();
		_ball->stopAllActions();
		_enemy->stopAllActions();
		_ball->setVisible(true);
		_ball->setSpriteFrame(BALLOONS[_id]);
		_ball->setColor(Color3B::WHITE);
		_enemy->setScale(1.0f);
		_enemy->setOpacity(255);

		if (isActive)
		{
			_enemy->stopAllActions();
			_enemy->runAction(_animationEnemy);
			//_enemy->setSpriteFrame(enemy_sprite);
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
	
	void destroy();
	Node* _node;
protected:

	Layer* _layer;
	bool _isActive;

	Sprite* _ball;
	Sprite* _enemy;

	Action* _animationEnemy;
	Action*	_destroyBall;
	Action*	_destroyEnemy;
};


#endif /* _BALLOON_H_ */