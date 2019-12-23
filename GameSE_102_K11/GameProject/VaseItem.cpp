#include "VaseItem.h"

VaseItem::VaseItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::VASE;
	kind = eKind::ITEM;
	isSound = false;
}

VaseItem::~VaseItem()
{
}

void VaseItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}
}

void VaseItem::setState(int state)
{
	Entity::setState(state);
	if (state == VASE)
	{
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(1, 9);
		setCurrentFrame(1);
		
	}
}

void VaseItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (currentFrame == 9)
	{//setFrames(0, 0);
		frameDelay = (float)INFINITE;
	}
	if (currentFrame == 1)
	{
		Audio::getInstance()->Play(MUSIC_VASE);
	}
}
