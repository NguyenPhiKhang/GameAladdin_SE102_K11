#include "Ground.h"

Ground::Ground(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::GROUND;
}

Ground::~Ground()
{
}

void Ground::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = spriteData.x;
	top = spriteData.y;
	right = left + 2270;
	bottom = top + 10;
}
