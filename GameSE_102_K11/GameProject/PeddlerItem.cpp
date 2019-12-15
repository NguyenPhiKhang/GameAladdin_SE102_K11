#include "PeddlerItem.h"

PeddlerItem::PeddlerItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::PEDDLER;
	kind = eKind::ITEM;
}

PeddlerItem::~PeddlerItem()
{
}
