#ifndef _GROUND_H
#define _GROUND_H

#include "Entity.h"

class Ground: public Entity
{
private:
public:
	Ground(float x, float y);
	~Ground();

	void getBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif // !_GROUND_H