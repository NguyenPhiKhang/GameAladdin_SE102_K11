#ifndef _SWORDWEAPON_H
#define _SWORDWEAPON_H

#include "Entity.h"

class SwordWeapon: public Entity
{
private:
	Entity* ent;
public:
	SwordWeapon(Entity* ent);
	~SwordWeapon();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void fixBounding(float& left, float& top, float& right, float& bottom,
					int addX, int addY, int w, int h); // fix lại bounding của weapon so với nhân vật
};


#endif // !_SWORDWEAPON_H