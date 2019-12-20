#include "BatItem.h"

BatItem::BatItem(float x, float y, Aladdin* aladdin)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BATS;
	kind = eKind::ENEMY;
	firstX = spriteData.x;
	firstY = spriteData.y;
	this->aladdin = aladdin;
	limitLeft = (int)(firstX - 50);
	limitRight = (int)(firstX + 100);
	velocity.x = -50.0f;
	velocity.y = 120.0f;
	deltaV.y = -5;
	total = 0.0f;
	isFlying = false;
	isRotating = false;
	A = 80.0f;
	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);
}

BatItem::~BatItem()
{
}

void BatItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (health == 0.0f && state == EXPLOSIVE_ENEMY)
	{
		if (currentFrame == 9)
			visible = false;
	}
	else {
		float lA, tA, bA, rA;
		aladdin->getBoundingBox(lA, tA, rA, bA);

		if (!isFlying)
		{
			if (rA > limitLeft&& lA < limitRight)
			{
				QueryPerformanceCounter(&timeEnd);
				if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / timerFreq.QuadPart) > 0.5f)
				{
					isFlying = true;
					setFrames(0, 10);
					setCurrentFrame(1);
					setFrameDelay(0.15f);
					velocity.y = 120.0f;
					isRotating = true;
					total = 0.0f;
				}
			}
		}
		else {
			if (currentFrame < 4 && isRotating)
			{
				frameDelay = 0.2f;
			}
			else {
				isRotating = false;
				frameDelay = 0.1f;
				total += frameTime;
				spriteData.x = (float)(A * cos((PI)*total + (PI / 2)) + firstX);
				spriteData.y += dy;
				if (currentFrame == 0)
					currentFrame = 3;
				if (spriteData.x > firstX)
				{
					velocity.y = -120;
				}
				if (spriteData.y < firstY)
				{
					spriteData.x = firstX;
					spriteData.y = firstY;
					isFlying = false;
					setFrames(0, 0);
					setCurrentFrame(0);
					QueryPerformanceCounter(&timeStart);
				}
			}
		}
	}

}

void BatItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 15;
		right = left + 6;                 //width 28,height 49
		top = spriteData.y + 5;
		bottom = top + 16;
	}
}

void BatItem::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case EXPLOSIVE_ENEMY:
	{
		D3DXVECTOR2 centerBat = getCenter();
		setCurrentFrame(0);
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 9);
		frameDelay = 0.08f;
		setXY(centerBat.x - spriteData.width / 2, centerBat.y - spriteData.height / 2 - 5);
		return;
	}
	break;
	}
}
