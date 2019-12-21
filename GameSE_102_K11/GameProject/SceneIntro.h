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
public:
	SceneIntro();
	~SceneIntro();

	void initialize();
	void update(float frameTime);
	void render();

};

#endif // !_SCENE_GAME_H