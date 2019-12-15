#include "Iron_StepItem.h"

Iron_StepItem::Iron_StepItem(float x, float y, int w, int h)
{
	spriteData.x = x;
	spriteData.y = y;
	spriteData.width = w;
	spriteData.height = h;
	type = eType::IRON_STEP;
	kind = eKind::FLOOR;
}

Iron_StepItem::~Iron_StepItem()
{
}
