#include "FireIdle.h"

FireIdle::FireIdle(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::FIRE_IDLE;
	setTextureManager(TextureManager::getIntance()->getTexture(eType::FIRE_IDLE));
	setFrames(0, 4);
	setCurrentFrame(0);
	setFrameDelay(0.1f);
}

FireIdle::~FireIdle()
{
}
