#ifndef _SKELETONITEM_H
#define _SKELETONITEM_H

#include "Entity.h"
#include "Aladdin.h"
#include "BoneWeapon.h"
#include <time.h>

namespace SkeletonNS {
	const int arrBoneX[] =
	{
		124, 61, -203, 152,
		-159, 201,-80, -111,
		-32, 119,-100,-52,
		220, -190, 151
	};
	const int arrBoneY[] =
	{
		-138, -181, -100, -185,
		100, -162, -198, -183,
		106, 101, -124, 100,
		10, 18, -30
	};
}

class SkeletonItem : public Entity
{
private:
	Aladdin* aladdin;

	bool isBoom;
	std::vector<Entity*> *listWeaponOfEnemy;

public:
	SkeletonItem(float x, float y, Aladdin* aladdin, std::vector<Entity*>* listWeaponOfEnemy);
	~SkeletonItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	void setViewport(D3DXVECTOR2 pos)
	{
		Image::setViewport(pos);
		/*for (int i = 0; i < 10; i++)
		{
			bone[i]->setViewport(pos + D3DXVECTOR2(bone[i]->getX() - this->getX(), bone[i]->getY() - this->getY()));
		}*/
	}
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif