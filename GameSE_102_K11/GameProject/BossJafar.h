#ifndef _BOSS_JAFAR_H
#define _BOSS_JAFAR_H

#include "Entity.h"
#include "Aladdin.h"
#include "FireIdle.h"
#include "Camera.h"
#include "FireRun.h"
#include "StarWeapon.h"

class BossJafar: public Entity
{
private:
	Aladdin* aladdin;
	FireIdle* fire1;	// lửa kế bên snake
	FireIdle* fire2;
	bool isSpray;

	std::vector<Entity*>* listWeaponOfEnemy;
public:
	BossJafar(float x, float y, Aladdin* aladdin, std::vector<Entity*>* listWeaponOfEnemy);
	~BossJafar();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
	void setViewport(Camera* camera);
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
};

#endif
