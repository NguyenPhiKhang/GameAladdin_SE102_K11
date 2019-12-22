#ifndef _HAKIMITEM_H
#define _HAKIMITEM_H

#include "Entity.h"
#include "Aladdin.h"
#include "SwordWeapon.h"
#include "Audio.h"

class HakimItem : public Entity
{
private:
	Aladdin* aladdin;
	bool isHurt;
	bool isAttack;

	SwordWeapon* sword;
public:
	HakimItem(float x, float y, Aladdin* aladdin);
	~HakimItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
	void RenderBoundingBox(Camera* camera);
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	SwordWeapon* getSword() { return sword; }
};

#endif