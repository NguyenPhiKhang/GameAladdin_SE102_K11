#include "SceneIntro.h"



SceneIntro::SceneIntro()
{
	Menu = new Image();
	Selector = new Image();

	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);

	velocityY = 50.0f;
	selected = 0;
	isMoveMap = false;
	isMember = false;
	isMenu = true;
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
	
	Selector->setX(77);
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
	
	if (isMenu)
	{
		if (Input::getInstance()->isKeyDown(VK_UP))
		{
			if (Selector->getY() == 141)
			{
				Selector->setY(125);
				selected = 0;
			}
		}
		if (Input::getInstance()->isKeyDown(VK_DOWN))
		{
			if (Selector->getY() == 125)
			{
				Selector->setY(141);
				selected = 1;
			}
		}
		if (Input::getInstance()->isKeyDown(VK_RETURN) && selected == 0)
		{
			isMoveMap = true;
			Input::getInstance()->keyUp(13);
		}
		if (Input::getInstance()->isKeyDown(VK_RETURN) && selected == 1)
		{
			Menu->setTextureManager(TextureManager::getIntance()->getTexture(eType::MEMBER));
			Selector->setXY(112.0f, 181.0f);
			isMenu = false;
			isMember = true;
			selected = 2;
			Input::getInstance()->keyUp(13);
		}
	}
	else {
		if (isMember)
		{
			if (Input::getInstance()->isKeyDown(VK_RETURN) && selected == 2)
			{
				isMenu = true;
				isMember = false;
				Menu->setTextureManager(TextureManager::getIntance()->getTexture(eType::MENU));
				selected = 0;
				Selector->setX(73);
				Selector->setY(125);
				Input::getInstance()->keyUp(13);
			}
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