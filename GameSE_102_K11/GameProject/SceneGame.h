#ifndef _SCENE_GAME_H
#define _SCENE_GAME_H

#include "Game.h"
#include "Camera.h"
#include "MapGame.h"
#include "Grid.h"
#include "Aladdin.h"
#include "Ground.h"
#include "HUD_Info.h"
#include "appleWeapon.h"
#include "FireIdle.h"
#include "SceneIntro.h"

class SceneGame: public Game
{
private:
	Camera* camera;
	MapGame* tileMap;
	Grid* grid;

	Aladdin* aladdin;
	Image* pillar_snake; // background của map jafar's palace
	Image* front_hurdle; // front background của map sultan's dungeon

	HUD_Info* hud;

	//Ground* ground;

	std::vector<Entity*> listEnemies;
	std::vector<Entity*> listItems;
	std::vector<Entity*> listOthers;
	std::vector<Entity*> listColumns;
	std::vector<Entity*> listWeaponOfEnemy;


	/*float posX;
	float posY;
	float verticalX;
	float verticalY;*/

	eType mapCurrent;
	float oldXCam;
	float oldYCam;

	int allScore;		// all score ALADDIN
	int allChance;		// tổng số mạng của ALADDIN
	int allGem;			// tổng số Gem

	FireIdle* fire;

	SceneIntro* sceneIntro;

public:
	SceneGame();
	~SceneGame();

	void initialize(HWND hwnd);
	void update(float frameTime);
	void render();
	void LoadMap(eType type, bool isChange = false);
	void ResetObjectMap();

	void setMapCurrent(eType type, bool isChange = false);
	int getMapCurrent() { return mapCurrent; }


	void CheckCollision();
	void CheckCollisionWeapon(std::vector<Entity*> listEnt);
	void CheckCollisionAladdinWithItem();
	void CheckCollisionWithEnemy();
	void CheckCollisionAladdinWithEnemy();
	void CheckCollisionWithPodiumFire();

};

#endif // !_SCENE_GAME_H