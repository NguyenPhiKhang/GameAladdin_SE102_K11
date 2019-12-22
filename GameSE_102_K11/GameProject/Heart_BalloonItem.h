#ifndef _HEART_BALLOONITEM_H
#define _HEART_BALLOONITEM_H

#include "Entity.h"
#include "Audio.h"

class Heart_BalloonItem : public Entity
{
private:

public:
	Heart_BalloonItem(float x, float y);
	~Heart_BalloonItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif