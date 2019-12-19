#pragma once
#ifndef _BONEWEAPON_H
#define _BONEWEAPON_H

#include "Entity.h"

class BoneWeapon : public Entity
{
private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value
public:
	BoneWeapon(float x, float y);
	~BoneWeapon();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif