#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H_

#include "Camera.h"
#include "SceneGame.h"
#include "Game.h"

class SceneManager
{
private:
	static SceneManager* _instance;
	Game* scene;

public:
	SceneManager();
	~SceneManager();

	static SceneManager* getInstance();
	void setScene(Game* x);

	void initialize(HWND hwnd);
	void run(HWND hwnd);

	Game* getScene();

};


#endif 