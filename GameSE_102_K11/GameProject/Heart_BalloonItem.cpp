#include "Heart_BalloonItem.h"

Heart_BalloonItem::Heart_BalloonItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::HEART_BALLOON;
}

Heart_BalloonItem::~Heart_BalloonItem()
{
}
