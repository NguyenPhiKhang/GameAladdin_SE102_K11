#ifndef _GENIEITEM_H
#define _GENIEITEM_H

#include "Entity.h"

class GenieItem : public Entity
{
private:
	int countUpDown;
	bool overLimit;
	float oldY;
public:
	GenieItem(float x, float y);
	~GenieItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif