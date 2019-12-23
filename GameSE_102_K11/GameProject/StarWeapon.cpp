#include "StarWeapon.h"

StarWeapon::StarWeapon(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	velocity.y = 100.0f;
	setTextureManager(TextureManager::getIntance()->getTexture(eType::STAR));
	setFrames(0, 2);
	frameDelay = 0.1f;
	_gravity = 500.0f;
	type = eType::STAR;
	state = STAR;
	finished = false;
}

StarWeapon::~StarWeapon()
{
}

void StarWeapon::update(std::vector<Entity*>* listObj, float frameTime)
{
	if (flag == 0)
		Entity::update(listObj, frameTime);
	else
	{
		spriteData.x += dx;
		spriteData.y += dy;
		Image::update(frameTime);
	}

	if (health == 0.0f && state == EXPLOSIVE_BONE)
	{
		if (currentFrame == 3)
			finished = true;
	}
	else {
		deltaV.y = _gravity * frameTime;
#pragma region Xu li va cham Ground
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		std::vector<Entity*> list_floor;
		list_floor.clear();

		for (UINT i = 0; i < listObj->size(); i++)
			if (listObj->at(i)->getType() == eType::GROUND || listObj->at(i)->getKind() == eKind::WALL)
				list_floor.push_back(listObj->at(i));

		CalcPotentialCollisions(&list_floor, coEvents, frameTime);
		
		if (coEvents.size() == 0)
		{
			spriteData.y += dy;
			spriteData.x += dx;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (auto& coEnt : coEventsResult)
			{
				if (coEnt->entity->getType() == eType::GROUND)
				{
					if (ny == -1)
					{
						//spriteData.y += min_ty * dy + ny * 0.4f;
						velocity.y = -15.0f;
						_gravity = -_gravity;
					}
					else spriteData.y += dy;
				}
				else spriteData.y += dy;

				if (coEnt->entity->getKind() == eKind::WALL)
				{
					if (nx != 0)
					{
						spriteData.x += min_tx * dx + nx * 0.4f;
						finished = true;
						DebugOut("Ket thuc STAR [nx = %.2f]\n", nx);
					}
					else spriteData.x += dx;
				}
				else spriteData.x += dx;
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
#pragma endregion
}

void StarWeapon::setState(int state)
{
	Entity::setState(state);
	if (state == eType::EXPLOSIVE_BONE)
	{
		setTextureManager(TextureManager::getIntance()->getTexture(eType::EXPLOSIVE_BONE));
		setFrames(0, 3);
		setCurrentFrame(0);
		frameDelay = 0.1f;
		setY(spriteData.y - 5);
		health = .0f;
	}
}
