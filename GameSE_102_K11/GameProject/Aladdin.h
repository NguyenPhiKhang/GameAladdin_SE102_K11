#ifndef _ALADDIN_H
#define _ALADDIN_H

#include "Entity.h"
#include "Camera.h"
#include "MapGame.h"
#include "AppleItem.h"
#include "SwordWeapon.h"
#include "appleWeapon.h"


namespace aladdinNS {
	const int ALADDIN_SPEED = 140;
	const int ALADDIN_HEEL	= 13; // mặc định gót chân đến lề là 13px
								  // thường dùng để so sánh chân aladdin trong trường hợp không di chuyển
	const int ALADDIN_JUMP_DISTANCE = 185; // khoảng cách aladdin nhảy được cách chân
	const int ALADDIN_JUMP_SPEED = 330;
	const float GRAVITY_JUMP_SPEED = 700.0f;
}

using namespace aladdinNS;

class Aladdin: public Entity
{
private:
	float marginWhenChangeDirection;	// tự động trừ hay cộng khi đổi hướng
	float marginWhenRun;				// thay đổi lề 2 bên khi đang chạy
	float marginVertical;				// viewport khi nhảy lên/ hay rớt xuống

	int isPressDirectionFirst;			// -1: nhấn trái đầu tiên || 0: không nhấn || 1: nhấn phải đầu tiên

	bool checkDirection;				// kiểm tra aladdin đã ở hướng đó chưa? false: chưa ở hướng đó hướng đó, true: đã ở hướng đó

	bool isSliding;						// kiểm tra có trượt hay k?

	
	bool LoopFinished;					// kiểm tra vòng lặp chém/ ném xong chưa?
	bool LoopAttackGlance;				// kiểm tra vòng lặp chém khi đang ngước lên xong chưa?
	int	 countLoopAttackGlance;			// Đếm chém khi ngước lên đã đủ 2 lần chưa?
	bool JumpFinsihed;					// kiểm tra nhảy tiếp đất hay chưa?

	int _widthOld, _heightOld;
	bool	holdKeyUP;
	bool	holdKeyDown;

	bool	isFalling;
	bool	isPushing;
	bool	isClimbing;
	bool	isHurt;
	bool	isDeath;
	bool	isCompletedLevel;

	float yChain;		// y của dây xích để ngăn chặn đi tiếp
	int	hChain;	// height của dây xích 

	Camera* camera;
	MapGame* mapGame;

	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value

	int totalAppleCollect;

	DWORD colorUntounchable;

	int CountShake;

	Entity* abuFan;
	Entity* abuRun;
	Image* imgCompleted;
public:
	std::vector<Entity*> WeaponApple;
	SwordWeapon* sword;
	
public:
	Aladdin(Camera* camera, MapGame* mapGame);
	Aladdin(float x, float y);
	~Aladdin();

	void update(float frameTime, Game* gamePtr, std::vector<Entity*> *coEntities = NULL);
	void MoveViewport(Camera* camera, bool moveX=true, bool moveY = true);								// thay đổi viewport khi thay đổi hướng nhân vật
	//void ChangePositionState(int skewX=0, int skewY=0, bool isMoveX = false);	//skewX: vị trí X bị lệch của state so với vị trí mặc định
																				//skewY: vị trí Y bị lệch ở bottom texture so với chân																	
																				//isMoveX: có cho phép di chuyển X khi flipHorizontal = true hay k?
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderBoundingBox(Camera* camera);
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	void positionBoundingBox(
		float& left, float& top, float& right, float& bottom,
		float posLeft, float posLeftFlip, float posTop,
		float bbWidth, float bbHeight);

	void setState(int state, float xCenterChain = 0.0f, float yChain = 0.0f, int hChain = 0); // vị trí x của item...nếu cần
	bool isClimbingChain();
	void setIsClimbing(bool climbing) { this->isClimbing = climbing; }

	void CollideWithGround(std::vector<Entity*> *coEntities, float frameTime);
	void CollideWithWall(std::vector<Entity*>* coEntities, float frameTime, Game* gamePtr);
	//void CollideWithEntity(std::vector<Entity*>* coEntities, /*Entity * objEntity,*/ float frameTime);
	bool isCollisionWithItem(Entity* entItem, float frameTime);
	void setHitWall();

	void setAppleCollect(int appleCollect) { this->totalAppleCollect = appleCollect; }
	int getAppleCollect() { return totalAppleCollect; }

	bool getIsDeath() { return isDeath; }
	void setIsDeath(bool is) { this->isDeath = is; }

	bool getIsCompletedLevel() { return isCompletedLevel; }
	void setIsCompletedLevel(bool is) { this->isCompletedLevel = is; }
};

#endif