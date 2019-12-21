#ifndef _STARWEAPON_H
#define _STARWEAPON_H

#include "Entity.h"
#include "TextureManager.h"


class StarWeapon: public Entity
{
private:
	float _gravity;
public:
	StarWeapon(float x, float y);
	~StarWeapon();
	void update(std::vector<Entity*>* listObj, float frameTime);
};

#endif