#include "SwordWeapon.h"

SwordWeapon::SwordWeapon(Entity* ent)
{
	this->ent = ent;
	visible = false;
	type = eType::SWORD_WEAPON;
}

SwordWeapon::~SwordWeapon()
{
}

void SwordWeapon::update(float frameTime)
{
	Entity::update(frameTime);
}

void SwordWeapon::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (ent->getState())
	{
#pragma region ALADDIN
	case ALADDIN_ATTACK:

		if (ent->getCurrentFrame() == 3)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -21, -27, 10, 11);
			else fixBounding(left, top, right, bottom, 25, -27, 10, 11);
		}
		if (ent->getCurrentFrame() == 4)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 18, -22, 47, 62);
			else fixBounding(left, top, right, bottom, -51, -22, 47, 62);
		}

		//else { visible = false; }
		break;
	case ALADDIN_RUN_ATTACK:

		if (ent->getCurrentFrame() == 3)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -13, -13, 28, 10);
			else fixBounding(left, top, right, bottom, -1, -13, 28, 10);
		}
		if (ent->getCurrentFrame() == 4)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 11, -13, 38, 42);
			else fixBounding(left, top, right, bottom, -35, -13, 38, 42);
		}
		break;
	case ALADDIN_JUMP_ATTACK:
		//visible = true;
		if (ent->getCurrentFrame() == 3)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -24, -4, 20, 6);
			else fixBounding(left, top, right, bottom, 18, -4, 20, 6);
		}
		if (ent->getCurrentFrame() == 4)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 12, -14, 52, 60);
			else fixBounding(left, top, right, bottom, -50, -14, 52, 60);
		}
		break;
	case ALADDIN_SIT_ATTACK:
		if (ent->getCurrentFrame() == 3)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 38, 1, 23, 11);
			else fixBounding(left, top, right, bottom, -47, 1, 23, 11);
		}
		if (ent->getCurrentFrame() > 3 && ent->getCurrentFrame() < 6)
		{
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 29, -1, 24, 13);
			else fixBounding(left, top, right, bottom, -39, -1, 24, 13);
		}
		break;
	case ALADDIN_CLIMB_ATTACK:
		switch (ent->getCurrentFrame())
		{
		case 2:
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -4, -43, 56, 43);
			else fixBounding(left, top, right, bottom, -38, -43, 56, 43);
			break;
		case 3:
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -30, 19, 78, 40);
			else fixBounding(left, top, right, bottom, -34, 19, 78, 40);
			break;
		case 4:
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -33, -22, 43, 56);
			else fixBounding(left, top, right, bottom, 4, -22, 43, 56);
			break;
		case 5:
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, 12, -43, 40, 45);
			else fixBounding(left, top, right, bottom, -14, -43, 40, 45);
			break;
		/*case 6:
			ent->getBoundingBox(left, top, right, bottom);
			if (!ent->getDirection())
				fixBounding(left, top, right, bottom, -33, -22, 43, 56);
			else fixBounding(left, top, right, bottom, 4, -22, 43, 56);
			break;*/
		}
		break;
#pragma endregion

	}
}

void SwordWeapon::fixBounding(float& left, float& top, float& right, float& bottom, int addX, int addY, int w, int h)
{
	left = left + addX;
	top = top + addY;
	right = left + w;
	bottom = top + h;
}
