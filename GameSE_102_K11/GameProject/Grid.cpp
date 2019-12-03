#include "Grid.h"

Grid::Grid()
{
	cols_gridMap = 0;
}

Grid::~Grid()
{
	for (auto& x : cells)
	{
		for (int i = 0; i < x.second.size(); i++)
			x.second.clear();
	}
	cells.clear();

	allObjects.clear();

}

void Grid::SetFile(std::string str)
{
	filepath = str;
}

void Grid::ReloadGrid()
{

	for (auto& x : cells)
	{
		for (int i = 0; i < x.second.size(); i++)
			x.second.clear();
	}
	cells.clear();
	allObjects.clear();


	int id, type, w, h, n;
	float x, y;

	std::ifstream ifs(filepath);
	Json::Reader reader;
	Json::Value root;
	reader.parse(ifs, root);

	Json::Value mapItem = root["map_grid"];
	n = mapItem.size();

	cols_gridMap = root["cols_grid"].asInt();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < mapItem[i]["array_items"].size(); j++)
		{
			id = mapItem[i]["array_items"][j]["_id"].asInt();
			type = mapItem[i]["array_items"][j]["_type"].asInt();
			x = mapItem[i]["array_items"][j]["_x"].asFloat();
			y = mapItem[i]["array_items"][j]["_y"].asFloat();
			w = mapItem[i]["array_items"][j]["_width"].asInt();
			h = mapItem[i]["array_items"][j]["_height"].asInt();
			//DebugOut("Error id: %d\n", id);
			Entity* ent;
			if (CheckObjectInit(id))
				ent = allObjects[id];
			else { 
				ent = GetNewEntity(id, type, x, y, w, h);
				allObjects[id] = ent;
			}
			ent->setID(id);
			cells[mapItem[i]["id_cell"].asInt()].push_back(ent);
		}
	}
	ifs.close();
	allObjects.clear();

	/*std::ofstream ofs;
	ofs.open("grid_items.txt");
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			if (!cells[i][j].empty())
			{
				ofs << "{\n'id_cells': " << i*29 + j + 1 << ",\n'array_items':[\n";
				for(int x=0;x<cells[i][j].size();x++)
				{
					if(x==cells[i][j].size()-1)
						ofs << "{\n'_id': " << cells[i][j].at(x)->getID() << ",\n'_type': " << cells[i][j].at(x)->getType() << ",\n'_x': " << cells[i][j].at(x)->getX()
						<< ",\n'_y': " << cells[i][j].at(x)->getY() <<",\n'_width': "<< cells[i][j].at(x)->getWidth() <<",\n'_height': " << cells[i][j].at(x)->getHeight()<<"\n}";
					else ofs << "{\n'id': " << cells[i][j].at(x)->getID() << ",\n'type': " << cells[i][j].at(x)->getType() << ",\n'x': " << cells[i][j].at(x)->getX()
						<< ",\n'y': " << cells[i][j].at(x)->getY() << ",\n'_width': "<< cells[i][j].at(x)->getWidth() << ",\n'_height': "<< cells[i][j].at(x)->getHeight()<< "\n},";
				}
				ofs << "\n]\n},";
			}
		}
	}
	ofs.close();*/

}

Entity* Grid::GetNewEntity(int id, int type, float x, float y, int width, int height)
{
	switch (type)
	{
	case GROUND:
	{
		Ground* ground = new Ground(x, y, width, height);
		//ground->setTextureManager(TextureManager::getIntance()->getTexture(eType::BBOX));
		return ground;
	}
	case WOOD:
	{
		WoodItem* wood = new WoodItem(x, y, width, height);
		return wood;
	}
	case IRON_STEP:
	{
		Iron_StepItem* ironStep = new Iron_StepItem(x, y, width, height);
		return ironStep;
	}
	case BARRIERS: 
	{
		BarrierItem* barrier = new BarrierItem(x, y, width, height);
		return barrier;
	}
	case CHAINS:
	{
		ChainItem* chain = new ChainItem(x, y, width, height);
		return chain;
	}
	case PILLAR:
	{
		PillarItem* pillar = new PillarItem(x, y, width, height);
		return pillar;
	}
	case APPLES:
	{
		AppleItem* apple = new AppleItem(x, y);
		apple->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return apple;
	}
	case BALLS:
	{
		BallItem* ball = new BallItem(x, y);
		ball->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		/*(id % 2 == 0) ? ball->setCurrentFrame(0) : ball->setCurrentFrame(4);*/
		ball->setCurrentFrame(0);
		ball->setFrameDelay(0.1f);
		ball->setFrames(0, 8);
		return ball;
	}
	case COLUMN1:
	{
		Column_OutItem* column = new Column_OutItem(x, y, type);
		column->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return column;
	}
	case COLUMN2:
	{
		Column_OutItem* column = new Column_OutItem(x, y, type);
		column->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return column;
	}
	case COLUMN3:
	{
		Column_OutItem* column = new Column_OutItem(x, y, type);
		column->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return column;
	}
	case COLUMN4:
	{
		Column_OutItem* column = new Column_OutItem(x, y, type);
		column->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return column;
	}
	case BUTTRESS:
	{
		ButtressItem* buttress = new ButtressItem(x, y);
		buttress->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		buttress->setFrameDelay(0.08f);
		buttress->setFrames(0, 27);
		(id%2==0)? buttress->setCurrentFrame(0) : buttress->setCurrentFrame(7);
		return buttress;
	}
	case EXITS:
	{
		ExitItem* ent = new ExitItem(x, y);
		ent->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return ent;
	}
	case GENIES:
	{
		GenieItem* genie = new GenieItem(x, y);
		genie->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		genie->setCurrentFrame(0);
		genie->setFrameDelay(0.1f);

		genie->setFrames(0, 3);

		return genie;
	}
	case HEART_BALLOON:
	{
		Heart_BalloonItem* heart = new Heart_BalloonItem(x, y);
		heart->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		heart->setCurrentFrame(0);
		heart->setFrameDelay(0.1f);
		heart->setFrames(0, 7);
		return heart;
	}
	case PODIUM:
	{
		PodiumItem* podium = new PodiumItem(x, y);
		podium->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		podium->setFrameDelay(0.1f);
		(id % 2 == 0) ? podium->setCurrentFrame(0) : podium->setCurrentFrame(4);
		podium->setFrames(0, 7);
		return podium;
	}
	case SKELETON:
	{
		SkeletonItem* ent = new SkeletonItem(x, y);
		ent->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return ent;
	}
	case SPEAR:
	{
		SpearItem* spear = new SpearItem(x, y);
		spear->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		spear->setCurrentFrame(0);
		spear->setFrameDelay(0.2f);
		spear->setFrames(0, 13);
		return spear;
	}
	case VASE:
	{
		VaseItem* vase = new VaseItem(x, y);
		vase->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		vase->setCurrentFrame(0);

		// ban đầu vase ở frame(0) khi bị chém bắt đầu chạy animation
		vase->setFrameDelay(0.1f);
		vase->setFrames(0, 10);

		return vase;
	}
	case STALL:
	{
		StallItem* ent = new StallItem(x, y);
		ent->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return ent;
	}
	case PEDDLER:
	{
		PeddlerItem* peddler = new PeddlerItem(x, y);
		peddler->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		peddler->setCurrentFrame(0);
		peddler->setFrameDelay(0.2f);
		peddler->setFrames(0, 13);
		//khi cheém vào peddler thì show stall

		return peddler;
	}
	case HAKIM:
	{
		HakimItem* ent = new HakimItem(x, y);

		ent->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return ent;
	}
	case NAHBI:
	{
		NahbiItem* ent = new NahbiItem(x, y);
		ent->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		return ent;
	}
	}

	return NULL;
}

void Grid::GetListEntity(std::vector<Entity*>& ListObj, Camera* camera)
{
	std::vector<Entity*> list;
	for (auto i : ListObj)
	{
		list.push_back(i);
	}


	ListObj.clear();

	std::unordered_map<int, Entity*> mapObject;

	int bottom = (int)((camera->getYCamera() + GAME_HEIGHT - 1) / GRID_CELL_HEIGHT);
	int top = (int)((camera->getYCamera() + 1) / GRID_CELL_HEIGHT);

	int left = (int)((camera->getXCamera() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->getXCamera() + GAME_WIDTH - 1) / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (auto k : cells[i * cols_gridMap + j + 1])
			{
				if (mapObject.find(k->getID()) == mapObject.end())
					mapObject[k->getID()] = k;
			}
	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}

	/*for (auto& x : ListObj)
	{
		bool flag = false;
		for (auto y : list)
		{
			if (x->getID() == y->getID())
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
			x->setCurrentFrame(0);
	}*/
}

bool Grid::CheckObjectInit(int id)
{
	if (allObjects.find(id) == allObjects.end())
		return false;
	return true;
}

//void Grid::Insert(int id, int type, float x, float y, int w, int h)
//{
//	int top = (int)(y / GRID_CELL_HEIGHT);
//	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
//	int left = (int)(x / GRID_CELL_WIDTH);
//	int right = (int)((x + w) / GRID_CELL_WIDTH);
//
//	Entity* ent = GetNewEntity(id, type, x, y, w, h);
//	if (ent == NULL)
//		return;
//	ent->setID(id);
//
//	/*for (int i = top; i <= bottom; i++)
//		for (int j = left; j <= right; j++)
//			cells[i][j].push_back(ent);*/
//}