#ifndef _FIRE_RUN_H
#define _FIRE_RUN_H

#include "Entity.h"
#include "Audio.h"

class FireRun: public Entity
{
private:
public:
	FireRun(float x, float y);
	~FireRun();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif