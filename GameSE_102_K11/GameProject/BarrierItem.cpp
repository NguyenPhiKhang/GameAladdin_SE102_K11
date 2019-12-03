#include "BarrierItem.h"

BarrierItem::BarrierItem(float x, float y, int width, int height)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = width;
	spriteData.height = height;
	type = eType::BARRIERS;
}

BarrierItem::~BarrierItem()
{
}

void BarrierItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = spriteData.x;
	top = spriteData.y;
	right = left + spriteData.width;
	bottom = top + spriteData.height -3;
}
