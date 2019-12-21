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
}

StarWeapon::~StarWeapon()
{
}

void StarWeapon::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	/*if (health == 0.0f && state == EXPLOSIVE_ENEMY)
	{
		if (currentFrame == 9)
			visible = false;
	}
	else {*/
	deltaV.y =  _gravity* frameTime;
#pragma region Xu li va cham Ground
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	std::vector<Entity*> list_floor;
	list_floor.clear();

	for (UINT i = 0; i < listObj->size(); i++)
		if (listObj->at(i)->getType() == eType::IRON_STEP)
			list_floor.push_back(listObj->at(i));

	CalcPotentialCollisions(&list_floor, coEvents, frameTime);
	if (coEvents.size() == 0)
	{
		spriteData.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (ny == -1)
		{
			//spriteData.y += min_ty * dy + ny * 0.4f;
			velocity.y = -100.0f;
			_gravity = -_gravity;
		}
		else spriteData.y += dy;
	}
	spriteData.x += dx;

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
}
