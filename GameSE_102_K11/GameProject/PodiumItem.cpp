#include "PodiumItem.h"

PodiumItem::PodiumItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::PODIUM;
	kind = eKind::FLOOR;
	isSound = false;
}

PodiumItem::~PodiumItem()
{
}

void PodiumItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(frameTime);
	if (currentFrame == 0 || currentFrame == 4)
	{
		frameDelay = 2.0f;
		isSound = false;
	}
	else if((currentFrame == 1||currentFrame == 5)&&!isSound)
	{
		Audio::getInstance()->Play(MUSIC_PODIUM);
		isSound = true;
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
	if (currentFrame >= 2&& currentFrame <=6)
	{
		left = spriteData.x + 7;
		top = spriteData.y + 1;
		right = left + 28;
		bottom = top + 12;
	}
}

