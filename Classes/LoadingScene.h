#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"
#include "2d\CCProgressTimer.h"
USING_NS_CC;

class LoadingScene : public LayerColor
{
public:
	static Scene* createScene();
	static LoadingScene* create();

	virtual bool init();
	void update(float dt);

protected:
	void loadResource(int idx);
	void switchScene();

	ProgressTimer* _progressTimer;
	int _idxLoaded;
	int _nNeedLoad;
	float _per;
};

#endif /* _LOADING_SCENE_H_ */