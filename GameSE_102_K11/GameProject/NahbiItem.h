#ifndef _NAHBIITEM_H
#define _NAHBIITEM_H

#include "Entity.h"
#include "Aladdin.h"
#include "SwordWeapon.h"
#include "Audio.h"

class NahbiItem : public Entity
{
private:
	Aladdin* aladdin;
	bool isAttack;
	bool isHurt;
	SwordWeapon* sword;
	bool isSound;
	int countLead;
	bool isLoop;
	bool isLoopFinish;
public:
	NahbiItem(float x, float y, Aladdin* aladdin);
	~NahbiItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
	void RenderBoundingBox(Camera* camera);
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	SwordWeapon* getSword() { return sword; }
};

#endif