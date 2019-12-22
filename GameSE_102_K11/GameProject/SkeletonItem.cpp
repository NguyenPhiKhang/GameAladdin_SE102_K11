#include "SkeletonItem.h"

SkeletonItem::SkeletonItem(float x, float y, Aladdin* aladdin, std::vector<Entity*>* listWeaponOfEnemy)
{
	spriteData.x = x - 40;
	spriteData.y = y - 17;
	type = eType::SKELETON;
	kind = eKind::ENEMY;
	this->aladdin = aladdin;
	this->listWeaponOfEnemy = listWeaponOfEnemy;
	isBoom = false;
	firstX = spriteData.x;
	firstY = spriteData.y;
	isSound = false;
}

SkeletonItem::~SkeletonItem()
{

}

void SkeletonItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	srand(unsigned(time(NULL)));
	Entity::update(listObj, frameTime);
	if (currentFrame != 20) {
		isSound = false;
	}
	if (health == 0.0f && state == EXPLOSIVE_ENEMY)
	{
		if (currentFrame == 9)
			visible = false;
	}
	else
	{
		float lA, tA, bA, rA;
		aladdin->getBoundingBox(lA, tA, rA, bA);
		float lE, tE, bE, rE;
		getBoundingBox(lE, tE, rE, bE);

		if (tE - bA <= 55 && tA - bE <= 55 && lE - rA <= 150 && lA - rE <= 150 && currentFrame == 0)
		{
			setState(eType::SKELETON);
		}
		else {
			if (currentFrame == 19)
				frameDelay = 0.4f;
			else frameDelay = 0.14f;
			if (currentFrame == 20 && !isSound)
			{
				if (!isBoom)
				{
					isBoom = true;
					Audio::getInstance()->Play(MUSIC_SKELETON);
					isSound = true;
					for (int i = 0; i < 15; i++)
					{
						Entity* bone = new BoneWeapon(getCenterX() - 5, getCenterY() - 10);
						bone->setTextureManager(TextureManager::getIntance()->getTexture(BONE));
						bone->setCurrentFrame(0);
						bone->setFrames(0, 3);
						bone->setFrameDelay(0.05f);
						bone->setVelocity(D3DXVECTOR2((float)SkeletonNS::arrBoneX[i], (float)SkeletonNS::arrBoneY[i]));
						listWeaponOfEnemy->push_back(bone);
					}
				}
				else return;
			}
			
			if (currentFrame == 21)
			{
				visible = false;
				health = 0.0f;
			}
		}
	}
}
void SkeletonItem::draw(COLOR_ARGB color)
{
	Entity::draw();
}

void SkeletonItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		left = spriteData.x + 54;
		right = left + 16;                 //width 28,height 49
		top = spriteData.y + 28;
		bottom = top + 70;
	}
}

void SkeletonItem::setState(int state)
{
	Entity::setState(state);
	switch (state)
	{
	case EXPLOSIVE_ENEMY:
	{
		D3DXVECTOR2 centerSkeleton = getCenter();
		setCurrentFrame(0);
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 9);
		frameDelay = 0.1f;
		setXY(centerSkeleton.x - spriteData.width / 2, centerSkeleton.y - spriteData.height / 2);
		Audio::getInstance()->Play(MUSIC_EXPLOSION_ENEMY);
		return;
	}
	case SKELETON:
		setFrames(0, 21);
		setCurrentFrame(1);
		frameDelay = 0.14f;
		break;
		//}
	}
}
