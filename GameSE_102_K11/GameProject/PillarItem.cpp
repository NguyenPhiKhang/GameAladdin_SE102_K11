#include "PillarItem.h"

PillarItem::PillarItem(float x, float y, int width, int height)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = width;
	spriteData.height = height;
	type = eType::PILLAR;
}

PillarItem::~PillarItem()
{
}
