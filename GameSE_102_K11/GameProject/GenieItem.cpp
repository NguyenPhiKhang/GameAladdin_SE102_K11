#include "GenieItem.h"

GenieItem::GenieItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::GENIES;
	kind = eKind::ITEM;
	state = GENIES;
	countUpDown = 0;
	overLimit = false;
	velocity.y = -15;
	oldY = y;
}

GenieItem::~GenieItem()
{
}

void GenieItem::update(float frameTime)
{
	Entity::update(frameTime);
	if (state == GENIES)
	{
		spriteData.y += dy;
		if (spriteData.y<oldY - 8 || spriteData.y > oldY)
		{
			overLimit = true;
			if(spriteData.y < oldY - 8)
				spriteData.y = oldY - 8;
			else {
				spriteData.y = oldY;
			}

		}
		if (overLimit)
		{
			countUpDown++;
			overLimit = false;
			velocity.y = -velocity.y;
		}
		if (countUpDown > 6&&currentFrame==0)
		{
			countUpDown = 0;
			setCurrentFrame(1);
			setFrames(1, 3);
			velocity.y = 0.0f;
			frameDelay = 0.3f;
		}
		if (currentFrame == 3)
		{
			setFrames(0, 0);
			setCurrentFrame(0);
			velocity.y = 15;
		}
	}
	if (state == EXPLOSIVE_GENIE)
	{
		if (currentFrame == 14)
			visible = false;
	}
}

void GenieItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health > 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}
}

void GenieItem::setState(int state)
{
	Entity::setState(state);
	if (state == EXPLOSIVE_GENIE)
	{
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 14);
		setCurrentFrame(0);
		frameDelay = 0.05f;
	}
}
