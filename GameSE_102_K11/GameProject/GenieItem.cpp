#include "GenieItem.h"

GenieItem::GenieItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::GENIES;
}

GenieItem::~GenieItem()
{
}
