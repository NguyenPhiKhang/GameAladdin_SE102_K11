#include "SpearItem.h"

SpearItem::SpearItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::SPEAR;
}

SpearItem::~SpearItem()
{
}
