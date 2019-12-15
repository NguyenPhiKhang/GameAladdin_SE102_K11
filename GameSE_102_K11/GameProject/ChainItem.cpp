#include "ChainItem.h"

ChainItem::ChainItem(float x, float y, int width, int height)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = width;
	spriteData.height = height;
	type = eType::CHAINS;
	kind = eKind::ITEM;
}

ChainItem::~ChainItem()
{
}

void ChainItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = spriteData.x;
	top = spriteData.y + 96;
	right = left + spriteData.width;
	bottom = top + spriteData.height - 156;
}
