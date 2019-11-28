#include "Column_OutItem.h"

Column_OutItem::Column_OutItem(float x, float y, int type)
{
	spriteData.x = x;
	spriteData.y = y;
	this->type = type;
}

Column_OutItem::~Column_OutItem()
{
}
