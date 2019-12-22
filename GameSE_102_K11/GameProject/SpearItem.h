#ifndef _SPEARITEM_H
#define _SPEARITEM_H

#include "Entity.h"

class SpearItem : public Entity
{
private:

public:
	SpearItem(float x, float y);
	~SpearItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif