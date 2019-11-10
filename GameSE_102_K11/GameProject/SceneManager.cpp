#include "SceneManager.h"

SceneManager* SceneManager::_instance = NULL;


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	if (_instance == NULL)
		_instance = new SceneManager();
	return _instance;
}

void SceneManager::setScene(Game* x)
{
	Game* scene_temp = scene;
	scene = x;
	safeDelete(scene_temp);
}

void SceneManager::initialize(HWND hwnd)
{
	scene->initialize(hwnd);
}

void SceneManager::run(HWND hwnd)
{
	scene->run(hwnd);
}

Game* SceneManager::getScene()
{
	return scene;
}
