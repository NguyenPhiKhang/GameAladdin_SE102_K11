#ifndef _WOODITEM_H
#define _WOODITEM_H

#include "Entity.h"

class WoodItem : public Entity
{
private:

public:
	WoodItem(float x, float y, int w, int h);
	~WoodItem();
	//void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif