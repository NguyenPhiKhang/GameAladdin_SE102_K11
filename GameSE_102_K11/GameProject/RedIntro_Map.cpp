<<<<<<< Updated upstream
#include "RedIntro_Map.h"

RedIntro_Map::RedIntro_Map()
{
	imgIntro = new Image();

	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);

	isFinished = false;
}
RedIntro_Map::~RedIntro_Map()
{
	safeDelete(imgIntro);
}

void RedIntro_Map::LoadIntroMap(int state)
{
	imgIntro->setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
	imgIntro->setFrames(0, 3);
	imgIntro->setCurrentFrame(0);
	imgIntro->setFrameDelay(0.15f);
	QueryPerformanceCounter(&timeStart);
}

void RedIntro_Map::update(float frameTime)
{
	imgIntro->update(frameTime);
	QueryPerformanceCounter(&timeEnd);
	if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / timerFreq.QuadPart) > 10.0f||Input::getInstance()->isKeyDown(VK_RETURN))
	{
		isFinished = true;
		Input::getInstance()->keyUp(13);
	}
}

void RedIntro_Map::render()
{
	imgIntro->setViewport(D3DXVECTOR2(imgIntro->getX(), imgIntro->getY()));
	imgIntro->draw();
=======
#include "RedIntro_Map.h"

RedIntro_Map::RedIntro_Map()
{
	imgIntro = new Image();

	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);

	isFinished = false;
}
RedIntro_Map::~RedIntro_Map()
{
	safeDelete(imgIntro);
}

void RedIntro_Map::LoadIntroMap(int state)
{
	imgIntro->setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
	imgIntro->setFrames(0, 3);
	imgIntro->setCurrentFrame(0);
	imgIntro->setFrameDelay(0.15f);
	QueryPerformanceCounter(&timeStart);
}

void RedIntro_Map::update(float frameTime)
{
	imgIntro->update(frameTime);
	QueryPerformanceCounter(&timeEnd);
	if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / timerFreq.QuadPart) > 10.0f||Input::getInstance()->isKeyDown(VK_RETURN))
	{
		isFinished = true;
		Input::getInstance()->keyUp(13);
	}
}

void RedIntro_Map::render()
{
	imgIntro->setViewport(D3DXVECTOR2(imgIntro->getX(), imgIntro->getY()));
	imgIntro->draw();
>>>>>>> Stashed changes
}