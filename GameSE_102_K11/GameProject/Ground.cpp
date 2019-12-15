#include "Ground.h"

Ground::Ground(float x, float y, int width, int height)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = width;
	spriteData.height = height;
	type = eType::GROUND;
	kind = eKind::FLOOR;
}

Ground::~Ground()
{
}

//void Ground::getBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = spriteData.x;
//	top = spriteData.y;
//	right = left + 2270;
//	bottom = top + 10;
//}
