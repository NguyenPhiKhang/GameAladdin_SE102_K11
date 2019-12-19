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
	setFrames(1, 9);
	setCurrentFrame(1);
}

void VaseItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (currentFrame == 9)
		setFrames(0, 0);
}
