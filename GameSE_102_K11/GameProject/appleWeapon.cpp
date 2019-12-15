#include "appleWeapon.h"

appleWeapon::appleWeapon(Entity* ent, Camera* camera)
{
	this->ent = ent;
	startFly = false;
	//visible = false;
	this->camera = camera;
	type = eType::APPLE_WEAPON;
	finished = false;
}

appleWeapon::~appleWeapon()
{
}

void appleWeapon::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);

	CollideWithGround(listObj, frameTime);

	if (!startFly)
	{
		switch (ent->getState())
		{
		case ALADDIN_THROW:
			if (ent->getCurrentFrame() == 3)
			{
				setState(APPLE_WEAPON);
				if (!ent->getDirection())
				{
					velocity.x = 250;
					velocity.y = 50;
					spriteData.x = ent->getX() + 83;
					spriteData.y = ent->getY() + 41;
				}
				else {
					velocity.x = -250;
					velocity.y = 50;
					spriteData.x = ent->getX() + 53;
					spriteData.y = ent->getY() + 41;
				}
				startFly = true;
			}
			break;
		case ALADDIN_RUN_THROW:
			if (ent->getCurrentFrame() == 3)
			{
				setState(APPLE_WEAPON);
				if (!ent->getDirection())
				{
					velocity.x = 350;
					velocity.y = 20;
					spriteData.x = ent->getX() + 80;
					spriteData.y = ent->getY() + 48;
				}
				else {
					velocity.x = -350;
					velocity.y = 20;
					spriteData.x = ent->getX() + 55;
					spriteData.y = ent->getY() + 48;
				}
				startFly = true;
			}
			break;
		case ALADDIN_JUMP_THROW:
			if (ent->getCurrentFrame() == 3)
			{
				setState(APPLE_WEAPON);
				if (!ent->getDirection())
				{
					velocity.x = 250;
					velocity.y = 150;
					spriteData.x = ent->getX() + 86;
					spriteData.y = ent->getY() + 46;
				}
				else {
					velocity.x = -250;
					velocity.y = 150;
					spriteData.x = ent->getX() + 47;
					spriteData.y = ent->getY() + 46;
				}
				startFly = true;
			}
			break;
		case ALADDIN_SIT_THROW:
			if (ent->getCurrentFrame() == 4)
			{
				setState(APPLE_WEAPON);
				if (!ent->getDirection())
				{
					velocity.x = 350;
					velocity.y = 30;
					spriteData.x = ent->getX() + 89;
					spriteData.y = ent->getY() + 60;
				}
				else {
					velocity.x = -350;
					velocity.y = 30;
					spriteData.x = ent->getX() + 44;
					spriteData.y = ent->getY() + 60;
				}
				startFly = true;
			}
			break;
		case ALADDIN_CLIMB_THROW:
			if (ent->getCurrentFrame() == 4)
			{
				setState(APPLE_WEAPON);
				if (!ent->getDirection())
				{
					velocity.x = 350;
					velocity.y = 30;
					spriteData.x = ent->getX() + 89;
					spriteData.y = ent->getY() + 55;
				}
				else {
					velocity.x = -350;
					velocity.y = 30;
					spriteData.x = ent->getX() + 44;
					spriteData.y = ent->getY() + 55;
				}
				startFly = true;
			}
			break;
		default:
			setVelocity(D3DXVECTOR2(0.0f, 0.0f));
			visible = false;
			break;
		}
	}
	if (velocity.y > 0.0f)
		deltaV.y = 3.0f;
	else deltaV.y = 0.0f;

	spriteData.x += dx;
	spriteData.y += dy;

	if (startFly)
	{
		if (spriteData.x - camera->getXCamera() > GAME_WIDTH || spriteData.x - camera->getXCamera() < 0 ||
			spriteData.y - camera->getYCamera() > GAME_HEIGHT || spriteData.y - camera->getYCamera() < 0)
		{
			visible = false;
			startFly = false;
			finished = true;
		}
	}

	if (health == 0.0f)
	{
		if (currentFrame == 4)
		{
			finished = true;
		}
	}

}

void appleWeapon::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}
}

void appleWeapon::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case EXPLOSIVE_APPLE_WEAPON:
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 4);
		currentFrame = 0;
		frameDelay = 0.04f;
		setVelocity(D3DXVECTOR2(0.0f, 0.0f));
		health = 0.0f;
		break;
	case APPLE_WEAPON:
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 3);
		currentFrame = 0;
		frameDelay = 0.08f;
	default:
		break;
	}

}

void appleWeapon::CollideWithGround(std::vector<Entity*>* coEntities, float frameTime)
{
	if (startFly)
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
			//spriteData.y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			if (ny == -1)
			{
				spriteData.y += min_ty * dy + ny * 0.4f;
				//velocity.y = ALADDIN_JUMP_SPEED;
				if (state != EXPLOSIVE_APPLE_WEAPON)
				{
					setState(EXPLOSIVE_APPLE_WEAPON);
				}
			}
			//else spriteData.y += dy;
		}

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}
