#ifndef _REDINTRO_H
#define _REDINTRO_H

#include "Image.h"
#include "Input.h"
#include "Audio.h"

class RedIntro_Map
{
private:
	Image* imgIntro;

	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value

	bool isFinished;
public:
	RedIntro_Map();
	~RedIntro_Map();

	void LoadIntroMap(int state);
	void update(float frameTime);
	void render();

	bool getIsFinished() { return isFinished; }
	void setIsFinished(bool is) { this->isFinished = is; }
};

#endif