#ifndef _VASEITEM_H
#define _VASEITEM_H

#include "Entity.h"

class VaseItem : public Entity
{
private:

public:
	VaseItem(float x, float y);
	~VaseItem();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
	void update(std::vector<Entity*>* listObj, float frameTime);
};

#endif