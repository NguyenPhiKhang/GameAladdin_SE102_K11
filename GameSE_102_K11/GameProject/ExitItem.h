#ifndef _EXITITEM_H
#define _EXITITEM_H

#include "Entity.h"

class ExitItem : public Entity
{
private:

public:
	ExitItem(float x, float y);
	~ExitItem();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif