#include "ButtressItem.h"

ButtressItem::ButtressItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BUTTRESS;
	kind = eKind::ENEMY;
}

ButtressItem::~ButtressItem()
{
}

void ButtressItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
}

void ButtressItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (currentFrame == 12 || currentFrame == 16)
	{
		left = spriteData.x + 7;
		top = spriteData.y + 29;
		right = left + 26;
		bottom = top + 27;
		return;
	}
	if (currentFrame >= 13 && currentFrame <= 15)
	{
		left = spriteData.x + 7;
		top = spriteData.y + 25;
		right = left + 27;
		bottom = top + 27;
		return;
	}
	if (currentFrame == 10 || currentFrame == 11 || currentFrame == 17 || currentFrame == 18)
	{
		left = spriteData.x + 6;
		top = spriteData.y + 32;
		right = left + 25;
		bottom = top + 25;
		return;
	}
}
