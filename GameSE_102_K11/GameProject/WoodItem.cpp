#include "WoodItem.h"

WoodItem::WoodItem(float x, float y, int w, int h)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = w;
	spriteData.height = h;
	type = eType::WOOD;
	kind = eKind::FLOOR;
}

WoodItem::~WoodItem()
{
}

//void WoodItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = spriteData.x;
//	top = spriteData.y;
//	right = left + spriteData.width;
//	bottom = top + 5;
//}
