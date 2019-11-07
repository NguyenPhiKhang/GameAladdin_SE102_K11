#ifndef _MAP_GAME_H
#define _MAP_GAME_H

#include <JsonCpp/json/json.h>
#include "constants.h"
#include "image.h"
#include <fstream>
#include "textureManager.h"
#include "Camera.h"
#include "Graphics.h"

// for convenience

namespace MapNS {
	const int TEXTURE_SIZE = 8;
	const int TEXTURE_COLS = 100;
	const int MAP_HEIGHT_1 = 1134;
	const int MAP_WIDTH_1 = 2270;
	const int MAX_SPEED_KEYB = 500;
	const float POSX_KEYB = 160.0f;
	const float POSY_KEYB = 120.0f;
}


class MapGame
{
private:
	Image* map;

	int ColumnsMap, RowsMap;
	int tileWidth, tileHeight;
	int bankMapWidth, bankMapHeight;

	int tileMap[142][284];

public:
	MapGame();
	~MapGame();
	bool initialize(Graphics* graphics, TextureManager* texture);
	void ReadMapJSON(std::string filename);
	void Render(Camera* camera);
};

#endif // !1

