#include "PeddlerItem.h"

PeddlerItem::PeddlerItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::PEDDLER;
}

PeddlerItem::~PeddlerItem()
{
}
