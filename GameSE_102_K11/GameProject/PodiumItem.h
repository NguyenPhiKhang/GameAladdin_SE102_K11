#ifndef _PODIUMITEM_H
#define _PODIUMITEM_H

#include "Entity.h"

class PodiumItem : public Entity
{
private:

public:
	PodiumItem(float x, float y);
	~PodiumItem();

	void update(float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif