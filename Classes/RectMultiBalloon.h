#ifndef _RECT_MULTIBALLOON_H_
#define _RECT_MULTIBALLOON_H_

#include "MultiBalloon.h"

class RectMultiBalloon : public MultiBalloon
{
public:
	static RectMultiBalloon* create(Layer* layer, int zOrder, int n);
	virtual void init();
	virtual void setActive(bool isActive) final;
protected:
	void initPositions();
	void initActions();
	void initLines();
	std::vector<Sprite*> _lines;
};

#endif /* _RECT_MULTIBALLOON_H_ */