#ifndef _HUD_INFO_H
#define _HUB_INFO_H

#include "Image.h"
#include "Text.h"

class HUD_Info
{
private:
	Image* healthMeter;
	Image* iconChance;
	Image* iconApple;
	Image* iconGem;
	Text* fontTotal;
	Text* fontScore;

	char textTotalApple[10];
	char textTotalChance[10];
	char textTotalGem[10];
	char textTotalScore[10];

	int countShowApple;
	int countShowHealth;

public:
	HUD_Info();
	~HUD_Info();
	void update(float frameTime);
	void initialize(std::string fonttotal, std::string fontscore);
	void Render(int totalApple, int totalChance, int totalGem, int totalScore, int health);
};

#endif