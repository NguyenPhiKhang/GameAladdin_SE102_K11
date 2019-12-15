#include "ExitItem.h"

ExitItem::ExitItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::EXITS;
	kind = eKind::WALL;
}

ExitItem::~ExitItem()
{
}

void ExitItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = spriteData.x + 64;
	top = spriteData.y + 48;
	right = left + 14;
	bottom = top + 96;
}