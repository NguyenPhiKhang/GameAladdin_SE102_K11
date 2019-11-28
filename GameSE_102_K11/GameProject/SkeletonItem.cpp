#include "SkeletonItem.h"

SkeletonItem::SkeletonItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::SKELETON;
}

SkeletonItem::~SkeletonItem()
{
}
