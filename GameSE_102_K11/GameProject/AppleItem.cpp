#include "AppleItem.h"

AppleItem::AppleItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::APPLES;
}

AppleItem::~AppleItem()
{
}
