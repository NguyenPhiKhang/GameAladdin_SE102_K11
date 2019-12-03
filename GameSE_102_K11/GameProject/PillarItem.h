#ifndef _PILLARITEM_H
#define _PILLARITEM_H

#include "Entity.h"

class PillarItem : public Entity
{
private:

public:
	PillarItem(float x, float y, int width, int height);
	~PillarItem();
};

#endif