#include "NahbiItem.h"

NahbiItem::NahbiItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::NAHBI;
	kind = eKind::ENEMY;
}

NahbiItem::~NahbiItem()
{
}
