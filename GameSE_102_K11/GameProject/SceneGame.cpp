#include "SceneGame.h"

SceneGame::SceneGame()
{
	camera = new Camera();
	tileMap = new MapGame();
	grid = new Grid(&listWeaponOfEnemy);

	//ground = new Ground(0.0f, 1097.0f);

	//	Postition test
	//	Aladdin			 ||	Camera
	//	1347.0f, 715.0f	 ||	1287.0f, 655.0f
	//	84.0f, 996.0f	 ||	24.0f, 894.0f
	//	2085.0f, 108.0f	 ||	2025.0f, 48.0f
	aladdin = new Aladdin(camera, tileMap);
	pillar_snake = new Image();
	front_hurdle = new Image();

	hud = new HUD_Info();

	/*posX = 0;
	posY = 1134;
	verticalX = MapNS::MAX_SPEED_KEYB;
	verticalY = MapNS::MAX_SPEED_KEYB;*/

	oldXCam = 0.0f;
	oldYCam = 0.0f;

	allScore = 0;
	allChance = 2;
	allGem = 3;
	//isTouchPodiumFire = false;

	sceneIntro = new SceneIntro();
	mapCurrent = eType::MAP_INTRO;
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

	hud->initialize(FONT_TOTAL_TEXTURE, FONT_SCORE_TEXTURE);

	sceneIntro->initialize();
}

void SceneGame::update(float frameTime)
{
	if (mapCurrent == MAP_INTRO)
	{
		sceneIntro->update(frameTime);
		if (input->isKeyDown(VK_RETURN))
		{
			setMapCurrent(MAP_SULTAN);
		}
	}
	else {
		grid->GetListEntity(listOthers, listEnemies, listItems, camera);

		aladdin->update(frameTime, this, &listOthers);

		if (mapCurrent == MAP_SULTAN) // Xét camera font background hurdle
		{
			float deltaCamX = camera->getXCamera() - oldXCam;
			float deltaCamY = camera->getYCamera() - oldYCam;
			front_hurdle->setX(front_hurdle->getX() - ((deltaCamX == 0.0f) ? 0.0f :
				(deltaCamX > 0.0f) ? (deltaCamX + 2.5f) : (deltaCamX - 2.5f)));
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

		for (auto& ent : listOthers)
		{
			ent->update(&listOthers, frameTime);
		}
		for (auto& item : listItems)
		{
			item->update(&listOthers, frameTime);
		}
		for (auto& enemy : listEnemies)
		{
			enemy->update(&listOthers, frameTime);
		}
		for (int i = 0; i < listWeaponOfEnemy.size(); i++)
		{
			if (listWeaponOfEnemy[i]->getVisible() == true)
			{
				if ((listWeaponOfEnemy[i]->getType() == BONE || listWeaponOfEnemy[i]->getType() == FIRE_RUN || listWeaponOfEnemy[i]->getType() == STAR) && listWeaponOfEnemy[i]->getFinished())
				{
					listWeaponOfEnemy.erase(listWeaponOfEnemy.begin() + i);
					i--;
					continue;
				}
				listWeaponOfEnemy[i]->update(&listOthers, frameTime);
			}
			else {
				listWeaponOfEnemy.erase(listWeaponOfEnemy.begin() + i);
				i--;
			}
		}

		CheckCollision();
		hud->update(frameTime);
		if (mapCurrent == eType::MAP_JAFAR)
		{
			if (fire != NULL)
				fire->update(frameTime);
		}

		if (aladdin->getHealth() <= 10.0f)
		{
			setMapCurrent(mapCurrent, true);
			allChance--;
		}

		if (isKeyUPHealth)
		{
			aladdin->setHealth(100.0f);
		}
		if (isKeyUpApple)
		{
			aladdin->setAppleCollect(aladdin->getAppleCollect() + 5);
		}
	}
}

void SceneGame::render()
{
	Graphics::getInstance()->spriteBegin();

	if (mapCurrent == MAP_INTRO)
	{
		sceneIntro->render();
	}
	else
	{
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
		for (auto& ent : listOthers)
		{
			if (mapCurrent == eType::MAP_SULTAN)
			{
				if (ent->getKind() == eKind::COLUMN_OUT || ent->getType() == eType::EXITS)
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

		for (auto& ent : listItems)
		{
			ent->setViewport(camera->CameraTransform(ent->getX(), ent->getY()));
			ent->draw();

			if (isDebugRenderBBox)
				ent->RenderBoundingBox(camera);
		}

		for (auto& ent : listEnemies)
		{
			ent->setViewport(camera);
			ent->draw();

			if (isDebugRenderBBox)
				ent->RenderBoundingBox(camera);
		}

		for (auto& ent : listWeaponOfEnemy)
		{
			ent->setViewport(camera->CameraTransform(ent->getX(), ent->getY()));
			ent->draw();

			if (isDebugRenderBBox)
				ent->RenderBoundingBox(camera);
		}

		if (mapCurrent == eType::MAP_JAFAR)
		{
			if (fire != NULL)
			{
				fire->setViewport(camera);
				fire->draw();
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

		hud->Render(aladdin->getAppleCollect(), allChance, allGem, allScore, (int)aladdin->getHealth());

		//DebugOut("Y aladdin: %.2f\n", aladdin->getY());
	}

	Graphics::getInstance()->spriteEnd();
}

void SceneGame::LoadMap(eType type, bool isChange)
{
	mapCurrent = type;
	switch (type)
	{
	case MAP_SULTAN:
		camera->setPositionCam(24.0f, 894.0f);
		oldXCam = camera->getXCamera();
		oldYCam = camera->getYCamera();

		grid->SetFile(OBJECT_GRID_MAP_SULTAN);
		grid->ReloadGrid(aladdin);

		front_hurdle->setTextureManager(TextureManager::getIntance()->getTexture(eType::MAP_SULTAN_FRONT_BG));

		aladdin->setXY(84.0f, 956.0f);
		//aladdin->setXY(516.0f, 553.0f);
		//aladdin->setXY(1440.0f, 250.0f);
		//aladdin->setXY(2079.0f, 60.0f);
		//aladdin->setXY(800.0f, 694.0f);

		aladdin->setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
		aladdin->setFrameDelay(0.12f);
		aladdin->setFrames(0, 38);
		aladdin->setCurrentFrame(0);
		aladdin->setState(eType::ALADDIN_IDLE);

		if (isChange)
		{
			aladdin->setHealth(100.0f);
			aladdin->setAppleCollect(50);
			allGem = 3;
			allScore = 0;
		}

		tileMap->LoadMap(eType::MAP_SULTAN);
		if (!audio->isPlaying(eAudio::MUSIC_MAP_SULTAN))
			audio->Play(eAudio::MUSIC_MAP_SULTAN, true);
		if (audio->isPlaying(eAudio::MUSIC_MAP_JAFAR))
			audio->Stop(eAudio::MUSIC_MAP_JAFAR);

		if (fire != NULL) safeDelete(fire);
		break;
	case MAP_JAFAR:
		camera->setPositionCam(0.0f, 192.0f);
		oldXCam = camera->getXCamera();

		grid->SetFile(OBJECT_GRID_MAP_JAFAR);
		grid->ReloadGrid(aladdin);

		pillar_snake->setTextureManager(TextureManager::getIntance()->getTexture(eType::MAP_JAFAR_BACKGROUND));

		aladdin->setXY(8.0f, 200.0f);
		aladdin->setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
		aladdin->setFrameDelay(0.12f);
		aladdin->setFrames(0, 38);
		aladdin->setCurrentFrame(0);
		aladdin->setState(eType::ALADDIN_IDLE);

		if (isChange)
		{
			aladdin->setHealth(100.0f);
			aladdin->setAppleCollect(50);
			allGem = 3;
			allScore = 0;
		}

		tileMap->LoadMap(eType::MAP_JAFAR);
		if (!audio->isPlaying(eAudio::MUSIC_MAP_JAFAR))
			audio->Play(eAudio::MUSIC_MAP_JAFAR, true);
		if (audio->isPlaying(eAudio::MUSIC_MAP_SULTAN))
			audio->Stop(eAudio::MUSIC_MAP_SULTAN);

		fire = new FireIdle(0.0f, 0.0f);

		break;
	}

	ResetObjectMap();
}

void SceneGame::ResetObjectMap()
{
	listOthers.clear();
	listEnemies.clear();
	listItems.clear();
	listColumns.clear();
	listWeaponOfEnemy.clear();

	isDebugRenderBBox = false;
}

void SceneGame::setMapCurrent(eType type, bool isChange)
{
	//if (mapCurrent != type)
	LoadMap(type, isChange);
}

void SceneGame::CheckCollision()
{
	CheckCollisionWeapon(listOthers);
	CheckCollisionAladdinWithItem();
	CheckCollisionWithEnemy();
	CheckCollisionWithPodiumFire();
}

void SceneGame::CheckCollisionWeapon(std::vector<Entity*> listEnt)
{
	for (auto* weaponApple : aladdin->WeaponApple)
	{
		if (weaponApple->getVisible() && weaponApple->getState() != EXPLOSIVE_APPLE_WEAPON)
		{
			for (auto& entOther : listEnt)
			{
				if (entOther->getKind() == eKind::WALL || entOther->getKind() == eKind::ENEMY)
				{
					if (weaponApple->isCollitionObjectWithObject(entOther, frameTime))
					{
						appleWeapon* aWeapon = dynamic_cast<appleWeapon*>(weaponApple);
						switch (entOther->getType())
						{
						case HAKIM:
							aWeapon->setState(eType::EXPLOSIVE_APPLE_WEAPON);
							if (entOther->getHealth() == 100.0f)
							{
								entOther->setState(eType::HAKIM_BEHIT);
								entOther->setHealth(50.0f);
							}
							else
								if (entOther->getState() != EXPLOSIVE_ENEMY)
									entOther->setState(eType::EXPLOSIVE_ENEMY);
							break;
						case NAHBI:
							aWeapon->setState(eType::EXPLOSIVE_APPLE_WEAPON);
							if (entOther->getHealth() == 100.0f)
							{
								entOther->setState(eType::NAHBI_BEHIT);
								entOther->setHealth(50.0f);
							}
							else
								if (entOther->getState() != EXPLOSIVE_ENEMY)
									entOther->setState(eType::EXPLOSIVE_ENEMY);
							break;
						case SKELETON:
							aWeapon->setState(eType::EXPLOSIVE_APPLE_WEAPON);
							if (entOther->getHealth() == 100.0f)
								entOther->setHealth(50.0f);
							else entOther->setState(eType::EXPLOSIVE_ENEMY);
							break;
						case BATS:
							aWeapon->setState(eType::EXPLOSIVE_APPLE_WEAPON);
							if (entOther->getHealth() == 100.0f)
								entOther->setState(eType::EXPLOSIVE_ENEMY);
							break;
						case JAFAR_BOSS:
							aWeapon->setState(eType::EXPLOSIVE_GENIE, entOther);
							if (entOther->getHealth() > 0.0f)
							{
								entOther->setHealth(entOther->getHealth() - 5);
							}
							break;
						}
						break;
					}
				}
			}
		}
	}

	if (aladdin->sword->getVisible())
	{
		for (int i = 0; i < listEnt.size(); i++)
		{
			if (listEnt[i]->getKind() == eKind::WALL || listEnt[i]->getKind() == eKind::ENEMY)
			{
				//aladdin->setHitWall();
				//DebugOut("TRUNG TUONG\n");
				if (aladdin->sword->isCollitionObjectWithObject(listEnt[i], frameTime))
				{
					switch (listEnt[i]->getType())
					{
					case HAKIM:
						if (listEnt[i]->getHealth() == 100.0f)
						{
							listEnt[i]->setState(eType::HAKIM_BEHIT);
							listEnt[i]->setHealth(50.0f);
						}
						else if (listEnt[i]->getState() != EXPLOSIVE_ENEMY)
							listEnt[i]->setState(eType::EXPLOSIVE_ENEMY);
						break;
					case NAHBI:
						//case BAT:
						if (listEnt[i]->getHealth() == 100.0f)
						{
							listEnt[i]->setState(eType::NAHBI_BEHIT);
							listEnt[i]->setHealth(50.0f);
						}
						else
							if (listEnt[i]->getState() != EXPLOSIVE_ENEMY)
								listEnt[i]->setState(eType::EXPLOSIVE_ENEMY);
						break;
					case SKELETON:
						if (listEnt[i]->getHealth() == 100.0f)
							listEnt[i]->setHealth(50.0f);
						else listEnt[i]->setState(eType::EXPLOSIVE_ENEMY);
						break;
					case BONE:
						if (listEnt[i]->getHealth() == 100.0f || listEnt[i]->getFinished() == false)
						{
							listEnt[i]->setState(eType::EXPLOSIVE_BONE);
						}
						break;
					case BATS:
						if (listEnt[i]->getHealth() != 0.0f)
							listEnt[i]->setState(eType::EXPLOSIVE_ENEMY);
						break;
					}
				}
			}
		}
	}
}

void SceneGame::CheckCollisionAladdinWithItem()
{
	for (int i = 0; i < listItems.size(); i++)
	{
		bool wasCollision = false;
		if (listItems[i]->getHealth() > 0.0f)
		{
			if (aladdin->sword->isCollitionObjectWithObject(listItems[i], frameTime) && aladdin->sword->getVisible())
			{
				switch (listItems[i]->getType())
				{
				case eType::APPLES:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					wasCollision = true;
					aladdin->setAppleCollect(aladdin->getAppleCollect() + 1);
					break;
				case eType::GEMS:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					wasCollision = true;
					allScore += 150;
					allGem++;
					break;
				case eType::HEART_BALLOON:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					wasCollision = true;
					aladdin->setHealth(100.0f);
					allScore += 150;
					break;
				case eType::GENIES:
					listItems[i]->setState(eType::EXPLOSIVE_GENIE);
					wasCollision = true;
					allScore += 250;
					break;
				case eType::VASE:
					listItems[i]->setState(eType::VASE);
					wasCollision = true;
					break;
				}
			}
			if (wasCollision) continue;
			if (aladdin->isCollisionWithItem(listItems[i], frameTime))
			{
				switch (listItems[i]->getType())
				{
				case eType::APPLES:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					aladdin->setAppleCollect(aladdin->getAppleCollect() + 1);
					break;
				case eType::GEMS:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					allGem++;
					allScore += 150;
					break;
				case eType::HEART_BALLOON:
					listItems[i]->setState(eType::EXPLOSIVE_ITEM);
					aladdin->setHealth(100.0f);
					allScore += 150;
					break;
				case eType::CHAINS:
					if (!aladdin->isClimbingChain() && aladdin->getVelocity().y > 0)
						aladdin->setState(ALADDIN_CLIMB, listItems[i]->getCenterX(), listItems[i]->getY(), listItems[i]->getHeight());
					break;
				case eType::GENIES:
					listItems[i]->setState(eType::EXPLOSIVE_GENIE);
					wasCollision = true;
					allScore += 250;
					break;
				case eType::VASE:
					listItems[i]->setState(eType::VASE);
					wasCollision = true;
					break;
				}
			}
		}
	}
}

void SceneGame::CheckCollisionWithEnemy()
{
	CheckCollisionWeapon(listEnemies);
	CheckCollisionWeapon(listWeaponOfEnemy);
	CheckCollisionAladdinWithEnemy();
}

void SceneGame::CheckCollisionAladdinWithEnemy()
{
	if (!aladdin->isUntouchable())
	{
		for (int i = 0; i < listEnemies.size(); i++)
		{
			if (dynamic_cast<NahbiItem*>(listEnemies[i]) && listEnemies[i]->getHealth() > .0f)
			{
				NahbiItem* nahbi = dynamic_cast<NahbiItem*>(listEnemies[i]);
				if (nahbi->getSword()->getVisible())
				{
					if (nahbi->getSword()->isCollitionObjectWithObject(aladdin, frameTime))
					{
						aladdin->setState(eType::ALADDIN_HURT);
						return;

					}
				}
			}
			else {
				if (dynamic_cast<HakimItem*>(listEnemies[i]) && listEnemies[i]->getHealth() > .0f)
				{
					HakimItem* hakim = dynamic_cast<HakimItem*>(listEnemies[i]);
					if (hakim->getSword()->getVisible())
					{
						if (hakim->getSword()->isCollitionObjectWithObject(aladdin, frameTime))
						{
							aladdin->setState(eType::ALADDIN_HURT);
							return;

						}
					}
				}
			}
		}
	}

	if (!aladdin->isUntouchable())
	{
		for (int i = 0; i < listEnemies.size(); i++)
		{
			if (listEnemies[i]->getHealth() > 0.0f)
			{
				if (aladdin->isCollitionObjectWithObject(listEnemies[i], frameTime))
				{
					switch (listEnemies[i]->getType())
					{
					case SPEAR:
					case BUTTRESS:
					case NAHBI:
					case HAKIM:
					case SKELETON:
					case BATS:
					case JAFAR_BOSS:
						aladdin->setState(eType::ALADDIN_HURT);
						return;
						break;
					default:
						break;
					}
				}
			}
		}
	}

	if (!aladdin->isUntouchable())
	{
#pragma region Collision With Weapon of Enemy
		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
		{
			if (listWeaponOfEnemy[i]->getFinished() == false&&listWeaponOfEnemy[i]->getHealth()>0.0f)
			{
				LPCOLLISIONEVENT e = aladdin->SweptAABBEx(listWeaponOfEnemy[i], frameTime);
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					if (e->entity->getType() == STAR)
					{
						e->entity->setState(EXPLOSIVE_BONE);
						if (e->entity->getDirection())
							aladdin->setVelocityX(aladdin->getVelocity().x - 10);
						else aladdin->setVelocityX(aladdin->getVelocity().x + 10);
						//aladdin->MoveViewport(camera);
					}
					else
					{
						aladdin->setState(ALADDIN_HURT);
						return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
					}
				}

				if (aladdin->checkAABB(listWeaponOfEnemy[i]) == true)
				{
					if (listWeaponOfEnemy[i]->getType() == STAR)
					{
						listWeaponOfEnemy[i]->setState(EXPLOSIVE_BONE);
						if (e->entity->getDirection())
							aladdin->setVelocityX(aladdin->getVelocity().x - 10);
						else aladdin->setVelocityX(aladdin->getVelocity().x + 10);
					}
					else
					{
						aladdin->setState(ALADDIN_HURT);
						return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
					}
				}
			}
		}
#pragma endregion
	}
}

void SceneGame::CheckCollisionWithPodiumFire()
{
	if (mapCurrent == eType::MAP_JAFAR)
	{
		if(listEnemies.size()>0)
		{
		//("SL ENEMY: %d\n", listEnemies.size());
			if (listEnemies[0]->getState() == eType::SNAKE_BOSS)
			{
				bool isTouchPodiumFire = false;
				for (auto& podium : listOthers)
				{
					if (podium->getType() == eType::IRON_STEP)
					{
						float lA, tA, rA, bA;
						aladdin->getBoundingBox(lA, tA, rA, bA);
						float lP, tP, rP, bP;
						podium->getBoundingBox(lP, tP, rP, bP);
						/*DebugOut("bA = %.2f\n", bA);
						DebugOut("Y of podium: %.2f\n", podium->getY());*/
						if (bA + 5.0f >= tP && bA < bP && rA >= lP && lA <= rP && aladdin->getVelocity().y>0)
						{
							//DebugOut("CHAMJ\n");
							fire->setVisible(true);
							if (lA < lP)
								fire->setXY(lP - 10.0f, bA - fire->getHeight());
							else {
								if (rA > rP)
									fire->setXY(rP - 30.0f, bA - fire->getHeight());
								else fire->setXY(aladdin->getCenterX() - fire->getWidth() / 2, bA - fire->getHeight());
							}
							isTouchPodiumFire = true;
							if (!aladdin->isUntouchable())
								aladdin->setState(ALADDIN_HURT);
							break;
						}
					}
				}
				if (!isTouchPodiumFire)
				{
					//DebugOut("VISIBLE = %s\n", fire->getVisible() ? "true" : "false");
					if (fire->getVisible())
						fire->setVisible(false);
				}
			}
		}
	}
}

