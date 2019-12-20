#ifndef _BATITEM_H
#define _BATITEM_H

#include "Entity.h"
#include "Aladdin.h"

//namespace batNS{
//	const 
//}

class BatItem : public Entity
{
private:
	Aladdin* aladdin;
	int limitLeft;
	int limitRight;
	float total;
	bool isFlying;
	bool isRotating;
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value
	float A;					// Biên độ
public:
	BatItem(float x, float y, Aladdin* aladdin);
	~BatItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif