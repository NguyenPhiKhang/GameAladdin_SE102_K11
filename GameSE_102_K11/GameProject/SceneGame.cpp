#include "SceneGame.h"

SceneGame::SceneGame()
{
	camera = new Camera();
	tileMap = new MapGame();
	grid = new Grid();

	aladdin = new Aladdin(82.0f, 1018.0f);

	posX = 0;
	posY = 1134;
	verticalX = MapNS::MAX_SPEED_KEYB;
	verticalY = MapNS::MAX_SPEED_KEYB;
}

SceneGame::~SceneGame()
{
	safeDelete(camera);
	safeDelete(tileMap);
	safeDelete(grid);
}

void SceneGame::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	camera->setPositionCam(0.0f, 894.0f);

	grid->SetFile(APPLEITEM_POSITION);
	grid->ReloadGrid();

	aladdin->setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
	aladdin->setFrameDelay(0.12f);
	aladdin->setFrames(0, 38);
	aladdin->setCurrentFrame(0);
	aladdin->setState(eType::ALADDIN_IDLE);

	tileMap->LoadMap(eType::MAP_SULTAN);
}

void SceneGame::update(float frameTime)
{
	grid->GetListEntity(listEntity, camera);

	aladdin->update(frameTime, camera);


	/*if (Input::getInstance()->isKeyDown(ALADDIN_UP_KEY))
	{
		verticalY = -MapNS::MAX_SPEED_KEYB;
		posY += verticalY * frameTime;
		if (posY > MapNS::POSY_KEYB&& posY < MapNS::MAP_HEIGHT_1 - MapNS::POSY_KEYB)
		{
			camera->setPositionCam(camera->getXCamera(), posY - MapNS::POSY_KEYB);
		}
		if (posY < MapNS::POSY_KEYB) { camera->setPositionCam(camera->getXCamera(), 0); }
		if (posY < 0)
			posY = 0;
	}
	if (Input::getInstance()->isKeyDown(ALADDIN_DOWN_KEY))
	{
		verticalY = MapNS::MAX_SPEED_KEYB;
		posY += verticalY * frameTime;
		if (posY > MapNS::POSY_KEYB&& posY < MapNS::MAP_HEIGHT_1 - MapNS::POSY_KEYB)
		{
			camera->setPositionCam(camera->getXCamera(), camera->getYCamera() + verticalY * frameTime);
		}
		if (posY > MapNS::MAP_HEIGHT_1 - MapNS::POSY_KEYB) { camera->setPositionCam(camera->getXCamera(), MapNS::MAP_HEIGHT_1 - 2 * MapNS::POSY_KEYB); }
		if (posY > MapNS::MAP_HEIGHT_1)
			posY = MapNS::MAP_HEIGHT_1;
	}
	if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY))
	{
		verticalX = -MapNS::MAX_SPEED_KEYB;
		posX += verticalX * frameTime;
		if (posX > MapNS::POSX_KEYB&& posX < MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB)
		{
			camera->setPositionCam(posX - MapNS::POSX_KEYB, camera->getYCamera());
		}
		if (posX < MapNS::POSX_KEYB) { camera->setPositionCam(0, camera->getYCamera()); }
		if (posX < 0)
			posX = 0;
	}
	if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
	{
		verticalX = MapNS::MAX_SPEED_KEYB;
		posX += verticalX * frameTime;
		if (posX > MapNS::POSX_KEYB&& posX < MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB)
		{
			camera->setPositionCam(posX - MapNS::POSX_KEYB, camera->getYCamera());
		}
		if (posX > MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB) { camera->setPositionCam(MapNS::MAP_WIDTH_1 - 2 * MapNS::POSX_KEYB, camera->getYCamera()); }
		if (posX > MapNS::MAP_WIDTH_1)
			posX = MapNS::MAP_WIDTH_1;
	}*/
}

void SceneGame::render()
{
	Graphics::getInstance()->spriteBegin();

	tileMap->Render(camera);

	for (auto& ent : listEntity)
	{
		ent->setViewport(camera->CameraTransform(ent->getX(), ent->getY()));
		ent->draw();
	}

	aladdin->setViewport(camera->CameraTransform(aladdin->getX(), aladdin->getY()));
	aladdin->draw();

	Graphics::getInstance()->spriteEnd();
}
