#ifndef _SCENE_GAME_H
#define _SCENE_GAME_H

#include "Game.h"
#include "Camera.h"
#include "MapGame.h"
#include "Grid.h"
#include "Aladdin.h"
#include "Ground.h"

class SceneGame: public Game
{
private:
	Camera* camera;
	MapGame* tileMap;
	Grid* grid;

	Aladdin* aladdin;
	Image* pillar_snake; // background của map jafar's palace
	Image* front_hurdle; // front background của map sultan's dungeon

	//Ground* ground;

	std::vector<Entity*> listEntity;

	std::vector<Entity*> listColumns;

	float posX;
	float posY;
	float verticalX;
	float verticalY;

	eType mapCurrent;
	float oldXCam;
	float oldYCam;

public:
	SceneGame();
	~SceneGame();

	void initialize(HWND hwnd);
	void update(float frameTime);
	void render();
	void LoadMap(eType type);
	void ResetObjectMap();

	void setMapCurrent(eType type);

};

#endif // !_SCENE_GAME_H