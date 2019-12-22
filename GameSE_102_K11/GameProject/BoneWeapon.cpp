#include "BoneWeapon.h"

BoneWeapon::BoneWeapon(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::BONE;
	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");
	QueryPerformanceCounter(&timeStart);        // get starting time
	finished = false;
}

BoneWeapon::~BoneWeapon()
{
}
void BoneWeapon::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	deltaV.y = 100.0f * frameTime;
#pragma region Xu li va cham Ground
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	std::vector<Entity*> list_floor;
	list_floor.clear();

	for (UINT i = 0; i < listObj->size(); i++)
		if (listObj->at(i)->getKind()==eKind::FLOOR||listObj->at(i)->getKind()==eKind::WALL)
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
		/*spriteData.y += min_ty * dy + ny * 0.4f;
		spriteData.x += min_tx * dx + nx * 0.4f;*/
		for (auto& obj : coEventsResult)
		{
			if (obj->entity->getKind() == FLOOR)
			{
				if (ny != 0)
				{
					spriteData.y += min_ty * dy + ny * 0.4f;
					velocity.y = -velocity.y;
				}
				else spriteData.y += dy;
			}
			else spriteData.y += dy;
			if (obj->entity->getKind() == WALL)
			{
				if (nx != 0)
				{
					spriteData.x += min_tx * dx + nx * 0.4f;
					velocity.x = -velocity.x;
				}
				else spriteData.x += dx;
			}
			else spriteData.x += dx;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
	if (health != 0)
	{
		spriteData.x += dx;
		spriteData.y += dy;
		QueryPerformanceCounter(&timeEnd);
		if (((float)(timeEnd.QuadPart - timeStart.QuadPart) / timerFreq.QuadPart) > 1.5f)
		{
			setState(EXPLOSIVE_BONE);
			health = 0.0f;
			QueryPerformanceCounter(&timeStart);
			//finished = true;
		}
	}
	else {
		if (currentFrame == 3 && state == EXPLOSIVE_BONE)
		{
			finished = true;
		}
	}
}

void BoneWeapon::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0)
	{
		left = spriteData.x + 6;
		top = spriteData.y + 4;
		right = left + 5;
		bottom = top + 7;
	}
}

void BoneWeapon::setState(int state)
{
	Entity::setState(state);
	if (state == eType::EXPLOSIVE_BONE)
	{
		setTextureManager(TextureManager::getIntance()->getTexture(eType::EXPLOSIVE_BONE));
		setFrames(0, 3);
		setCurrentFrame(0);
		frameDelay = 0.1f;
		health = .0f;
	}
}
