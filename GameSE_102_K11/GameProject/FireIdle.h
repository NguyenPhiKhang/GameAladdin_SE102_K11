#ifndef _FIRE_IDLE_H
#define _FIRE_IDLE_H

#include "Entity.h"
#include "TextureManager.h"
#include "Audio.h"

class FireIdle: public Entity
{
private:
public:
	FireIdle(float x, float y);
	~FireIdle();
};

#endif