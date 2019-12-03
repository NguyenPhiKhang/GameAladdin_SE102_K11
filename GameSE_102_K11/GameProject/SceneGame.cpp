#include "SceneGame.h"

SceneGame::SceneGame()
{
	camera = new Camera();
	tileMap = new MapGame();
	grid = new Grid();

	//ground = new Ground(0.0f, 1097.0f);

	//	Postition test
	//	Aladdin			 ||	Camera
	//	1347.0f, 715.0f	 ||	1287.0f, 655.0f
	//	84.0f, 996.0f	 ||	24.0f, 894.0f
	//	2085.0f, 108.0f	 ||	2025.0f, 48.0f
	aladdin = new Aladdin(camera, tileMap);
	pillar_snake = new Image();
	front_hurdle = new Image();

	posX = 0;
	posY = 1134;
	verticalX = MapNS::MAX_SPEED_KEYB;
	verticalY = MapNS::MAX_SPEED_KEYB;

	oldXCam = 0.0f;
	oldYCam = 0.0f;
}

SceneGame::~SceneGame()
{
	safeDelete(camera);
	safeDelete(tileMap);
	safeDelete(grid);
	safeDelete(pillar_snake);
	safeDelete(front_hurdle);
}


void SceneGame::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	LoadMap(eType::MAP_SULTAN);

	aladdin->setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
	aladdin->setFrameDelay(0.12f);
	aladdin->setFrames(0, 38);
	aladdin->setCurrentFrame(0);
	aladdin->setState(eType::ALADDIN_IDLE);
}

void SceneGame::update(float frameTime)
{
	grid->GetListEntity(listEntity, camera);

	aladdin->update(frameTime, this, &listEntity);

	if (mapCurrent == MAP_SULTAN) // Xét camera font background hurdle
	{
		float deltaCamX = camera->getXCamera() - oldXCam;
		float deltaCamY = camera->getYCamera() - oldYCam;
		front_hurdle->setX(front_hurdle->getX() - ((deltaCamX == 0.0f) ? 0.0f :
			(deltaCamX > 0.0f)? (deltaCamX + 2.5f) : (deltaCamX - 2.5f)));
		front_hurdle->setY(front_hurdle->getY() - ((deltaCamY == 0.0f) ? 0.0f :
			(deltaCamY > 0.0f) ? (deltaCamY + 0.3f) : (deltaCamY - 0.3f)));

		if (front_hurdle->getX() > 0.0f)
			front_hurdle->setX(front_hurdle->getX() - 512.0f);
		if (front_hurdle->getX() < -512.0f)
			front_hurdle->setX(front_hurdle->getX() + 512.0f);
		if (front_hurdle->getY() > 0.0f)
			front_hurdle->setY(front_hurdle->getY() - 256.0f);
		if (front_hurdle->getY() < -256.0f)
			front_hurdle->setY(front_hurdle->getY() + 256.0f);

		oldXCam = camera->getXCamera();
		oldYCam = camera->getYCamera();
	}
	else
	{
		if (mapCurrent == MAP_JAFAR) // Xét camera font background pillar snake
		{
			float deltaCamX = camera->getXCamera() - oldXCam;
			pillar_snake->setX(pillar_snake->getX() - ((deltaCamX == 0.0f) ? 0.0f :
				(deltaCamX > 0.0f) ? (deltaCamX + 0.5f) : (deltaCamX - 0.5f)));

			if (pillar_snake->getX() > 0)
				pillar_snake->setX(pillar_snake->getX() - 128);
			if (pillar_snake->getX() < -128)
				pillar_snake->setX(pillar_snake->getX() + 128);
			oldXCam = camera->getXCamera();
		}
	}

	for (int i = 0; i < listEntity.size(); i++)
	{
		listEntity[i]->update(frameTime);
	}
}

void SceneGame::render()
{
	Graphics::getInstance()->spriteBegin();

	if (mapCurrent == eType::MAP_JAFAR)
	{
		float pillarX = pillar_snake->getX();
		float pillarY = pillar_snake->getY();

		for (int col = 0; col < GAME_WIDTH + 128; col += 128)
		{
			pillar_snake->setX(pillarX + col);
			pillar_snake->setViewport(D3DXVECTOR2(pillar_snake->getX(), pillar_snake->getY()));
			pillar_snake->draw();           // draw the ocean
		}

		pillar_snake->setXY(pillarX, pillarY);
	}

	tileMap->Render(camera);

	listColumns.clear();
	for (auto& ent : listEntity)
	{
		if (mapCurrent == eType::MAP_SULTAN)
		{
			if (ent->getID() >= 172 && ent->getID() <= 175)
			{
				listColumns.push_back(ent);
			}
			else
			{
				ent->setViewport(camera->CameraTransform(ent->getX(), ent->getY()));
				ent->draw();

				if (isDebugRenderBBox)
					ent->RenderBoundingBox(camera);
			}
		}
		else if (mapCurrent == eType::MAP_JAFAR)
		{
			ent->setViewport(camera->CameraTransform(ent->getX(), ent->getY()));
			ent->draw();

			if (isDebugRenderBBox)
				ent->RenderBoundingBox(camera);
		}
	}

	aladdin->setViewport(camera->CameraTransform(aladdin->getX(), aladdin->getY()));
	aladdin->draw();
	if (isDebugRenderBBox)
		aladdin->RenderBoundingBox(camera);

	if (mapCurrent == eType::MAP_SULTAN)
	{
		for (auto& column : listColumns)
		{
			column->setViewport(camera->CameraTransform(column->getX(), column->getY()));
			column->draw();
		}
		float hurdleX = front_hurdle->getX();
		float hurdleY = front_hurdle->getY();

		for (int row = 0; row < GAME_HEIGHT + 256; row += 256)
		{
			for (int col = 0; col < GAME_WIDTH + 512; col += 512)
			{
				front_hurdle->setX(hurdleX + col);
				front_hurdle->setY(hurdleY + row);
				front_hurdle->setViewport(D3DXVECTOR2(front_hurdle->getX(), front_hurdle->getY()));
				front_hurdle->draw();           // draw the ocean
			}
		}
		front_hurdle->setXY(hurdleX, hurdleY);
	}

	Graphics::getInstance()->spriteEnd();
}

void SceneGame::LoadMap(eType type)
{
	mapCurrent = type;
	switch (type)
	{
	case MAP_SULTAN:
		camera->setPositionCam(24.0f, 894.0f);
		oldXCam = camera->getXCamera();
		oldYCam = camera->getYCamera();

		grid->SetFile(OBJECT_GRID_MAP_SULTAN);
		grid->ReloadGrid();

		front_hurdle->setTextureManager(TextureManager::getIntance()->getTexture(eType::MAP_SULTAN_FRONT_BG));

		aladdin->setXY(84.0f, 956.0f);

		tileMap->LoadMap(eType::MAP_SULTAN);
		break;
	case MAP_JAFAR:
		camera->setPositionCam(0.0f, 192.0f);
		oldXCam = camera->getXCamera();

		grid->SetFile(OBJECT_GRID_MAP_JAFAR);
		grid->ReloadGrid();

		pillar_snake->setTextureManager(TextureManager::getIntance()->getTexture(eType::MAP_JAFAR_BACKGROUND));

		aladdin->setXY(8.0f, 250.0f);

		tileMap->LoadMap(eType::MAP_JAFAR);
		break;
	}

	ResetObjectMap();
}

void SceneGame::ResetObjectMap()
{
	listEntity.clear();
	listColumns.clear();

	isDebugRenderBBox = false;
}

void SceneGame::setMapCurrent(eType type)
{
	if (mapCurrent != type)
		LoadMap(type);
}

