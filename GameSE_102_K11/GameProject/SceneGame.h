#ifndef _SCENE_GAME_H
#define _SCENE_GAME_H

#include "Game.h"
#include "Camera.h"
#include "MapGame.h"
#include "Grid.h"
#include "Aladdin.h"

class SceneGame: public Game
{
private:
	Camera* camera;
	MapGame* tileMap;
	Grid* grid;

	Aladdin* aladdin;

	std::vector<Entity*> listEntity;

	float posX;
	float posY;
	float verticalX;
	float verticalY;
public:
	SceneGame();
	~SceneGame();

	void initialize(HWND hwnd);
	void update(float frameTime);
	void render();
};

#endif // !_SCENE_GAME_H