#ifndef _BALLITEM_H
#define _BALLITEM_H

#include "Entity.h"
#include "Camera.h"
#include "MapGame.h"


class BallItem : public Entity
{
private:

public:
	BallItem(float x, float y);
	~BallItem();

	//void update(float frameTime, Camera *camera);
};

#endif