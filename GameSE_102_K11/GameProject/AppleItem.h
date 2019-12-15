#ifndef _APPLEITEM_H
#define _APPLEITEM_H

#include "Entity.h"

class AppleItem: public Entity
{
private:

public:
	AppleItem(float x, float y);
	~AppleItem();
	void update(float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif