#include "Aladdin.h"
#include "Collision.cpp"
#include "Collision.cpp"


Aladdin::Aladdin(float x, float y) :Entity()
{
	spriteData.x = x;
	spriteData.y = y;
	isSliding = false;
	marginWhenChangeDirection = cameraNS::marginLeft;
	marginWhenRun = cameraNS::marginLeft;
	marginVertical = cameraNS::marginVertical;

	isPressDirectionFirst = 0;
	checkDirection = true;
	LoopFinished = true;
	LoopAttackGlance = true;
	countLoopAttackGlance = 0;
	JumpFinsihed = true;
	holdKeyUP = false;
	holdKeyDown = false;

	_widthOld = 0;
	_heightOld = 0;
	isFalling = false;

	type = eType::ALADDIN;
}

Aladdin::~Aladdin()
{
}

void Aladdin::update(float frameTime, Camera* camera, Game* gamePtr, std::vector<Entity*>* coEntities)
{
	Entity::update(frameTime);
	
	deltaV.y = GRAVITY_JUMP_SPEED * frameTime;
	CollideWithGround(coEntities, frameTime);

#pragma region Kiểm tra có nhập phím để xét các state
	if (gamePtr->getIsPress())
	{
#pragma region PRESS KEY UP
		if (Input::getInstance()->isKeyDown(ALADDIN_UP_KEY) &&
			state != ALADDIN_RUN && state != ALADDIN_SIT && state != ALADDIN_SIT_ATTACK && state != ALADDIN_SIT_THROW && JumpFinsihed && !holdKeyDown)
		{
			if (state != ALADDIN_GLANCE_UP && LoopAttackGlance == true)
			{
				setVelocity(D3DXVECTOR2(0.0f, 0.0f));
				LoopFinished = true;
				isSliding = false;
				currentFrame = 0;
				setFrames(0, 2);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_GLANCE_UP));
				frameDelay = 0.15f;

				state = ALADDIN_GLANCE_UP;
			}
			if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY) && !spriteData.flipHorizontal && LoopAttackGlance) spriteData.flipHorizontal = true;
			if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY) && spriteData.flipHorizontal && LoopAttackGlance) spriteData.flipHorizontal = false;
			if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY)) {
				if (state != ALADDIN_GLANCE_ATTACK && LoopAttackGlance)
				{
					LoopAttackGlance = false;
					currentFrame = 0;
					setFrames(0, 9);
					setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_GLANCE_ATTACK));
					frameDelay = 0.075f;

					state = ALADDIN_GLANCE_ATTACK;
				}
			}
			if (gamePtr->getSumTimeKeyUp() > 0.001f && !holdKeyUP)
			{
				holdKeyUP = true;
			}
		}
		else {
			if (!Input::getInstance()->isKeyDown(ALADDIN_UP_KEY)) {
				holdKeyUP = false;
			}
		}
#pragma endregion	...// ngước lên

#pragma region PRESS KEY JUMP
		if (Input::getInstance()->isKeyDown(ALADDIN_JUMP_KEY) &&
			state != ALADDIN_RUN && JumpFinsihed &&
			state != ALADDIN_GLANCE_UP && !holdKeyUP &&
			state != ALADDIN_SIT && !holdKeyDown
			)
		{
			if (gamePtr->getCountKeyJump() == 0)
			{
				setVelocityY(-ALADDIN_JUMP_SPEED);
				JumpFinsihed = false;
				LoopAttackGlance = true;
				LoopFinished = true;
				isSliding = false;
				currentFrame = 0;
				setFrames(0, 9);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP));
				frameDelay = 0.06f;

				state = ALADDIN_JUMP;

			}
		}
#pragma endregion	...// đang nhảy

#pragma region PRESS KEY RUN
		if ((Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY) || Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY)) &&
			state != ALADDIN_GLANCE_UP && !holdKeyUP &&
			/*state != ALADDIN_JUMP && state!= ALADDIN_JUMP_ATTACK && state!= ALADDIN_JUMP_THROW*/
			JumpFinsihed &&
			state != ALADDIN_SIT && !holdKeyDown)
		{
			if (state != ALADDIN_RUN && LoopFinished && JumpFinsihed)
			{
				currentFrame = 0;
				isSliding = false;
				LoopAttackGlance = true;
				setFrames(0, 12);
				frameDelay = 0.08f;

				if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY))
				{
					isPressDirectionFirst = -1;
					setVelocity(D3DXVECTOR2(-ALADDIN_SPEED, 0.0f));
					currentFrame = 0;
					if (spriteData.flipHorizontal == true)
						checkDirection = true;
					else {
						checkDirection = false;
						spriteData.flipHorizontal = true;
						marginWhenRun = cameraNS::marginRight;
					}
				}

				if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
				{
					isPressDirectionFirst = 1;
					setVelocity(D3DXVECTOR2(ALADDIN_SPEED, 0.0f));
					currentFrame = 0;
					if (spriteData.flipHorizontal == false)
						checkDirection = true;
					else {
						checkDirection = false;
						spriteData.flipHorizontal = false;
						marginWhenRun = cameraNS::marginLeft;
					}
				}
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_RUN));

				state = ALADDIN_RUN;

			}
			else {
				if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY))
				{
					if (!spriteData.flipHorizontal)
					{
						setVelocity(D3DXVECTOR2(-ALADDIN_SPEED, 0.0f));
						isPressDirectionFirst = -1;
						checkDirection = false;
						spriteData.flipHorizontal = true;
						marginWhenRun = cameraNS::marginRight;
					}
				}

				if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
				{
					if (spriteData.flipHorizontal)
					{
						setVelocity(D3DXVECTOR2(ALADDIN_SPEED, 0.0f));
						isPressDirectionFirst = 1;
						checkDirection = false;
						spriteData.flipHorizontal = false;
						marginWhenRun = cameraNS::marginLeft;
					}

				}
			}

			if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY))
			{
				if (gamePtr->getCountKeyAttack() == 0)
				{
					if (LoopFinished)
					{
						if (state != ALADDIN_RUN_ATTACK) {
							frameDelay = 0.08f;
							currentFrame = 0;
							isSliding = false;
							LoopFinished = false;
							setFrames(0, 5);
							setTextureManager(TextureManager::getIntance()->getTexture(ALADDIN_RUN_ATTACK));

							state = ALADDIN_RUN_ATTACK;
						}
					}
				}
			}

			if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY))
			{
				if (gamePtr->getCountKeyThrow() == 0)
				{
					if (LoopFinished)
					{
						if (state != ALADDIN_RUN_THROW) {
							frameDelay = 0.08f;
							currentFrame = 0;
							isSliding = false;
							LoopFinished = false;
							setFrames(0, 5);
							setTextureManager(TextureManager::getIntance()->getTexture(ALADDIN_RUN_THROW));

							state = ALADDIN_RUN_THROW;
						}
					}
				}
			}

			if (Input::getInstance()->isKeyDown(ALADDIN_JUMP_KEY))
			{
				if (gamePtr->getCountKeyJump() == 0)
				{
					if (state != ALADDIN_RUN_JUMP && JumpFinsihed)
					{
						setVelocityY(-ALADDIN_JUMP_SPEED);
						holdKeyUP = false;
						JumpFinsihed = false;
						LoopAttackGlance = true;
						LoopFinished = true;
						isSliding = false;
						currentFrame = 0;
						setFrames(0, 6);
						setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_RUN_JUMP));
						frameDelay = 0.08f;

						state = ALADDIN_RUN_JUMP;
					}
				}
			}
		}
#pragma endregion	...// đang chạy

#pragma region PRESS KEY ATTACK
		if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY) &&
			state != ALADDIN_GLANCE_UP && state != ALADDIN_GLANCE_ATTACK &&
			state != ALADDIN_RUN && state != ALADDIN_RUN_ATTACK &&
			/*state!=ALADDIN_JUMP && state!=ALADDIN_JUMP_ATTACK && state!=ALADDIN_JUMP_THROW*/
			state != ALADDIN_SIT && !holdKeyDown && !holdKeyUP &&
			JumpFinsihed)
		{
			if (gamePtr->getCountKeyAttack() == 0)
			{
				if (LoopFinished)
				{
					if (state != ALADDIN_ATTACK) {
						setVelocity(D3DXVECTOR2(0.0f, 0.0f));
						LoopFinished = false;
						isSliding = false;
						currentFrame = 0;
						setFrames(0, 6);
						frameDelay = 0.08f;
						setTextureManager(TextureManager::getIntance()->getTexture(ALADDIN_ATTACK));

						state = ALADDIN_ATTACK;
					}
				}
			}
			else goto IDLE;
		}
#pragma endregion ...// đang đứng chém

#pragma region PRESS KEY THROW
		if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY) &&
			state != ALADDIN_GLANCE_UP && state != ALADDIN_GLANCE_ATTACK &&
			state != ALADDIN_RUN && state != ALADDIN_RUN_ATTACK &&
			state != ALADDIN_SIT && !holdKeyDown && !holdKeyUP &&
			JumpFinsihed)
		{
			if (gamePtr->getCountKeyThrow() == 0)
			{
				if (LoopFinished)
				{
					if (state != ALADDIN_THROW) {
						setVelocity(D3DXVECTOR2(0.0f, 0.0f));
						frameDelay = 0.08f;
						currentFrame = 0;
						isSliding = false;
						LoopFinished = false;
						setFrames(0, 6);
						setTextureManager(TextureManager::getIntance()->getTexture(ALADDIN_THROW));

						state = ALADDIN_THROW;
					}
				}
			}
			else {
				goto IDLE;
			}
		}
#pragma endregion ...// đang đứng ném	

#pragma region PRESS KEY DOWN
		if (Input::getInstance()->isKeyDown(ALADDIN_DOWN_KEY) &&
			state != ALADDIN_RUN && JumpFinsihed &&
			state != ALADDIN_GLANCE_UP && !holdKeyUP
			)
		{
			if (state != ALADDIN_SIT && LoopFinished)
			{
				setVelocity(D3DXVECTOR2(0.0f, 0.0f));
				isSliding = false;
				LoopAttackGlance = true;
				if (!holdKeyDown)
					currentFrame = 0;
				else currentFrame = 3;
				setFrames(0, 3);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_SIT));
				frameDelay = 0.15f;
				state = ALADDIN_SIT;
			}
			if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY) && !spriteData.flipHorizontal && LoopAttackGlance) spriteData.flipHorizontal = true;
			if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY) && spriteData.flipHorizontal && LoopAttackGlance) spriteData.flipHorizontal = false;
			if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY)) {
				if (gamePtr->getCountKeyAttack() == 0)
				{
					if (LoopFinished)
					{
						if (state != ALADDIN_GLANCE_ATTACK)
						{
							LoopAttackGlance = true;
							LoopFinished = false;
							currentFrame = 0;
							setFrames(0, 6);
							setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_SIT_ATTACK));
							frameDelay = 0.1f;

							state = ALADDIN_SIT_ATTACK;
						}
					}
				}
			}
			else {
				if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY))
				{
					if (gamePtr->getCountKeyThrow() == 0)
					{
						if (LoopFinished)
						{
							if (state != ALADDIN_SIT_THROW)
							{
								LoopAttackGlance = true;
								LoopFinished = false;
								currentFrame = 0;
								setFrames(0, 6);
								setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_SIT_THROW));
								frameDelay = 0.1f;

								state = ALADDIN_SIT_THROW;
							}
						}
					}
				}
			}
			if (gamePtr->getSumTimeKeyDown() > 0.001f && !holdKeyDown)
			{
				holdKeyDown = true;
			}
		}
		else {
			if (!Input::getInstance()->isKeyDown(ALADDIN_DOWN_KEY)) {
				holdKeyDown = false;
			}
		}
#pragma endregion ...// đang ngồi

	}
	else // trường hợp không nhấn key nào
	{
		holdKeyUP = false;
		holdKeyDown = false;

		if (isSliding && state != ALADDIN_STOP_INERTIA)
		{
			setVelocity(D3DXVECTOR2(0.0f, 0.0f));
			currentFrame = 0;
			setFrames(0, 8);
			frameDelay = 0.1f;
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_STOP_INERTIA));

			state = ALADDIN_STOP_INERTIA;
		}
		else {
		IDLE:
			if (!isSliding && state != ALADDIN_IDLE && LoopFinished && LoopAttackGlance && JumpFinsihed)
			{
				setVelocity(D3DXVECTOR2(0.0f, 0.0f));
				currentFrame = 0;
				setFrames(0, 38);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
				frameDelay = 0.08f;

				state = ALADDIN_IDLE;
			}
		}
	}
#pragma endregion

#pragma region Kiểm tra các state của aladdin để xử lý
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
		if (currentFrame == 12)
			currentFrame = 1;
		if (currentFrame > 8)
		{
			isSliding = true;
		}

		spriteData.x += dx;
		//MoveViewport(camera);
	}
	else {
		if (isSliding && spriteData.x > -10.0f && spriteData.x < MapNS::MAP_WIDTH_1 - spriteData.width)
		{
			if (currentFrame == 2)
			{
				frameDelay = 0.2f;
				spriteData.x += (spriteData.flipHorizontal) ? -1.0f : 1.0f;

				//MoveViewport(camera);
			}
			else frameDelay = 0.08f;
			if (currentFrame == 8)
				isSliding = false;
		}
		else isSliding = false;
	}
	if (state == ALADDIN_ATTACK || state == ALADDIN_THROW)
	{
		if (currentFrame == 6)
		{
			LoopFinished = true;
		}
	}
	if (state == ALADDIN_RUN_ATTACK || state == ALADDIN_RUN_THROW)
	{
		if (currentFrame == 3)
			frameDelay = 0.15f;
		else frameDelay = 0.08f;
		if (currentFrame == 5)
			LoopFinished = true;
		spriteData.x += dx;
		//MoveViewport(camera);
	}
	if (state == ALADDIN_GLANCE_UP)
	{
		if (currentFrame == 2)
			setFrames(2, 2);
	}
	if (state == ALADDIN_SIT)
	{
		if (currentFrame == 3)
			setFrames(3, 3);
	}
	if (state == ALADDIN_GLANCE_ATTACK)
	{
		if (currentFrame == 9)
		{
			countLoopAttackGlance++;
			if (countLoopAttackGlance > 2)
			{
				LoopAttackGlance = true;
				countLoopAttackGlance = 0;
			}
			else currentFrame = 1;
		}
	}
	if (state == ALADDIN_SIT_ATTACK || state == ALADDIN_SIT_THROW)
	{
		if (currentFrame == 6)
			LoopFinished = true;
	}
	if (!JumpFinsihed)
	{
		if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY))
		{
			setVelocityX(-ALADDIN_SPEED);
			spriteData.flipHorizontal = true;
		}
		else
			if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY))
			{
				setVelocityX(ALADDIN_SPEED);
				spriteData.flipHorizontal = false;
			}
			else setVelocityX(0.0f);

		if (state == ALADDIN_RUN_JUMP)
		{
			if (getVelocity().y < 0 && getVelocity().y + 20 > 0)
			{
				currentFrame = 3;
				setFrames(3, 5);
				setFrameDelay(0.1f);
			}
			else {
				if (getVelocity().y < 0)
				{
					if (currentFrame > 1)
						setFrameDelay(0.15f);
					if (currentFrame == 4)
						setFrames(4, 4);
				}
			}
			if (getVelocity().y > 0)
			{
				if (currentFrame == 5)
					setFrames(5, 5);
			}/*
			if (getVelocity().y + 20.0f >= 350.0f)
			{
				setCurrentFrame(6);
				frameDelay = 1.0f;
			}*/

		}
		else {
			if (state == ALADDIN_JUMP)
			{
				if (currentFrame == 1 || currentFrame == 6)
					setFrames(0, 0);

				if (getVelocity().y < 0 && getVelocity().y + 25 > 0)
				{
					setFrames(2, 6);
					setFrameDelay(0.11f);
					setCurrentFrame(2);
				}/*

				if (getVelocity().y + 80 >= 350.0f)
				{
					if (currentFrame < 7)
					{
						setFrames(7, 9);
						setFrameDelay(0.08f);
						currentFrame = 7;
					}
					else {
						if (currentFrame == 9)
							setFrameDelay(0.1f);
						else setFrameDelay(0.08f);
					}
				}*/
			}
		}

		if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY) && state != ALADDIN_JUMP_ATTACK)
		{
			currentFrame = 0;
			setFrames(0, 6);
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP_ATTACK));
			frameDelay = 0.08f;
			state = ALADDIN_JUMP_ATTACK;
		}
		else
		{
			if (state == ALADDIN_JUMP_ATTACK)
			{
				if (currentFrame == 3)
					frameDelay = 0.18f;
				else frameDelay = 0.08f;
			}
		}

		if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY) && state != ALADDIN_JUMP_THROW)
		{
			currentFrame = 0;
			setFrames(0, 6);
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP_THROW));
			frameDelay = 0.08f;
			state = ALADDIN_JUMP_THROW;
		}
		else {
			if (state == ALADDIN_JUMP_THROW)
			{
				if (currentFrame == 2)
					frameDelay = 0.15f;
				else frameDelay = 0.08f;

				if (currentFrame == 6)
				{
					setFrames(0, 0);
				}
			}
		}

		spriteData.x += dx;
		/*spriteData.y += dy;
		MoveViewport(camera);*/
	}

#pragma endregion 

#pragma region Kiểm tra khi nhấn phím di chuyển nếu là lần đầu thì move viewport
	if (!checkDirection) // kiểm tra hướng có thay đổi hay không?
	{
		switch (isPressDirectionFirst)
		{
		case 1: // nhấn nút right đầu tiên
			if (marginWhenChangeDirection > marginWhenRun)
			{
				marginWhenChangeDirection -= 3.0f;

				MoveViewport(camera);
			}
			else {
				isPressDirectionFirst = 0;
				marginWhenChangeDirection = marginWhenRun;
			}
			break;
		case -1: //nhấn nút trái đầu tiên
			if (marginWhenChangeDirection < marginWhenRun)
			{
				marginWhenChangeDirection += 3.0f;

				MoveViewport(camera);
			}
			else {
				isPressDirectionFirst = 0;
				marginWhenChangeDirection = marginWhenRun;
			}
		default: // == 0
			break;
		}
	}
#pragma endregion

#pragma region Kiểm tra có giữ nút up/ down hay không? để move up/down viewport
	if (holdKeyUP && gamePtr->getSumTimeKeyUp() > 0.001f)
	{
		if (marginVertical < cameraNS::marginWhenGlance)
		{
			marginVertical += 4.0f;
			if (marginVertical > cameraNS::marginWhenGlance)
				marginVertical = cameraNS::marginWhenGlance;
			MoveViewport(camera);
		}
	}
	else
	{
		if (holdKeyDown && gamePtr->getSumTimeKeyDown() > 0.001f)
		{
			if (marginVertical > cameraNS::marginWhenSit)
			{
				marginVertical += -4.0f;
				if (marginVertical < cameraNS::marginWhenSit)
					marginVertical = cameraNS::marginWhenSit;
				MoveViewport(camera);
			}
		}
		else
			if (marginVertical < cameraNS::marginVertical)
			{
				marginVertical += 4.0f;
				if (marginVertical > cameraNS::marginVertical)
					marginVertical = cameraNS::marginVertical;
				MoveViewport(camera);
			}
			else
				if (marginVertical > cameraNS::marginVertical)
				{
					marginVertical += -4.0f;
					if (marginVertical < cameraNS::marginVertical)
						marginVertical = cameraNS::marginVertical;
					MoveViewport(camera);
				}
				else marginVertical = cameraNS::marginVertical;
	}
#pragma endregion

	MoveViewport(camera);
	//DebugOut("Vy: %.2f\n", velocity.y);
}

void Aladdin::MoveViewport(Camera* camera, bool moveX, bool moveY)
{
	// camera position X
	if (moveX)
	{
		if (spriteData.x > marginWhenChangeDirection&&
			spriteData.x > marginWhenRun&&
			spriteData.x < MapNS::MAP_WIDTH_1 - GAME_WIDTH + marginWhenRun &&
			spriteData.x < MapNS::MAP_WIDTH_1 - GAME_WIDTH + marginWhenChangeDirection
			)
		{
			camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
		}
		if (spriteData.x < marginWhenRun) {
			if (camera->getXCamera() > 0)
				camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
			else camera->setPositionCam(0, camera->getYCamera());
		}
		if (spriteData.x > MapNS::MAP_WIDTH_1 - GAME_WIDTH + marginWhenRun) {
			if (camera->getXCamera() < MapNS::MAP_WIDTH_1 - GAME_WIDTH)
				camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
			else camera->setPositionCam(MapNS::MAP_WIDTH_1 - GAME_WIDTH, camera->getYCamera());
		}
		if (spriteData.x > MapNS::MAP_WIDTH_1 - spriteData.width + 50)
			spriteData.x = (float)MapNS::MAP_WIDTH_1 - spriteData.width + 50;
		if (spriteData.x < -50.0f)
			spriteData.x = -50.0f;
	}
	// camera position Y
	if (moveY)
	{
		if (spriteData.y > marginVertical&&
			//spriteData.y > /*marginWhenGlance*/ cameraNS::marginVertical&&
			//spriteData.y < MapNS::MAP_HEIGHT_1 - GAME_HEIGHT + /*marginWhenGlance*/ cameraNS::marginVertical &&
			spriteData.y < MapNS::MAP_HEIGHT_1 - GAME_HEIGHT + marginVertical
			)
		{
			camera->setPositionCam(camera->getXCamera(), spriteData.y - marginVertical);
		}

		if (spriteData.y < marginVertical)
		{
			if (camera->getYCamera() > 0)
				camera->setPositionCam(camera->getXCamera(), spriteData.y - marginVertical);
			else camera->setPositionCam(camera->getXCamera(), 0.0f);
		}

		if (spriteData.y > MapNS::MAP_HEIGHT_1 - GAME_HEIGHT + marginVertical)
		{
			/*if (camera->getYCamera() < MapNS::MAP_HEIGHT_1 - GAME_HEIGHT)
				camera->setPositionCam(camera->getXCamera(), spriteData.y - marginVertical);
			else*/ camera->setPositionCam(camera->getXCamera(), MapNS::MAP_HEIGHT_1 - GAME_HEIGHT);
		}
		if (spriteData.y > MapNS::MAP_HEIGHT_1 - spriteData.height)
			spriteData.y = (float)MapNS::MAP_HEIGHT_1 - spriteData.height;
		if (spriteData.y < 0.0f)
			spriteData.y = 0.0f;
	}
}

//void Aladdin::ChangePositionState(int skewX, int skewY, bool isMoveX)
//{
//	_widthOld = TextureManager::getIntance()->getTexture((eType)state)->getWidthFrame();
//	/*_heightOld = TextureManager::getIntance()->getTexture((eType)state)->getHeightFrame();*/
//	//spriteData.y += /*(_heightOld - spriteData.height)*/ - skewY;
//	if (isMoveX)
//	{
//		if (!spriteData.flipHorizontal)
//		{
//			spriteData.x += skewX;
//		}
//		else {
//			spriteData.x += (_widthOld - spriteData.width) - skewX;
//		}
//	}
//}

void Aladdin::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case ALADDIN_IDLE:
		if(!(currentFrame>=0&&currentFrame<9))
			positionBoundingBox(left, top, right, bottom, 55, 56, 49, 17, 52);
		else positionBoundingBox(left, top, right, bottom, 43, 57, 53, 28, 48);
		break;
	case ALADDIN_GLANCE_UP:
		positionBoundingBox(left, top, right, bottom, 43, 57, 50, 28, 51);
		break;
	case ALADDIN_GLANCE_ATTACK:
		if (currentFrame == 3 || currentFrame == 4 || currentFrame == 5)
			positionBoundingBox(left, top, right, bottom, 38, 62, 49, 28, 52);
		else positionBoundingBox(left, top, right, bottom, 45, 55, 53, 28, 48);
		break;
	case ALADDIN_JUMP:
		if (currentFrame == 0 || currentFrame == 9)
			positionBoundingBox(left, top, right, bottom, 41, 59, 68, 28, 34);
		else positionBoundingBox(left, top, right, bottom, 43, 60, 41, 25, 61);
		break;
	case ALADDIN_JUMP_ATTACK:
		//if (currentFrame == 0 || currentFrame == 6)
			positionBoundingBox(left, top, right, bottom, 48, 49, 48, 31, 54);
		//else positionBoundingBox(left, top, right, bottom, 50, 51, 56, 27, 42);
		break;
	case ALADDIN_JUMP_THROW:
		//if (currentFrame == 6)
			positionBoundingBox(left, top, right, bottom, 47, 57, 51, 24, 51);
		//else positionBoundingBox(left, top, right, bottom, 47, 53, 51, 28, 48);
		break;
	case ALADDIN_RUN:
		positionBoundingBox(left, top, right, bottom, 33, 65, 52, 30, 49);
		break;
	case ALADDIN_ATTACK:
		positionBoundingBox(left, top, right, bottom, 44, 58, 53, 26, 48);
		break;
	case ALADDIN_RUN_JUMP:
		if (currentFrame == 0 || currentFrame == 2 || currentFrame == 3)
			positionBoundingBox(left, top, right, bottom, 36, 60, 65, 32, 36);
		else if (currentFrame == 1)
			positionBoundingBox(left, top, right, bottom, 37, 61, 50, 30, 58);
		else positionBoundingBox(left, top, right, bottom, 29, 67, 52, 32, 50);
		break;
	case ALADDIN_STOP_INERTIA:
		positionBoundingBox(left, top, right, bottom, 36, 54, 51, 38, 50);
		break;
	case ALADDIN_THROW:
		positionBoundingBox(left, top, right, bottom, 42, 58, 48, 28, 53);
		break;
	case ALADDIN_RUN_ATTACK:
		positionBoundingBox(left, top, right, bottom, 36, 62, 53, 30, 48);
		break;
	case ALADDIN_RUN_THROW:
		positionBoundingBox(left, top, right, bottom, 36, 66, 48, 26, 53);
		break;
	case ALADDIN_SIT:
		if (currentFrame == 0)
			positionBoundingBox(left, top, right, bottom, 42, 62, 57, 24, 44);
		else positionBoundingBox(left, top, right, bottom, 45, 51, 73, 32, 28);
		break;
	case ALADDIN_SIT_ATTACK:
		positionBoundingBox(left, top, right, bottom, 36, 50, 73, 42, 28);
		break;
	case ALADDIN_SIT_THROW:
		if (currentFrame == 2 || currentFrame == 3 || currentFrame == 4)
			positionBoundingBox(left, top, right, bottom, 44, 56, 66, 28, 35);
		else positionBoundingBox(left, top, right, bottom, 39, 51, 71, 38, 30);
		break;
	}
}

void Aladdin::positionBoundingBox(float& left, float& top, float& right, float& bottom,
	float posLeft, float posLeftFlip, float posTop,
	float bbWidth, float bbHeight)
{
	left = (!spriteData.flipHorizontal) ? spriteData.x + posLeft : spriteData.x + posLeftFlip;
	top = spriteData.y + posTop;
	right = left + bbWidth;
	bottom = top + bbHeight;
}

void Aladdin::CollideWithGround(std::vector<Entity*>* coEntities, float frameTime)
{
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	std::vector<Entity*> list_ground;
	list_ground.clear();

	for (UINT i = 0; i < coEntities->size(); i++)
		if (coEntities->at(i)->getType()==eType::GROUND|| coEntities->at(i)->getType() == eType::WOOD ||
			coEntities->at(i)->getType() == eType::IRON_STEP || coEntities->at(i)->getType()== eType::PODIUM)
			list_ground.push_back(coEntities->at(i));

	CalcPotentialCollisions(this, &list_ground, coEvents, frameTime);

	if (coEvents.size() == 0)
	{
		//spriteData.x += dx;
		spriteData.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//////spriteData.x += min_tx * dx + nx * 0.4f;
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	/*if (dynamic_cast<CGoomba*>(e->obj))
		//	{*/

		//	if (e->entity->getType() == eType::WOOD)
		//	{
		//		//DebugOut("wood, nx = %.2f, ny = %.2f, t= %.2f\n", e->nx, e->ny, e->t);
		//		DebugOut("aladdin, nx = %.2f, ny = %.2f, min_tx= %.2f, min_ty = %.2f\n", nx, ny, min_tx, min_ty);
		//	}
		//}

		if (ny == -1)
		{
			spriteData.y += min_ty * dy + ny * 0.4f;
			velocity.y = ALADDIN_JUMP_SPEED;
			if (!JumpFinsihed)
			{
				JumpFinsihed = true;
				marginVertical = cameraNS::marginVertical;
			}
		}
		else spriteData.y += dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

