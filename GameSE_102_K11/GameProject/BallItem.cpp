#include "BallItem.h"

BallItem::BallItem(float x, float y):Entity()
{
	spriteData.x = x;
	spriteData.y = y;
}

BallItem::~BallItem()
{
}

//void BallItem::update(float frameTime,  Camera *camera)
//{
//	Entity::update(frameTime);
//	currentFrame = 0;
//	//setFrames(0, 8);
//	//setTextureManager(TextureManager::getIntance()->getTexture(eType::BALLS));
//
//}