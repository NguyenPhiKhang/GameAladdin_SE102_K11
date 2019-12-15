#include "Column_OutItem.h"

Column_OutItem::Column_OutItem(float x, float y, int type)
{
	spriteData.x = x;
	spriteData.y = y;
	this->type = type;
	kind = eKind::COLUMN_OUT;
}

Column_OutItem::~Column_OutItem()
{
}
