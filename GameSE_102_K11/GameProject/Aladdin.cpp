#include "Aladdin.h"


Aladdin::Aladdin(float x, float y):Entity()
{
	spriteData.x = x;
	spriteData.y = y;
}

Aladdin::~Aladdin()
{
}

void Aladdin::update(float frameTime, Camera* camera)
{
	Entity::update(frameTime);
	if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY) || Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
	{
		if (state != ALADDIN_RUN)
		{
			currentFrame = 0;
			setFrames(0, 12);
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_RUN));
			state = ALADDIN_RUN;
			frameDelay = 0.2f;
			spriteData.y += 21;
			if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY))
			{
				setVelocity(D3DXVECTOR2(-aladdinNS::ALADDIN_SPEED, 0.0f));
				spriteData.flipHorizontal = true;
			}
			if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
			{
				setVelocity(D3DXVECTOR2(aladdinNS::ALADDIN_SPEED, 0.0f));
				spriteData.flipHorizontal = false;
			}
		}
	}
	else {
		if (state != ALADDIN_IDLE)
		{
			setFrames(0, 38);
			currentFrame = 0;
			state = ALADDIN_IDLE;
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
			frameDelay = 0.12f;
			spriteData.y -= 21;
		}
	}
	if (state == ALADDIN_IDLE)
	{
		if (currentFrame == 3 || currentFrame == 6 || currentFrame == 21 || currentFrame == 38)
			frameDelay = 0.6f;
		else if (currentFrame == 0)
			frameDelay = 1.0f;
		else frameDelay = 0.12f;
	}
	if (state == ALADDIN_RUN)
	{
		dx = frameTime * velocity.x;
		spriteData.x += dx;
		if (spriteData.x > MapNS::POSX_KEYB && spriteData.x < MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB)
		{
			camera->setPositionCam(spriteData.x - MapNS::POSX_KEYB, camera->getYCamera());
		}
		if (spriteData.x < MapNS::POSX_KEYB) { camera->setPositionCam(0, camera->getYCamera()); }
		if (spriteData.x> MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB) { camera->setPositionCam(MapNS::MAP_WIDTH_1 - 2 * MapNS::POSX_KEYB, camera->getYCamera()); }
		if (spriteData.x> MapNS::MAP_WIDTH_1-spriteData.width)
			spriteData.x= MapNS::MAP_WIDTH_1-spriteData.width;
		if (spriteData.x< 0)
			spriteData.x= 0;
	}
}
