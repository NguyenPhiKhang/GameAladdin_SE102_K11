#include "Aladdin.h"
#include "Collision.cpp"
#include "Collision.cpp"


Aladdin::Aladdin(Camera* camera, MapGame* mapGame) : Entity()
{
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
	isPushing = false;
	isClimbing = false;
	yChain = 0.0f;
	hChain = 0;
	totalAppleCollect = 50;
	health = 20.0f;
	isDeath = false;
	isCompletedLevel = false;
	isSound = false;
	isRevival = false;

	this->camera = camera;
	this->mapGame = mapGame;

	//WeaponApple.push_back(new SwordWeapon(this));
	//WeaponApple.push_back(new appleWeapon(this, camera));

	sword = new SwordWeapon(this);

	type = eType::ALADDIN_IDLE;
	kind = eKind::ALADDIN;

	colorUntounchable = graphicsNS::ALPHA50;
	CountShake = 0;

	abuFan = new Entity();
	imgCompleted = new Image();
	abuRun = new Entity();
}

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
	isPushing = false;
	isClimbing = false;
	yChain = 0.0f;
	hChain = 0;
	totalAppleCollect = 8;
	health = 90.0f;


	//WeaponApple.push_back(new SwordWeapon(this));
	//WeaponApple.push_back(new appleWeapon(this, camera));

	sword = new SwordWeapon(this);

	type = eType::ALADDIN_IDLE;
	kind = eKind::ALADDIN;
}

Aladdin::~Aladdin()
{
	safeDelete(sword);
}

void Aladdin::update(float frameTime, Game* gamePtr, std::vector<Entity*>* coEntities)
{
	Entity::update(frameTime);
	if (!isDeath)
	{
		if (!isCompletedLevel)
		{
			if (!isRevival)
			{
				if (!isClimbing)
				{
					deltaV.y = GRAVITY_JUMP_SPEED * frameTime;
					CollideWithGround(coEntities, frameTime);
					CollideWithWall(coEntities, frameTime, gamePtr);
					if (isCompletedLevel)
						return;
				}
				//CollideWithEntity(coEntities, frameTime);

#pragma region Kiểm tra có nhập phím để xét các state
				if (gamePtr->getIsPress())
				{
#pragma region PRESS KEY UP
					if (Input::getInstance()->isKeyDown(ALADDIN_UP_KEY) &&
						state != ALADDIN_RUN && state != ALADDIN_SIT && state != ALADDIN_SIT_ATTACK &&
						state != ALADDIN_SIT_THROW && JumpFinsihed && !holdKeyDown && !isClimbing && !isFalling && state != ALADDIN_HURT)
					{
						if (state != ALADDIN_GLANCE_UP && LoopAttackGlance == true)
						{
							//setVelocity(D3DXVECTOR2(0.0f, 0.0f));
							setVelocityX(0.0f);
							LoopFinished = true;
							sword->setVisible(false);
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
								sword->setVisible(true);
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
						state != ALADDIN_SIT && !holdKeyDown && !isFalling
						)
					{
						if (gamePtr->getCountKeyJump() == 0)
						{
							setVelocityY(-ALADDIN_JUMP_SPEED);
							JumpFinsihed = false;
							LoopAttackGlance = true;
							LoopFinished = true;
							sword->setVisible(false);
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
						state != ALADDIN_SIT && !holdKeyDown && !isPushing && !isClimbing)
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
								setVelocityX(-ALADDIN_SPEED);
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
								setVelocityX(ALADDIN_SPEED);
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
									setVelocityX(-ALADDIN_SPEED);
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
									setVelocityX(ALADDIN_SPEED);
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
										sword->setVisible(true);
									}
								}
							}
						}

						if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY) && totalAppleCollect > 0)
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
										Audio::getInstance()->Play(MUSIC_ALADDIN_THROW);
										state = ALADDIN_RUN_THROW;
										if (totalAppleCollect > 0)
										{
											WeaponApple.push_back(new appleWeapon(this, camera));
											totalAppleCollect--;
										}
									}
								}
							}
						}

						if (Input::getInstance()->isKeyDown(ALADDIN_JUMP_KEY))
						{
							if (gamePtr->getCountKeyJump() == 0)
							{
								if (state != ALADDIN_RUN_JUMP && JumpFinsihed && !isFalling)
								{
									setVelocityY(-ALADDIN_JUMP_SPEED);
									holdKeyUP = false;
									JumpFinsihed = false;
									LoopAttackGlance = true;
									LoopFinished = true;
									sword->setVisible(false);
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
						JumpFinsihed && !isClimbing)
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
									frameDelay = 0.06f;
									Audio::getInstance()->Play(MUSIC_ALADDIN_ATK_HIGH);
									setTextureManager(TextureManager::getIntance()->getTexture(ALADDIN_ATTACK));
									state = ALADDIN_ATTACK;
									sword->setVisible(true);
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
						JumpFinsihed && !isClimbing && totalAppleCollect > 0)
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
									Audio::getInstance()->Play(MUSIC_ALADDIN_THROW);
									state = ALADDIN_THROW;
									if (totalAppleCollect > 0)
									{
										WeaponApple.push_back(new appleWeapon(this, camera));
										totalAppleCollect--;
									}
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
						state != ALADDIN_GLANCE_UP && !holdKeyUP && !isClimbing && !isFalling && state != ALADDIN_HURT
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
										Audio::getInstance()->Play(MUSIC_ALADDIN_ATK_LOW);
										state = ALADDIN_SIT_ATTACK;
										sword->setVisible(true);
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
											Audio::getInstance()->Play(MUSIC_ALADDIN_THROW);
											state = ALADDIN_SIT_THROW;
											if (totalAppleCollect > 0)
											{
												WeaponApple.push_back(new appleWeapon(this, camera));
												totalAppleCollect--;
											}
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
						setVelocityX(0.0f);
						currentFrame = 0;
						setFrames(0, 8);
						frameDelay = 0.1f;
						setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_STOP_INERTIA));

						state = ALADDIN_STOP_INERTIA;
					}
					else {
					IDLE:
						if (!isSliding && state != ALADDIN_IDLE && LoopFinished && LoopAttackGlance && JumpFinsihed && !isClimbing && state != ALADDIN_HURT && !isFalling)
						{
							setVelocityX(0.0f);
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
					if (currentFrame > 9)
					{
						isSliding = true;
					}

					//spriteData.x += dx;
					//MoveViewport(camera);
				}
				else {
					if (isSliding && spriteData.x > -10.0f && spriteData.x < mapGame->getWidthMap() - spriteData.width)
					{
						if (currentFrame == 2)
						{
							frameDelay = 0.2f;
							spriteData.x += (spriteData.flipHorizontal) ? -2.0f : 2.0f;

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
						sword->setVisible(false);
					}
				}
				if (state == ALADDIN_RUN_ATTACK || state == ALADDIN_RUN_THROW)
				{
					if (currentFrame == 3)
						frameDelay = 0.15f;
					else frameDelay = 0.08f;
					if (currentFrame == 5)
					{
						LoopFinished = true;
						sword->setVisible(false);
					}
					//spriteData.x += dx;
					//MoveViewport(camera);
				}
				if (state == ALADDIN_CLIMB_ATTACK || state == ALADDIN_CLIMB_THROW)
				{
					if ((state == ALADDIN_CLIMB_ATTACK && currentFrame == 7) || (state == ALADDIN_CLIMB_THROW && currentFrame == 5))
					{
						LoopFinished = true;
						sword->setVisible(false);
					}
					if ((state == ALADDIN_CLIMB_ATTACK && currentFrame == 2) || (state == ALADDIN_CLIMB_ATTACK && currentFrame == 5))
					{
						Audio::getInstance()->Play(MUSIC_ALADDIN_ATK_HIGH);
					}
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
							sword->setVisible(false);
						}
						else { currentFrame = 1; }
					}
					if (currentFrame == 2 || currentFrame == 6)
					{
						Audio::getInstance()->Play(MUSIC_ALADDIN_ATK_HIGH);
					}
				}
				if (state == ALADDIN_SIT_ATTACK || state == ALADDIN_SIT_THROW)
				{
					if (currentFrame == 6)
					{
						LoopFinished = true;
						sword->setVisible(false);
					}
				}

				if (state == ALADDIN_HURT)
				{
					if (currentFrame == 5)
						setState(eType::ALADDIN_IDLE);
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
							}
						}
						else {
							if (state == ALADDIN_CLIMB_JUMP)
							{
								if (velocity.y < 0 && currentFrame == 2)
								{
									currentFrame = 2;
									setFrames(0, 0);
								}

								if (velocity.y > 0 && currentFrame == 2)
								{
									setFrames(3, 8);
									setCurrentFrame(3);
									frameDelay = 0.07f;
								}

								if (currentFrame == 8)
								{
									currentFrame = 8;
									setFrames(0, 0);
								}
							}
						}
					}

					if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY) && state != ALADDIN_JUMP_ATTACK)
					{
						currentFrame = 0;
						setFrames(0, 6);
						setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP_ATTACK));
						frameDelay = 0.08f;
						Audio::getInstance()->Play(MUSIC_ALADDIN_ATK_HIGH);
						state = ALADDIN_JUMP_ATTACK;
						sword->setVisible(true);
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

					if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY) && state != ALADDIN_JUMP_THROW && totalAppleCollect > 0)
					{
						currentFrame = 0;
						setFrames(0, 6);
						setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP_THROW));
						frameDelay = 0.08f;
						Audio::getInstance()->Play(MUSIC_ALADDIN_THROW);
						state = ALADDIN_JUMP_THROW;
						if (totalAppleCollect > 0)
						{
							WeaponApple.push_back(new appleWeapon(this, camera));
							totalAppleCollect--;
						}
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

					//spriteData.x += dx;
					/*spriteData.y += dy;
					MoveViewport(camera);*/
				}

				if (isClimbing)
				{
					if (Input::getInstance()->isKeyDown(ALADDIN_LEFT_KEY) && LoopFinished)
					{
						spriteData.flipHorizontal = true;
					}
					else
						if (Input::getInstance()->isKeyDown(ALADDIN_RIGHT_KEY) && LoopFinished)
						{
							spriteData.flipHorizontal = false;
						}
					if (Input::getInstance()->isKeyDown(ALADDIN_UP_KEY)) {
						LoopFinished = true;
						sword->setVisible(false);
						if (state != ALADDIN_CLIMB)
						{
							setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB));
							state = ALADDIN_CLIMB;
						}
						setFrames(1, 9);
						currentFrame = abs(currentFrame);
						frameDelay = 0.05f;
						setVelocityY(-80.0f);
						if (currentFrame == 9)
						{
							spriteData.flipHorizontal = !spriteData.flipHorizontal;
							setCurrentFrame(1);
						}
						spriteData.y += dy;
						if (spriteData.y + 5 < yChain)
						{
							spriteData.y = yChain - 5;
							setFrames(0, 0);
						}
					}
					else
					{
						if (Input::getInstance()->isKeyDown(ALADDIN_DOWN_KEY))
						{
							LoopFinished = true;
							sword->setVisible(false);
							if (currentFrame > 0)
								currentFrame = -currentFrame;
							if (state != ALADDIN_CLIMB)
							{
								setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB));
								state = ALADDIN_CLIMB;
							}
							setFrames(-8, 0);
							frameDelay = 0.04f;
							setVelocityY(80.0f);
							if (currentFrame == 0)
							{
								spriteData.flipHorizontal = !spriteData.flipHorizontal;
								setCurrentFrame(-8);
							}
							spriteData.y += dy;
							if (spriteData.y + 44 > yChain + hChain - 60)
							{
								isClimbing = false;
								isFalling = true;
							}
						}
						else {
							setVelocityY(0.0f);
							if (Input::getInstance()->isKeyDown(ALADDIN_ATTACK_KEY))
							{
								if (gamePtr->getCountKeyAttack() == 0)
								{
									if (LoopFinished)
									{
										if (state != ALADDIN_CLIMB_ATTACK)
										{
											frameDelay = 0.08f;
											currentFrame = 0;
											LoopFinished = false;
											setFrames(0, 7);
											setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB_ATTACK));
											state = ALADDIN_CLIMB_ATTACK;
											sword->setVisible(true);
										}
									}
								}
							}
							else {
								if (Input::getInstance()->isKeyDown(ALADDIN_THROW_KEY) && totalAppleCollect > 0)
								{
									if (gamePtr->getCountKeyThrow() == 0)
									{
										if (LoopFinished)
										{
											if (state != ALADDIN_CLIMB_THROW)
											{
												frameDelay = 0.08f;
												currentFrame = 0;
												LoopFinished = false;
												setFrames(0, 5);
												setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB_THROW));
												Audio::getInstance()->Play(MUSIC_ALADDIN_THROW);
												state = ALADDIN_CLIMB_THROW;
												if (totalAppleCollect > 0)
												{
													WeaponApple.push_back(new appleWeapon(this, camera));
													totalAppleCollect--;
												}
											}
										}
									}
								}
								else
									if (LoopFinished)
									{
										setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB));
										state = ALADDIN_CLIMB;
										setFrames(0, 0);
										setCurrentFrame(abs(currentFrame));
									}
							}
						}
					}
					if (Input::getInstance()->isKeyDown(ALADDIN_JUMP_KEY))
					{
						LoopFinished = true;
						sword->setVisible(false);
						JumpFinsihed = false;
						isClimbing = false;
						if (state != ALADDIN_CLIMB_JUMP)
						{
							setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB_JUMP));
							state = ALADDIN_CLIMB_JUMP;
							setFrames(0, 9);
							frameDelay = 0.05f;
							setVelocityY(-ALADDIN_JUMP_SPEED);
							currentFrame = 0;
						}

					}
				}

				if (isFalling && state == ALADDIN_IDLE)
				{
					if (JumpFinsihed)
					{
						setVelocityY(200.0f);
						JumpFinsihed = false;
						LoopAttackGlance = true;
						LoopFinished = true;
						sword->setVisible(false);
						isSliding = false;
						currentFrame = 5;
						setFrames(5, 9);
						setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_JUMP));
						frameDelay = 0.06f;

						state = ALADDIN_JUMP;
					}
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

#pragma region Kiểm tra có được va chạm hay không
				if (unTouchable == true)
				{
					QueryPerformanceCounter(&timeEnd);
					if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / gamePtr->getTimeFreq().QuadPart) > 1.0f)
					{
						unTouchable = false;
					}
				}
#pragma endregion


				if (sword->getVisible())
				{
					sword->update(coEntities, frameTime);
				}
				for (int i = 0; i < WeaponApple.size(); i++)
				{
					if (WeaponApple[i]->getVisible() == true)
					{
						if (WeaponApple[i]->getType() == APPLE_WEAPON && WeaponApple[i]->getFinished())
						{
							WeaponApple.erase(WeaponApple.begin() + i);
							i--;
							return;
						}
						WeaponApple[i]->update(coEntities, frameTime);
					}
				}

				//DebugOut("SO TAO: %d\n", totalAppleCollect);

				MoveViewport(camera);
				//DebugOut("isFalling: [%s]\n", isFalling?"true":"false");
			}
			else {
				if (state == ALADDIN_REVIVAL && currentFrame == 13)
				{
					setState(ALADDIN_IDLE);
					isRevival = false;
				}
				if (currentFrame == 5)
				{
					if (!Audio::getInstance()->isPlaying(eAudio::MUSIC_REVIVAL))
						Audio::getInstance()->Play(eAudio::MUSIC_REVIVAL);
				}
			}
		}
		else {
			abuRun->update(frameTime);
			abuRun->setX(abuRun->getX() + abuRun->getDX());
			spriteData.x += dx;
			if (state == ALADDIN_RUN_COMPLETED)
			{
				if (spriteData.x < 0)
				{
					if (gamePtr->getMapCurrent() == eType::MAP_SULTAN)
						gamePtr->setMapCurrent(eType::JAFAR_INTRO);
					else {
						if (gamePtr->getMapCurrent() == eType::MAP_JAFAR)
							gamePtr->setMapCurrent(eType::MAP_INTRO);
					}
					isCompletedLevel = false;
				}
			}
		}
	}
	else
	{
		abuFan->update(frameTime);
		if (abuFan->getCurrentFrame() == 3)
		{
			if (!Audio::getInstance()->isPlaying(MUSIC_ABU_FAN))
				Audio::getInstance()->Play(MUSIC_ABU_FAN);
		}

		if (state == ALADDIN_SHAKE)
		{
			if (currentFrame == 8 && CountShake < 8)
			{
				setFrames(2, 8);
				CountShake++;
			}
			else {
				if (currentFrame == 8 && CountShake >= 8)
				{
					CountShake = 0;
					setState(eType::ALADDIN_CARRIED);
				}
			}
		}
		else {
			if (currentFrame == 18 && CountShake < 10)
			{
				setFrames(15, 18);
				CountShake++;
			}
			else {
				if (currentFrame == 18 && CountShake >= 10)
				{
					isDeath = false;
					CountShake = 0;
					gamePtr->setMapCurrent((eType)gamePtr->getMapCurrent(), gamePtr->getAllChance() < 0 ? true : false);
				}
			}
		}
	}

	if (state == ALADDIN_CARRIED && currentFrame == 4)
	{
		Audio::getInstance()->Play(MUSIC_BOOM_HUG);
		Audio::getInstance()->Play(MUSIC_BOXING_BELL);
	}
}

void Aladdin::draw(COLOR_ARGB color)
{
	if (!isDeath)
	{
		if (!isCompletedLevel)
		{
			if (unTouchable == false)
				Entity::draw(color);
			else Entity::draw((rand() % 3 < 1) ? graphicsNS::ALPHA40 & colorFilter : graphicsNS::ALPHA80 & colorFilter);

			if (sword->getVisible())
			{
				sword->setViewport(camera->CameraTransform(sword->getX(), sword->getY()));
				sword->draw();
			}
			for (auto& weapon : WeaponApple)
			{
				if (weapon->getVisible() == true)
				{
					weapon->setViewport(camera->CameraTransform(weapon->getX(), weapon->getY()));
					weapon->draw();
				}
			}
		}
		else {
			imgCompleted->draw();
			abuRun->setViewport(D3DXVECTOR2(abuRun->getX(), abuRun->getY()));
			abuRun->draw();
			setViewport(D3DXVECTOR2(spriteData.x, spriteData.y));
			Entity::draw();
		}
	}
	else {
		Entity::draw(color);
		abuFan->draw(color);
	}
}

void Aladdin::MoveViewport(Camera* camera, bool moveX, bool moveY)
{
	// camera position X
	if (moveX)
	{
		if (spriteData.x > marginWhenChangeDirection&&
			spriteData.x > marginWhenRun&&
			spriteData.x < mapGame->getWidthMap() - GAME_WIDTH + marginWhenRun &&
			spriteData.x < mapGame->getWidthMap() - GAME_WIDTH + marginWhenChangeDirection
			)
		{
			camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
		}
		if (spriteData.x < marginWhenRun) {
			if (camera->getXCamera() > 0)
				camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
			else camera->setPositionCam(0, camera->getYCamera());
		}
		if (spriteData.x > mapGame->getWidthMap() - GAME_WIDTH + marginWhenRun) {
			if (camera->getXCamera() < mapGame->getWidthMap() - GAME_WIDTH)
				camera->setPositionCam(spriteData.x - marginWhenChangeDirection, camera->getYCamera());
			else camera->setPositionCam((float)(mapGame->getWidthMap() - GAME_WIDTH), camera->getYCamera());
		}
		if (spriteData.x > mapGame->getWidthMap() - spriteData.width + 50)
			spriteData.x = (float)mapGame->getWidthMap() - spriteData.width + 50;
		if (spriteData.x < -50.0f)
			spriteData.x = -50.0f;
	}
	// camera position Y
	if (moveY)
	{
		if (spriteData.y > marginVertical&&
			//spriteData.y > marginWhenGlance &&
			//spriteData.y < mapGame->getHeightMap() - GAME_HEIGHT + /*marginWhenGlance*/ marginVertical &&
			spriteData.y < mapGame->getHeightMap() - GAME_HEIGHT + marginVertical
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

		if (spriteData.y > mapGame->getHeightMap() - GAME_HEIGHT + marginVertical)
		{
			/*if (camera->getYCamera() < mapGame->getHeightMap() - GAME_HEIGHT)
				camera->setPositionCam(camera->getXCamera(), spriteData.y - marginVertical);
			else */camera->setPositionCam(camera->getXCamera(), (float)(mapGame->getHeightMap() - GAME_HEIGHT));
		}
		if (spriteData.y > mapGame->getHeightMap() - spriteData.height)
			spriteData.y = (float)mapGame->getHeightMap() - spriteData.height;
		if (spriteData.y < -60.0f)
			spriteData.y = -60.0f;
	}
}

void Aladdin::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case ALADDIN_IDLE:
	case ALADDIN_ATTACK:
	case ALADDIN_RUN_ATTACK:
	case ALADDIN_HURT:
		positionBoundingBox(left, top, right, bottom, 61, 61, 55, 14, 46);
		break;
	case ALADDIN_GLANCE_UP:
	case ALADDIN_GLANCE_ATTACK:
	case ALADDIN_JUMP_ATTACK:
	case ALADDIN_JUMP_THROW:
		positionBoundingBox(left, top, right, bottom, 61, 61, 50, 14, 51);
		break;
	case ALADDIN_JUMP:
	case ALADDIN_CLIMB:
		positionBoundingBox(left, top, right, bottom, 61, 61, 44, 14, 57);
		break;
	case ALADDIN_RUN:
		positionBoundingBox(left, top, right, bottom, 61, 61, 52, 14, 49);
		break;
	case ALADDIN_RUN_JUMP:
		positionBoundingBox(left, top, right, bottom, 52, 61, 58, 23, 43);
		break;
	case ALADDIN_STOP_INERTIA:
		positionBoundingBox(left, top, right, bottom, 61, 61, 58, 14, 43);
		break;
	case ALADDIN_THROW:
	case ALADDIN_RUN_THROW:
		positionBoundingBox(left, top, right, bottom, 61, 61, 48, 14, 53);
		break;
	case ALADDIN_SIT:
	case ALADDIN_SIT_ATTACK:
		positionBoundingBox(left, top, right, bottom, 61, 61, 73, 14, 28);
	case ALADDIN_SIT_THROW:
		positionBoundingBox(left, top, right, bottom, 61, 61, 71, 14, 30);
		break;
	case ALADDIN_PUSH:
		positionBoundingBox(left, top, right, bottom, 31, 61, 70, 44, 31);
		break;
	case ALADDIN_CLIMB_ATTACK:
	case ALADDIN_CLIMB_THROW:
		positionBoundingBox(left, top, right, bottom, 61, 61, 41, 14, 61);
		break;
	case ALADDIN_CLIMB_JUMP:
		positionBoundingBox(left, top, right, bottom, 61, 61, 36, 14, 65);
		break;
	case ALADDIN_REVIVAL:
		//positionBoundingBox(left, top, right, bottom, )
		break;
	}
}

void Aladdin::RenderBoundingBox(Camera* camera)
{
	if (!isDeath)
	{
		Entity::RenderBoundingBox(camera);
		if (sword->getVisible())
		{
			sword->RenderBoundingBox(camera);
		}
		for (auto& weapon : WeaponApple)
		{
			if (weapon->getVisible() == true)
			{
				weapon->RenderBoundingBox(camera);
			}
		}
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

void Aladdin::setState(int statenew, float xCenterChain, float yChain, int hChain)
{
	//Entity::setState(state);
	switch ((eType)statenew)
	{
	case ALADDIN_CLIMB:
		Entity::setState(statenew);
		if (!isClimbing)
		{
			isClimbing = true;
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_CLIMB));
			setFrames(0, 0);
			setCurrentFrame(1);
			setVelocity(D3DXVECTOR2(0.0f, 0.0f));
			setX(xCenterChain - spriteData.width / 2);
			isPushing = false;
			JumpFinsihed = true;
			isSliding = false;
			LoopFinished = true;
			sword->setVisible(false);
			this->yChain = yChain;
			this->hChain = hChain;
		}
		break;
	case ALADDIN_IDLE:
		Entity::setState(statenew);
		setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
		setVelocityX(0.0f);
		currentFrame = 0;
		setFrames(0, 38);
		frameDelay = 0.08f;
		isFalling = true;
		isPushing = false;
		isClimbing = false;
		isSliding = false;
		LoopFinished = true;
		LoopAttackGlance = true;
		JumpFinsihed = true;
		spriteData.flipHorizontal = false;
		break;
	case ALADDIN_HURT:
		if (state == ALADDIN_IDLE || state == ALADDIN_SIT || state == ALADDIN_GLANCE_UP || state == ALADDIN_STOP_INERTIA || state == ALADDIN_PUSH)
		{
			Entity::setState(statenew);
			setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_HURT));
			setVelocityX(0.0f);
			currentFrame = 0;
			setFrames(0, 5);
			frameDelay = 0.18f;
			isFalling = true;
			isPushing = false;
			isClimbing = false;
			isSliding = false;
			LoopFinished = true;
			LoopAttackGlance = true;
			JumpFinsihed = true;
			unTouchable = true;
			health -= 10.0f;
			QueryPerformanceCounter(&timeStart);
		}
		else {
			unTouchable = true;
			health -= 10.0f;
			QueryPerformanceCounter(&timeStart);
		}
		Audio::getInstance()->Play(MUSIC_ALADDIN_HURT);
		break;
	case ALADDIN_SHAKE:
		Entity::setState(statenew);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)statenew));
		setVelocityX(0.0f);
		currentFrame = 0;
		setFrames(0, 8);
		frameDelay = 0.12f;
		setViewport(D3DXVECTOR2(120.0f, 80.0f));
		spriteData.flipHorizontal = false;
		abuFan->setTextureManager(TextureManager::getIntance()->getTexture(eType::ABU_FAN));
		abuFan->setFrames(0, 5);
		abuFan->setCurrentFrame(0);
		abuFan->setFrameDelay(0.08f);
		abuFan->setViewport(D3DXVECTOR2(200.0f, 125.0f));
		Audio::getInstance()->StopAll();

		//Audio::getInstance()->Play(MUSIC_ABU_FAN,true);
		break;
	case ALADDIN_CARRIED:
		Entity::setState(statenew);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)statenew));
		setVelocityX(0.0f);
		setFrames(0, 18);
		setCurrentFrame(0);
		frameDelay = 0.12f;

		break;
	case ALADDIN_RUN_COMPLETED:
		Entity::setState(statenew);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)statenew));
		setVelocityX(0.0f);
		setFrames(0, 9);
		setCurrentFrame(0);
		frameDelay = 0.12f;
		velocity.x = -100.0f;
		setXY(380.0f, 151.0f);
		spriteData.flipHorizontal = true;
		abuRun->setTextureManager(TextureManager::getIntance()->getTexture(eType::ABU_RUN));
		abuRun->setFrames(0, 7);
		abuRun->setCurrentFrame(0);
		abuRun->setFrameDelay(0.12f);
		abuRun->setXY(320.0f, 175.0f);
		abuRun->setVelocityX(-100.0f);
		isCompletedLevel = true;
		imgCompleted->setTextureManager(TextureManager::getIntance()->getTexture(eType::LEVEL_COMPLETED));
		break;
	case ALADDIN_REVIVAL:
		Entity::setState(ALADDIN_REVIVAL);
		isRevival = true;
		break;
	}
}

bool Aladdin::isClimbingChain()
{
	return isClimbing;
}

void Aladdin::CollideWithGround(std::vector<Entity*>* coEntities, float frameTime)
{
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	std::vector<Entity*> list_ground;
	list_ground.clear();

	for (UINT i = 0; i < coEntities->size(); i++)
		if (coEntities->at(i)->getKind() == eKind::FLOOR)
			list_ground.push_back(coEntities->at(i));

	CalcPotentialCollisions(&list_ground, coEvents, frameTime);

	if (coEvents.size() == 0)
	{
		spriteData.y += dy;
		if (!isFalling)
		{
			isFalling = true;
			if (velocity.y > 0)
				velocity.y = 200.0f;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (ny == -1)
		{
			spriteData.y += min_ty * dy + ny * 0.4f;
			velocity.y = ALADDIN_JUMP_SPEED;
			if (!JumpFinsihed)
			{
				JumpFinsihed = true;
				marginVertical = cameraNS::marginVertical;
				setVelocityX(0.0f);
				currentFrame = 0;
				setFrames(0, 38);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_IDLE));
				frameDelay = 0.08f;

				state = ALADDIN_IDLE;
			}
			if (isFalling == true)
			{
				isFalling = false;
				isSliding = false;
				/*setVelocityY(200.0f);
				JumpFinsihed = false;
				LoopAttackGlance = true;
				LoopFinished = true;
				sword->setVisible(false);
				isSliding = false;
				currentFrame = 5;
				setFrames(0, 15);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_TOUCHGROUND));
				frameDelay = 0.06f;

				state = ALADDIN_TOUCHGROUND;*/
			}
		}
		else spriteData.y += dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void Aladdin::CollideWithWall(std::vector<Entity*>* coEntities, float frameTime, Game* gamePtr)
{
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	std::vector<Entity*> list_wall;
	list_wall.clear();

	for (UINT i = 0; i < coEntities->size(); i++)
		if (coEntities->at(i)->getKind() == eKind::WALL)
		{
			list_wall.push_back(coEntities->at(i));
		}

	CalcPotentialCollisions(&list_wall, coEvents, frameTime);
	if (coEvents.size() == 0)
	{
		spriteData.x += dx;
		isPushing = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0)
		{
			for (int i = 0; i < coEventsResult.size(); i++)
			{
				if (coEventsResult.at(i)->entity->getType() == eType::EXITS)
				{
					//gamePtr->setMapCurrent(eType::MAP_JAFAR);
					//Sleep(500);
					if (Audio::getInstance()->isPlaying(eAudio::MUSIC_MAP_SULTAN))
						Audio::getInstance()->Stop(eAudio::MUSIC_MAP_SULTAN);
					Audio::getInstance()->Play(MUSIC_EXIT);
					setState(eType::ALADDIN_RUN_COMPLETED);
					return;
				}
			}
			spriteData.x += min_tx * dx + nx * 0.4f;
			DebugOut("push wall ! nx= %.2f\n", nx);

			if (state == ALADDIN_PUSH && currentFrame == 1 && !isSound)
			{
				Audio::getInstance()->Play(MUSIC_ALADDIN_PUSH);
				isSound = true;
			}
			else
			{
				isSound = false;
			}

			if (state != ALADDIN_PUSH && JumpFinsihed && !isFalling)
			{
				isPushing = true;
				LoopFinished = true;
				sword->setVisible(false);

				isSliding = false;
				currentFrame = 0;
				setFrames(1, 8);
				setTextureManager(TextureManager::getIntance()->getTexture(eType::ALADDIN_PUSH));
				frameDelay = 0.15f;

				state = ALADDIN_PUSH;
			}
		}
		else spriteData.x += dx;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

bool Aladdin::isCollisionWithItem(Entity* entItem, float frameTime)
{
	if (entItem->getHealth() <= 0.0f)
		return false;

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->getBoundingBox(l, t, r, b);  // lấy BBOX của simon

	entItem->getBoundingBox(l1, t1, r1, b1);
	if (this->checkAABB(l, t, r, b, l1, t1, r1, b1) == true)
	{
		return true; // check with AABB
	}

	return isCollitionObjectWithObject(entItem, frameTime);
}

void Aladdin::setHitWall()
{
	sword->setCurrentFrame(endFrame);
}
