#include "ButtressItem.h"

ButtressItem::ButtressItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BUTTRESS;
}

ButtressItem::~ButtressItem()
{
}
