#include "BatItem.h"

BatItem::BatItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BATS;
	kind = eKind::ENEMY;
}

BatItem::~BatItem()
{
}
