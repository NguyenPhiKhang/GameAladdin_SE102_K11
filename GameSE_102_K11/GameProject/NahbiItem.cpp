#include "NahbiItem.h"

NahbiItem::NahbiItem(float x, float y, Aladdin* aladdin)
{
	spriteData.x = x - 66;
	spriteData.y = y + 2;
	type = eType::NAHBI;
	kind = eKind::ENEMY;
	this->aladdin = aladdin;
	//velocity.y = 10;
	isAttack = false;
	isHurt = false;
	sword = new SwordWeapon(this);
	firstX = spriteData.x;
	firstY = spriteData.y;
}

NahbiItem::~NahbiItem()
{
	safeDelete(sword);
}

void NahbiItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (health == 0.0f && state == EXPLOSIVE_ENEMY)
	{
		if (currentFrame == 9)
			visible = false;
	}
	else {
		/*deltaV.y = GRAVITY_JUMP_SPEED * frameTime;

		#pragma region Xu li va cham Ground
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		std::vector<Entity*> list_floor;
		list_floor.clear();

		for (UINT i = 0; i < listObj->size(); i++)
			if (listObj->at(i)->getKind() == eKind::FLOOR)
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
#pragma endregion*/

		float lA, tA, bA, rA;
		aladdin->getBoundingBox(lA, tA, rA, bA);
		float lE, tE, bE, rE;
		getBoundingBox(lE, tE, rE, bE);


		if (!isHurt)
		{
			if (((tE - bA) > 2 || (bE - tA) < -10) && state != NAHBI_LEAD)
			{
				setState(NAHBI_LEAD);
			}

			if ((lA - lE) <= 0)
			{
				if (spriteData.flipHorizontal == false)
					spriteData.flipHorizontal = true;
				if (((rA - lE) >= -80) && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					if (!isAttack)
					{
						setState(NAHBI_ATTACK);
					}
				}
				else if ((lA - rE) < -80 && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					spriteData.x += -100 * frameTime;
					setLimit();
					if (spriteData.x + 73 < LimitLeft)
						spriteData.x = LimitLeft - 73;
					if ((lA - rE) < -80 && spriteData.x == LimitLeft - 73)
					{
						if (state != NAHBI_LEAD)
							setState(NAHBI_LEAD);
					}
					else {
						if (state != NAHBI_RUN)
							setState(NAHBI_RUN);
					}
					if (lA - (rE - 100 * frameTime) > -80)
						spriteData.x = spriteData.x + (80.0f - (lA - (rE - 100 * frameTime)));

				}
			}
			else {
				if (spriteData.flipHorizontal == true)
					spriteData.flipHorizontal = false;
				if (((lA - rE) <= 80) && !((tE - bA) > 2 || (bE - tA) < -10))
				{
					if (!isAttack)
					{
						setState(NAHBI_ATTACK);
					}
				}
				else {
					if ((lA - rE) > 80 && !((tE - bA) > 2 || (bE - tA) < -10))
					{
						spriteData.x += 100 * frameTime;
						setLimit();
						if (spriteData.x + 93 > LimitRight)
						{
							spriteData.x = LimitRight - 93;
						}
						if ((lA - rE) > 80 && spriteData.x == LimitRight - 93)
						{
							if (state != NAHBI_LEAD)
								setState(NAHBI_LEAD);
						}
						else {
							if (state != NAHBI_RUN)
								setState(NAHBI_RUN);
						}
						if (lA - (rE + 100 * frameTime) < 80)
							spriteData.x = spriteData.x - (80.0f - (lA - (rE + 100 * frameTime)));
					}
				}
			}

			if (isAttack)
			{
				if (state == NAHBI_ATTACK && currentFrame == 5)
					setState(NAHBI_STAB);
				else {
					if (state == NAHBI_STAB && currentFrame == 6)
						setState(NAHBI_ATTACK);
				}
			}
		}
		else {
			if (currentFrame == 5)
				isHurt = false;
		}
		if (sword->getVisible())
		{
			sword->update(listObj, frameTime);
		}
	}
}

void NahbiItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 73;
		right = left + 20;                 //width 28,height 49
		top = spriteData.y + 31;
		bottom = top + 42;
	}
}

void NahbiItem::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case EXPLOSIVE_ENEMY:
	{
		D3DXVECTOR2 centerNahbi = getCenter();
		setCurrentFrame(0);
		health = 0.0f;
		sword->setVisible(false);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 9);
		frameDelay = 0.1f;
		setXY(centerNahbi.x - spriteData.width / 2, centerNahbi.y - spriteData.height / 2);
		return;
	}
	case NAHBI_BEHIT:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 5);
		frameDelay = 0.1f;
		isHurt = true;
		isAttack = false;
		sword->setVisible(false);
		break;
	case NAHBI_LEAD:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 5);
		frameDelay = 0.2f;
		isAttack = false;
		sword->setVisible(false);
		break;
	case NAHBI_ATTACK:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 5);
		frameDelay = 0.1f;
		isAttack = true;
		sword->setVisible(true);
		break;
	case NAHBI_STAB:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 6);
		frameDelay = 0.15f;
		isAttack = true;
		sword->setVisible(true);
		break;
	case NAHBI_RUN:
		setCurrentFrame(0);
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 7);
		frameDelay = 0.15f;
		isAttack = false;
		sword->setVisible(false);
		break;
	}
}

void NahbiItem::RenderBoundingBox(Camera* camera)
{
	Entity::RenderBoundingBox(camera);
	if(sword->getVisible())
		sword->RenderBoundingBox(camera);
}

void NahbiItem::draw(COLOR_ARGB color)
{
	Entity::draw(color);
	if (sword->getVisible())
		sword->draw(color);
}
