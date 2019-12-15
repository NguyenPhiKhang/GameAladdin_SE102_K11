#include "VaseItem.h"

VaseItem::VaseItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::VASE;
	kind = eKind::ITEM;
}

VaseItem::~VaseItem()
{
}

void VaseItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health > 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}
}

void VaseItem::setState(int state)
{
	health = 0.0f;
	setFrames(1, 8);
	setCurrentFrame(1);
}

void VaseItem::update(float frameTime)
{
	Entity::update(frameTime);
	if (currentFrame == 8)
		setFrames(0, 0);
}
