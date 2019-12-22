<<<<<<< Updated upstream
#ifndef _SCENE_INTRO_H
#define _SCENE_INTRO_H

#include "Game.h"
#include "Image.h"
#include "Graphics.h"
#include "Input.h"

class SceneIntro
{
private:
	Image *Menu;
	Image *Selector;
	//int mapcurrent;

	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value

	float velocityY;

	int selected;
	bool isMoveMap;

	bool isMenu;
	bool isMember;
public:
	SceneIntro();
	~SceneIntro();

	void initialize();
	void update(float frameTime);
	void render();

	int getSelected() { return selected; }
	bool isMoveMainMap() { return isMoveMap; }
	void setIsMoveMainMap(bool is) { this->isMoveMap = is; }
};

=======
#ifndef _SCENE_INTRO_H
#define _SCENE_INTRO_H

#include "Game.h"
#include "Image.h"
#include "Graphics.h"
#include "Input.h"

class SceneIntro
{
private:
	Image *Menu;
	Image *Selector;
	//int mapcurrent;

	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value

	float velocityY;

	int selected;
	bool isMoveMap;

	bool isMenu;
	bool isMember;
public:
	SceneIntro();
	~SceneIntro();

	void initialize();
	void update(float frameTime);
	void render();

	int getSelected() { return selected; }
	bool isMoveMainMap() { return isMoveMap; }
	void setIsMoveMainMap(bool is) { this->isMoveMap = is; }
};

>>>>>>> Stashed changes
#endif // !_SCENE_GAME_H