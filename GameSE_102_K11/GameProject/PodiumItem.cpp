#include "PodiumItem.h"

PodiumItem::PodiumItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::PODIUM;
}

PodiumItem::~PodiumItem()
{
}

void PodiumItem::update(float frameTime)
{
	Entity::update(frameTime);
	if (currentFrame == 0 || currentFrame == 4)
	{
		frameDelay = 3.0f;
	}
	else
	{
		frameDelay = 0.15f;
	}

	/*std::vector<Entity*> listEnt;
	for (auto* x : listEnt)
	{
		if ((x->getID() != 223) || (x->getID() != 225) || (x->getID() != 226) || (x->getID() != 227) || (x->getID() != 230) || (x->getID() != 232) || (x->getID() != 234) || (x->getID() != 236) || (x->getID() != 237) || (x->getID() != 239) || (x->getID() != 241) || (x->getID() != 243) || (x->getID() != 245) || (x->getID() != 247) || (x->getID() != 249) || (x->getID() != 250) || (x->getID() != 252) || (x->getID() != 254) || (x->getID() != 218) || (x->getID() != 220))
		{
			currentFrame = 0;
		}
		else
		{
			currentFrame = 4;
		}
	}*/
}

void PodiumItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (currentFrame == 3 || currentFrame == 4 || currentFrame == 5)
	{
		left = spriteData.x + 7;
		top = spriteData.y + 1;
		right = left + 28;
		bottom = top + 12;
	}
}

