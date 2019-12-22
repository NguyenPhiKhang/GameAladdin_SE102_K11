#include "Heart_BalloonItem.h"

Heart_BalloonItem::Heart_BalloonItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::HEART_BALLOON;
	kind = eKind::ITEM;
}

Heart_BalloonItem::~Heart_BalloonItem()
{
}

void Heart_BalloonItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (health == 0.0f)
	{
		if (currentFrame > 5 && currentFrame < 9)
			frameDelay = 0.15f;
		else frameDelay = 0.05f;
		if (currentFrame == 11)
			visible = false;
	}
}

void Heart_BalloonItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}
}

void Heart_BalloonItem::setState(int state)
{
	Entity::setState(state);
	if (state == EXPLOSIVE_ITEM)
	{
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 11);
		 setCurrentFrame(0);
		frameDelay = 0.05f;
		Audio::getInstance()->Play(MUSIC_HEART);
	}
}
