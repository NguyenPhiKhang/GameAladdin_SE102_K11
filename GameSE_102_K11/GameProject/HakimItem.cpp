#include "HakimItem.h"

HakimItem::HakimItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::HAKIM;
}

HakimItem::~HakimItem()
{
}