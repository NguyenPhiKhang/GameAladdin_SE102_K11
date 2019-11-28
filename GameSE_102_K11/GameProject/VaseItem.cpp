#include "VaseItem.h"

VaseItem::VaseItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::VASE;
}

VaseItem::~VaseItem()
{
}
