#include "FireRun.h"

FireRun::FireRun(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::FIRE_RUN;
	setTextureManager(TextureManager::getIntance()->getTexture(eType::FIRE_RUN));
	setCurrentFrame(0);
	setFrames(0, 7);
	frameDelay = 0.1f;
	velocity.y = 20.0f;
	finished = false;
}

FireRun::~FireRun()
{
}

void FireRun::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	deltaV.y = 20.0f * frameTime;
#pragma region Xu li va cham Ground
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	std::vector<Entity*> list_floor;
	list_floor.clear();

	for (UINT i = 0; i < listObj->size(); i++)
		if (listObj->at(i)->getKind() == eKind::FLOOR|| listObj->at(i)->getKind() == eKind::WALL)
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
			if (coEnt->entity->getKind() == eKind::FLOOR)
			{
				if (ny == -1)
				{
					spriteData.y += min_ty * dy + ny * 0.4f;
					velocity.y = 200.0f;
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
					DebugOut("Ket thuc Fire [nx = %.2f]\n", nx);
				}
				else spriteData.x+= dx;
			}
			else spriteData.x += dx;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
}

void FireRun::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (spriteData.flipHorizontal == false)
	{
		left = spriteData.x + 10;
	}
	else {
		left = spriteData.x + 33;
	}
	top = spriteData.y + 30;
	right = left + 56;
	bottom = top + 20;
}
