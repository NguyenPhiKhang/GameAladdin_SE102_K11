#include "SceneIntro.h"



SceneIntro::SceneIntro()
{
	Menu = new Image();
	Selector = new Image();

	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);

	velocityY = 50.0f;
}
SceneIntro::~SceneIntro()
{
	safeDelete(Menu);
	safeDelete(Selector);
}

void SceneIntro::initialize()
{
	Menu->setTextureManager(TextureManager::getIntance()->getTexture(eType::MENU));
	Selector->setTextureManager(TextureManager::getIntance()->getTexture(eType::SELECTOR));
	
	Selector->setX(73);
	Selector->setY(125);
}

void SceneIntro::update(float frameTime)
{
	QueryPerformanceCounter(&timeEnd);
	if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / timerFreq.QuadPart) > 0.2f)
	{
		timeStart = timeEnd;
		velocityY = -velocityY;
	}
	else {
		Selector->setX(Selector->getX() + velocityY * frameTime);
	}
	
	if (Input::getInstance()->isKeyDown(VK_UP))
	{
		if (Selector->getY() == 141)
		{
			Selector->setY(125);
		}
    }
	if (Input::getInstance()->isKeyDown(VK_DOWN))
	{
		if (Selector->getY()==125)
		{
			Selector->setY(141);
		}
	}

}

void SceneIntro::render()
{
	Menu->setViewport((D3DXVECTOR2(Menu->getX(), Menu->getY())));
	Selector->setViewport((D3DXVECTOR2(Selector->getX(), Selector->getY())));
	Menu->draw();
	Selector->draw();
}