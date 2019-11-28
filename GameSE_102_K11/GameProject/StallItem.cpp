#include "StallItem.h"

StallItem::StallItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::STALL;
}

StallItem::~StallItem()
{
}
