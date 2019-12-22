#include "HakimItem.h"

HakimItem::HakimItem(float x, float y, Aladdin* aladdin)
{
	spriteData.x = x - 70;
	spriteData.y = y - 4;
	type = eType::HAKIM;
	kind = eKind::ENEMY;
	this->aladdin = aladdin;
	isHurt = false;
	isAttack = false;
	velocity.y = 10;
	sword = new SwordWeapon(this);
	firstX = spriteData.x;
	firstY = spriteData.y;
}

HakimItem::~HakimItem()
{
	safeDelete(sword);
}

void HakimItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if(health == 0.0f && state == EXPLOSIVE_ENEMY)
	{
		if (currentFrame == 9)
			visible = false;
	}
	else {
		deltaV.y = GRAVITY_JUMP_SPEED * frameTime;
#pragma region Xu li va cham Ground
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		std::vector<Entity*> list_floor;
		list_floor.clear();

		for (UINT i = 0; i < listObj->size(); i++)
			if (listObj->at(i)->getType() == eType::WOOD)
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
				spriteData.y += min_ty * dy + ny * 0.4f;
				velocity.y = ALADDIN_JUMP_SPEED;
			}
			else spriteData.y += dy;
		}

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
#pragma endregion

		float lA, tA, bA, rA;
		aladdin->getBoundingBox(lA, tA, rA, bA);
		float lE, tE, bE, rE;
		getBoundingBox(lE, tE, rE, bE);

		if (!isHurt)
		{
			if (((tE - bA) > 2 || (bE - tA) < -10) && state != HAKIM_IDLE)
			{
				setState(HAKIM_IDLE);
			}

			if ((lA - lE) <= 0)
			{
				if (spriteData.flipHorizontal == false)
					spriteData.flipHorizontal = true;
				if (((rA - lE) >= -75) && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					if (!isAttack)
					{
						setState(HAKIM_ATTACK);
					}
				}
				else if ((lA - rE) < -75 && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					spriteData.x += -100 * frameTime;
					setLimit();
					if (spriteData.x + 71 < LimitLeft)
						spriteData.x = LimitLeft - 71;
					if ((lA - rE) < -75 && spriteData.x == LimitLeft - 71)
					{
						if (state != HAKIM_IDLE)
							setState(HAKIM_IDLE);
					}
					else {
						if (state != HAKIM_RUN)
							setState(HAKIM_RUN);
					}
					if (lA - (rE - 100 * frameTime) > -75)
						spriteData.x = spriteData.x + (75.0f - (lA - (rE - 100 * frameTime)));

				}
			}
			else {
				if (spriteData.flipHorizontal == true)
					spriteData.flipHorizontal = false;
				if (((lA - rE) <= 75) && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					if (!isAttack)
					{
						setState(HAKIM_ATTACK);
					}
				}
				else {
					if ((lA - rE) > 75 && !((tE - bA) > 2 || (bE - tA) < -10))
					{
						spriteData.x += 100 * frameTime;
						setLimit();
						if (spriteData.x + 85 > LimitRight)
						{
							spriteData.x = LimitRight - 85;
						}
						if ((lA - rE) > 75 && spriteData.x == LimitRight - 85)
						{
							if (state != HAKIM_IDLE)
								setState(HAKIM_IDLE);
						}
						else {
							if (state != HAKIM_RUN)
								setState(HAKIM_RUN);
						}
						if (lA - (rE + 100 * frameTime) < 75)
							spriteData.x = spriteData.x - (75.0f - (lA - (rE + 100 * frameTime)));
					}
				}
			}
		}
		else {
			if (currentFrame == 8)
				isHurt = false;
		}
		if (sword->getVisible())
		{
			sword->update(listObj, frameTime);
		}
	}
}


void HakimItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 71;
		right = left + 14;                 //width 28,height 49
		top = spriteData.y + 16;
		bottom = top + 58;
	}
}

void HakimItem::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case EXPLOSIVE_ENEMY:
	{
		D3DXVECTOR2 centerHakim = getCenter();
		setCurrentFrame(0);
		health = 0.0f;
		sword->setVisible(false);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 9);
		frameDelay = 0.1f;
		setXY(centerHakim.x - spriteData.width / 2, centerHakim.y - spriteData.height / 2);
		return;
	}
	case HAKIM_BEHIT:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 8);
		frameDelay = 0.15f;
		isHurt = true;
		isAttack = false;
		sword->setVisible(false);
		break;
	case HAKIM_IDLE:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 0);
		isAttack = false;
		sword->setVisible(false);
		break;
	case HAKIM_ATTACK:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 5);
		frameDelay = 0.1f;
		isAttack = true;
		sword->setVisible(true);
		break;
	case HAKIM_RUN:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 7);
		frameDelay = 0.1f;
		isAttack = false;
		sword->setVisible(false);
		break;
	}
}

void HakimItem::RenderBoundingBox(Camera* camera)
{
	Entity::RenderBoundingBox(camera);
	if (sword->getVisible())
		sword->RenderBoundingBox(camera);
}

void HakimItem::draw(COLOR_ARGB color)
{
	Entity::draw(color);
	if (sword->getVisible())
		sword->draw(color);
}
