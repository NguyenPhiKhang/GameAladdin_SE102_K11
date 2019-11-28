#include "ExitItem.h"

ExitItem::ExitItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::EXITS;
}

ExitItem::~ExitItem()
{
}
