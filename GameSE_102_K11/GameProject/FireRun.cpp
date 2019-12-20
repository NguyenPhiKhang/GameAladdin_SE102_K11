#include "FireRun.h"

FireRun::FireRun(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::FIRE_RUN;
}

FireRun::~FireRun()
{
}

void FireRun::update(std::vector<Entity*>* listObj, float frameTime)
{
}

void FireRun::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
