#ifndef _GRID_H
#define _GRID_H

#include <fstream>
#include <JsonCpp/json/json.h>
#include <unordered_map>
#include "Entity.h"
#include "Camera.h"
#include "constants.h"
#include "AppleItem.h"
#include "BallItem.h"
#include "BarrierItem.h"
#include "BatItem.h"
#include "ButtressItem.h"
#include "ChainItem.h"
#include "Column_OutItem.h"
#include "ExitItem.h"
#include "GenieItem.h"
#include "Heart_BalloonItem.h"
#include "PodiumItem.h"
#include "SkeletonItem.h"
#include "VaseItem.h"
#include "WoodItem.h"
#include "SpearItem.h"
#include "StallItem.h"
#include "PeddlerItem.h"
#include "NahbiItem.h"
#include "HakimItem.h"
#include "Ground.h"
#include "Iron_StepItem.h"
#include "PillarItem.h"


namespace gridNS {
	const int GRID_CELL_WIDTH = GAME_WIDTH / 4;
	const int GRID_CELL_HEIGHT = GAME_HEIGHT / 4;

	/*const int GRID_CELL_MAX_ROW = 100;
	const int GRID_CELL_MAX_COLUMN = 100;*/
	//const int GRID_CELL_MAX = 500;
}

using namespace gridNS;

class Grid
{
private:
	//std::vector<Entity*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	//std::vector<Entity*> cells[GRID_CELL_MAX];

	std::unordered_map<int, std::vector<Entity*>> cells;
	std::unordered_map<int, Entity*> allObjects;
	std::string filepath;

	int cols_gridMap;

public:
	Grid();
	~Grid();

	void SetFile(std::string str); // Đọc các object từ file
	void ReloadGrid();


	Entity* GetNewEntity(int id, int type, float x, float y, int width, int height);
	//void Insert(int id, int type, float x, float y, int w, int h); //Thêm object vào grid
	void GetListEntity(std::vector<Entity*>& ListObj, Camera* camera);
	bool CheckObjectInit(int id);	// kiểm tra object đã khởi tạo chưa? false: chưa, true: rồi
};

#endif // !_GRID_H