#include "HUD_Info.h"

HUD_Info::HUD_Info()
{
	healthMeter = new Image();
	iconApple = new Image();
	iconChance = new Image();
	iconGem = new Image();
	fontTotal = new Text();
	fontScore = new Text();

	//ShowIconApple = true;
	countShowApple = 0;
	countShowHealth = 0;
}

HUD_Info::~HUD_Info()
{
	safeDelete(healthMeter);
	safeDelete(iconApple);
	safeDelete(iconChance);
	safeDelete(iconGem);
	safeDelete(fontScore);
	safeDelete(fontTotal);
}

void HUD_Info::update(float frameTime)
{
	healthMeter->update(frameTime);
	iconApple->update(frameTime);
	iconChance->update(frameTime);
	iconGem->update(frameTime);
}

void HUD_Info::initialize(std::string fonttotal, std::string fontscore)
{
	healthMeter->setTextureManager(TextureManager::getIntance()->getTexture(eType::HEALTH_METER));
	iconGem->setTextureManager(TextureManager::getIntance()->getTexture(eType::ICON_GEM));
	iconChance->setTextureManager(TextureManager::getIntance()->getTexture(eType::ICON_CHANCE));
	iconApple->setTextureManager(TextureManager::getIntance()->getTexture(eType::ICON_APPLE));
	fontTotal->initialize(fonttotal, FONT_TOTAL);
	fontScore->initialize(fontscore, FONT_SCORE);


	healthMeter->setFrames(0, 3);
	healthMeter->setCurrentFrame(0);
	healthMeter->setFrameDelay(0.2f);
	healthMeter->setViewport(D3DXVECTOR2(15.0f, 15.0f));

	iconGem->setScale(1.2f);
	iconGem->setViewport(D3DXVECTOR2((float)(GAME_WIDTH - 100), (float)(GAME_HEIGHT - 40)));
	iconApple->setScale(1.6f);
	iconApple->setViewport(D3DXVECTOR2((float)(GAME_WIDTH - 55), (float)(GAME_HEIGHT - 40)));
	//iconChance->setScale(1.5f);
	iconChance->setViewport(D3DXVECTOR2(15.0f, (float)(GAME_HEIGHT - 45)));
}

void HUD_Info::Render(int totalApple, int totalChance, int totalGem, int totalScore, int health)
{
	fontTotal->setProportional(false);
	fontScore->setProportional(false);
	fontTotal->setBackColor(graphicsNS::TRANSCOLOR);
	fontScore->setBackColor(graphicsNS::TRANSCOLOR);

	int indicatorHealth = health / 10;
	if (healthMeter->getStartFrame() != (10 - indicatorHealth)*4)
	{
		healthMeter->setFrames((10 - indicatorHealth) * 4, ((10-indicatorHealth)!=8)?((10 - indicatorHealth) * 4 + 3):32);
		healthMeter->setCurrentFrame((10 - indicatorHealth) * 4);
	}

	if (health <= 40)
	{
		if (healthMeter->getVisible())
		{
			countShowHealth++;
			healthMeter->draw();
			if (countShowHealth > 10)
			{
				healthMeter->setVisible(false);
				countShowHealth = 0;
			}

		}
		else {
			countShowHealth++;
			if (countShowHealth > 10)
			{
				healthMeter->setVisible(true);
				countShowHealth = 0;
			}
		}
	}
	else {

		healthMeter->setVisible(true);
		healthMeter->draw();
	}

	if (totalGem > 0)
	{
		iconGem->draw();
		fontTotal->setFontHeight(10);
		sprintf_s(textTotalGem, "%d", totalGem);
		fontTotal->print(textTotalGem, (int)(iconGem->getXViewport()+iconGem->getWidth()+ 2), (int)(iconGem->getYViewport() + iconGem->getHeight() - 10));
	}
	if (totalApple > 0)
	{
		if (totalApple < 6)
		{
			if (iconApple->getVisible())
			{
				countShowApple++;
				iconApple->draw();
				if (countShowApple > 10)
				{
					iconApple->setVisible(false);
					countShowApple=0;
				}
				
			}
			else { 
				countShowApple++;
				if (countShowApple > 10)
				{
					iconApple->setVisible(true);
					countShowApple = 0;
				}
			}
		}
		else {
			iconApple->setVisible(true);
			iconApple->draw();
		}
		fontTotal->setFontHeight(10);
		sprintf_s(textTotalApple, "%d", totalApple);
		fontTotal->print(textTotalApple, (int)(iconApple->getXViewport() + iconApple->getWidth() + 2), (int)(iconApple ->getYViewport() + iconApple->getHeight() - 10));
	}


	if (totalChance >= 0)
	{
		iconChance->draw();
		fontTotal->setFontHeight(10);
		sprintf_s(textTotalChance, "%d", totalChance);
		fontTotal->print(textTotalChance, (int)(iconChance->getXViewport() + iconChance->getWidth() + 2), (int)(iconChance->getYViewport() + iconChance->getHeight() - 10));
	}

	if (totalScore > 0)
	{
		fontScore->setFontHeight(32);
		sprintf_s(textTotalScore, "%d", totalScore);
		fontScore->print(textTotalScore, (int)(GAME_WIDTH - 100), (int)(30));
	}
}
