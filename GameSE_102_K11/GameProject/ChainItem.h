#ifndef _CHAINITEM_H
#define _CHAINITEM_H

#include "Entity.h"

class ChainItem : public Entity
{
private:

public:
	ChainItem(float x, float y, int width, int height);
	~ChainItem();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif