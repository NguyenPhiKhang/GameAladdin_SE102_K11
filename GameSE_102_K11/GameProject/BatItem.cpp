#include "BatItem.h"

BatItem::BatItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BATS;
}

BatItem::~BatItem()
{
}
