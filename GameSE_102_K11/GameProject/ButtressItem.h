#ifndef _BUTTRESSITEM_H
#define _BUTTRESSITEM_H

#include "Entity.h"

class ButtressItem : public Entity
{
private:

public:
	ButtressItem(float x, float y);
	~ButtressItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif