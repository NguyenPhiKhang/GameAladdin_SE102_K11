#ifndef _ALADDIN_H
#define _ALADDIN_H

#include "Entity.h"
#include "Camera.h"
#include "MapGame.h"

namespace aladdinNS {
	const int ALADDIN_SPEED = 150;
}

class Aladdin: public Entity
{
private:

public:
	Aladdin(float x, float y);
	~Aladdin();

	void update(float frameTime, Camera* camera);
};

#endif