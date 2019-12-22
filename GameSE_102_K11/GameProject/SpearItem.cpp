#include "SpearItem.h"

SpearItem::SpearItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::SPEAR;
	kind = eKind::ENEMY;
}

SpearItem::~SpearItem()
{
}

void SpearItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (currentFrame == 0)
		frameDelay = 3.5f;
	else if (currentFrame == 4)
		frameDelay = 2.2f;
	else frameDelay = 0.08f;
}

void SpearItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (currentFrame == 3 || currentFrame == 5)
	{
		left = spriteData.x + 23;
		top = spriteData.y + 9;
		right = left + 10;
		bottom = top + 4;
	}
	if (currentFrame == 4)
	{
		left = spriteData.x + 23;
		top = spriteData.y + 8;
		right = left + 19;
		bottom = top + 7;
	}
}
