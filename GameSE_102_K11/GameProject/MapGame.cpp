#include "MapGame.h"

MapGame::MapGame()
{
	map = new Image();

	ColumnsMap = RowsMap = 0;
	tileWidth = tileHeight = 0;
}

MapGame::~MapGame()
{
	safeDelete(map);
}

void MapGame::LoadMap(eType type)
{
	switch (type)
	{
	case eType::MAP_SULTAN:
		ReadMapJSON(SULTAN_TILEMAP);
		map->setTextureManager(TextureManager::getIntance()->getTexture(eType::MAP_SULTAN));
		break;
	}
}

void MapGame::ReadMapJSON(std::string filename)
{
	std::ifstream ifs(filename);
	Json::Reader reader;
	Json::Value root;
	reader.parse(ifs, root);

	const Json::Value& infoMap = root["map"];
	ColumnsMap		= infoMap["_cols"].asInt();
	RowsMap			= infoMap["_rows"].asInt();
	tileWidth		= infoMap["_tilewidth"].asInt();
	tileHeight		= infoMap["_tileheight"].asInt();
	bankMapWidth	= infoMap["_width"].asInt();
	bankMapHeight	= infoMap["_height"].asInt();
	const Json::Value& dataMap = infoMap["data"];

	for (int i=0;i<RowsMap;i++){
		for (int j = 0; j < ColumnsMap; j++) {
			tileMap[i][j] = dataMap[i * ColumnsMap + j].asInt();
		}
	}
	ifs.close();
}

void MapGame::Render(Camera* camera)
{
	int col = (int)(camera->getXCamera() / tileWidth);
	int row = (int)(camera->getYCamera() / tileHeight);

	float xViewPort = -(float)((int)camera->getXCamera() % tileWidth);
	float YViewPort = -(float)((int)camera->getYCamera() % tileHeight);
	for (UINT i = 0; i < GAME_HEIGHT / tileHeight + 1; i++) {
		for (UINT j = 0; j < GAME_WIDTH / tileWidth + 1; j++) {
			if (!(row + i < 0 || row + i >= RowsMap || j + col < 0 || j + col >= ColumnsMap))
			{
				map->setCurrentFrame(tileMap[row + i][col + j] - 1);
				map->setXViewport(j * tileWidth + xViewPort);
				map->setYViewport(i * tileHeight + YViewPort);
				map->draw();
			}
		}
	}
}
