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
	aladdin = new Aladdin(84.0f, 956.0f);

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

	camera->setPositionCam(24.0f, 894.0f);

	grid->SetFile(OBJECT_MAP1_POSITION);
	grid->ReloadGrid();

	aladdin->setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
	aladdin->setFrameDelay(0.12f);
	aladdin->setFrames(0, 38);
	aladdin->setCurrentFrame(0);
	aladdin->setState(eType::ALADDIN_IDLE);

	//ground->setTextureManager(TextureManager::getIntance()->getTexture(eType::BBOX));

	tileMap->LoadMap(eType::MAP_SULTAN);
}

void SceneGame::update(float frameTime)
{
	grid->GetListEntity(listEntity, camera);

	aladdin->update(frameTime, camera, this, &listEntity);

	for (int i = 0; i < listEntity.size(); i++)
	{
		listEntity[i]->update(frameTime);
	}
}

void SceneGame::render()
{
	Graphics::getInstance()->spriteBegin();

	tileMap->Render(camera);

	listColumns.clear();
	for (auto& ent : listEntity)
	{
		if (ent->getID() == 172 || ent->getID() == 173 || ent->getID() == 174 || ent->getID() == 175)
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

	aladdin->setViewport(camera->CameraTransform(aladdin->getX(), aladdin->getY()));
	aladdin->draw();
	if (isDebugRenderBBox)
		aladdin->RenderBoundingBox(camera);

	for (auto& column : listColumns)
	{
		column->setViewport(camera->CameraTransform(column->getX(), column->getY()));
		column->draw();
	}

	Graphics::getInstance()->spriteEnd();
}
