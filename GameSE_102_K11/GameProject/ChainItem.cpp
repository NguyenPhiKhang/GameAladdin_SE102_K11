#include "ChainItem.h"

ChainItem::ChainItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::CHAINS;
}

ChainItem::~ChainItem()
{
}
