#include "GemItem.h"

GemItem::GemItem(float x, float y) :Entity()
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::GEMS;
	kind = eKind::ITEM;
	isSound = false;
}

GemItem::~GemItem()
{
}

void GemItem::update(std::vector<Entity*>* listObj, float frameTime)
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

void GemItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 6;
		top = spriteData.y + 6;
		right = left + 17;
		bottom = top + 16;
	}
}

void GemItem::setState(int state)
{
	Entity::setState(state);
	if (state == EXPLOSIVE_ITEM)
	{
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 11);
		setCurrentFrame(0);
		frameDelay = 0.05f;
		Audio::getInstance()->Play(MUSIC_GEM_COLLECT);
	}
}
