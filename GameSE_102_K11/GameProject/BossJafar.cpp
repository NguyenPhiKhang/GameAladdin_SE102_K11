#include "BossJafar.h"

BossJafar::BossJafar(float x, float y, Aladdin* aladdin, std::vector<Entity*>* listWeaponOfEnemy)
{
	spriteData.x = x;
	spriteData.y = y;
	this->aladdin = aladdin;
	kind = eKind::ENEMY;
	type = eType::JAFAR_BOSS;
	health = 160.0f;
	this->listWeaponOfEnemy = listWeaponOfEnemy;
	isSpray = false;

}

BossJafar::~BossJafar()
{
	safeDelete(fire1);
	safeDelete(fire2);
}

void BossJafar::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (state == SNAKE_BOSS)
	{
		fire1->update(listObj, frameTime);
		fire2->update(listObj, frameTime);
	}
	float lA, tA, bA, rA;
	aladdin->getBoundingBox(lA, tA, rA, bA);
	float lE, tE, bE, rE;
	getBoundingBox(lE, tE, rE, bE);

	if ((lA - lE) <= 0)
	{
		if (spriteData.flipHorizontal == false)
			spriteData.flipHorizontal = true;
	}
	else {
		if (spriteData.flipHorizontal == true)
			spriteData.flipHorizontal = false;
	}
	//if(he)
	if (health < 110.0f && state != SNAKE_BOSS)
	{
		setState(SNAKE_BOSS);
		fire1 = new FireIdle(380.0f, 294.0f);
		fire2 = new FireIdle(411.0f, 294.0f);
	}

	if (state == JAFAR_BOSS)
	{
		if (currentFrame == 6)
		{
			frameDelay = 3.0f;
			StarWeapon* star = new StarWeapon(spriteData.x + 103.0f, spriteData.y + 26.0f);
			star->flipHorizontal((spriteData.flipHorizontal) ? false : true);
			star->setVelocityX((spriteData.flipHorizontal) ? -300.0f : 300.0f);
			listWeaponOfEnemy->push_back(star);
		}
		else
			if (currentFrame == 0)
				frameDelay = 0.5f;
			else frameDelay = 0.15f;
		//if()
	}

	if (state == SNAKE_BOSS)
	{
		if (currentFrame == 8)
		{
			frameDelay = 0.25f;
			if (isSpray)
				isSpray = false;
		}
		else frameDelay = 0.12f;
		if (currentFrame == 10 && !isSpray)
		{
			Entity* fire = new FireRun((!spriteData.flipHorizontal) ? 370.0f : 356.0f, 297.0f);
			fire->setVelocityX((!spriteData.flipHorizontal) ? 100.0f : -100.0f);
			fire->flipHorizontal(spriteData.flipHorizontal);
			listWeaponOfEnemy->push_back(fire);
			isSpray = true;
		}

	}
	//DebugOut("HEALTH: %.2f\n", health);
}

void BossJafar::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 47;
		right = left + 20;
		top = spriteData.y + 30;
		bottom = top + 54;
	}
}

void BossJafar::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case SNAKE_BOSS:
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setCurrentFrame(0);
		setFrames(0, 10);
		setFrameDelay(0.12f);
		break;
	default:
		break;
	}
}

void BossJafar::setViewport(Camera* camera)
{
	Entity::setViewport(camera);
	if (state == SNAKE_BOSS)
	{
		fire1->setViewport(camera);
		fire2->setViewport(camera);
	}
}

void BossJafar::draw(COLOR_ARGB color)
{
	if (state == SNAKE_BOSS)
	{
		fire2->draw(color);
	}
	Entity::draw(color);
	if (state == SNAKE_BOSS)
	{
		fire1->draw(color);
	}
}
