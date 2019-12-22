#ifndef _APPLEWEAPON_H
#define _APPLEWEAPON_H

#include "Entity.h"
#include "Aladdin.h"
#include "Camera.h"
#include "Audio.h"


class appleWeapon : public Entity
{
private:
	Entity* ent;
	Camera* camera;
	bool startFly;
	bool isSound;
public:
	appleWeapon(Entity* ent, Camera* camera);
	~appleWeapon();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state, Entity* obj=NULL);
	void CollideWithGround(std::vector<Entity*>* coEntities, float frameTime);
};


#endif // !_APPLEWEAPON_H
