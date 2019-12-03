#ifndef _MAP_GAME_H
#define _MAP_GAME_H

#include <JsonCpp/json/json.h>
#include "constants.h"
#include "image.h"
#include <fstream>
#include "Camera.h"
#include "Texture.h"

// for convenience

namespace MapNS {
	const int MAP_HEIGHT_SULTAN = 1134;
	const int MAP_WIDTH_SULTAN = 2270;
	const int MAP_HEIGHT_JAFAR = 448;
	const int MAP_WIDTH_JAFAR = 830;
	const int MAX_SPEED_KEYB = 500;
	const int POSX_KEYB = 160;
	const int POSY_KEYB = 120;
}


class MapGame
{
private:
	Image* map;

	int ColumnsMap, RowsMap; 
	int tileWidth, tileHeight; // width & height of map frame
	int bankMapWidth, bankMapHeight;

	int _widthMap;
	int _heightMap;

	int tileMap[142][284];

public:
	MapGame();
	~MapGame();
	void LoadMap(eType type);
	void ReadMapJSON(std::string filename);
	void Render(Camera* camera);

	int getWidthMap() { return _widthMap; }
	int getHeightMap() { return _heightMap; }
	
};

#endif // !1

