#ifndef _BARRIERITEM_H
#define _BARRIERITEM_H

#include "Entity.h"

class BarrierItem : public Entity
{
private:

public:
	BarrierItem(float x, float y, int width, int height);
	~BarrierItem();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif