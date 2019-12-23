#include "Grid.h"
#include <ctime>

Grid::Grid(std::vector<Entity*> *listWeaponOfEnemy)
{
	cols_gridMap = 0;
	this->listWeaponOfEnemy = listWeaponOfEnemy;
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

void Grid::ReloadGrid(Aladdin* aladdin)
{

	for (auto& x : cells)
	{
		x.second.clear();
	}
	cells.clear();

	for (auto& obj : allObjects)
	{
		safeDelete(obj.second);
	}
	allObjects.clear();
	srand((unsigned)time(NULL));


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
				ent = GetNewEntity(id, type, x, y, w, h, aladdin);
				allObjects[id] = ent;
			}
			ent->setID(id);
			cells[mapItem[i]["id_cell"].asInt()].push_back(ent);
		}
	}
	ifs.close();
	allObjects.clear();
}

Entity* Grid::GetNewEntity(int id, int type, float x, float y, int width, int height, Aladdin* aladdin)
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
	case GEMS:
	{
		GemItem* gem = new GemItem(x, y);
		gem->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		gem->setCurrentFrame(rand() % 9);
		gem->setFrameDelay(0.1f);
		gem->setFrames(0, 8);
		return gem;
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
		buttress->setFrameDelay(0.1f);
		buttress->setFrames(0, 27);
		buttress->setCurrentFrame(rand()%28);
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
		genie->setFrames(0, 0);

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
		SkeletonItem* ent = new SkeletonItem(x, y, aladdin, listWeaponOfEnemy);
		ent->setTextureManager(TextureManager::getIntance()->getTexture(SKELETON));
		//ent->setFrameDelay(0.15f);
		//ent->setState(1000);
		ent->setCurrentFrame(0);

		return ent;
		break;
	}
	case SPEAR:
	{
		SpearItem* spear = new SpearItem(x, y);
		spear->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		(id % 2 == 0) ? spear->setCurrentFrame(4) : spear->setCurrentFrame(0);
		spear->setFrameDelay(0.3f);
		spear->setFrames(0, 7);
		return spear;
	}
	case VASE:
	{
		VaseItem* vase = new VaseItem(x, y);
		vase->setTextureManager(TextureManager::getIntance()->getTexture((eType)type));
		vase->setCurrentFrame(0);
		vase->setFrameDelay(0.1f);
		vase->setFrames(0, 0);

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
		HakimItem* ent = new HakimItem(x, y, aladdin);
		ent->setState(HAKIM_ATTACK);
		ent->setTextureManager(TextureManager::getIntance()->getTexture(HAKIM_ATTACK));
		return ent;
	}
	case NAHBI:
	{
		NahbiItem* ent = new NahbiItem(x, y, aladdin);
		ent->setState(NAHBI_LEAD);
		ent->setTextureManager(TextureManager::getIntance()->getTexture(NAHBI_LEAD));
		ent->setFrames(0, 5);
		ent->setCurrentFrame(0);
		ent->setFrameDelay(0.15f);
		return ent;
	}
	case BATS:
	{
		BatItem* ent = new BatItem(x, y, aladdin);
		ent->setState(BATS);
		ent->setTextureManager(TextureManager::getIntance()->getTexture(BATS));
		return ent;
	}
	case JAFAR_BOSS:
	{
		BossJafar* boss = new BossJafar(x, y, aladdin, listWeaponOfEnemy);
		boss->setState(JAFAR_BOSS);
		boss->setTextureManager(TextureManager::getIntance()->getTexture(JAFAR_BOSS));
		boss->setCurrentFrame(0);
		boss->setFrames(0, 7);
		boss->setFrameDelay(0.1f);
		return boss;
	}
	}

	return NULL;
}

void Grid::GetListEntity(std::vector<Entity*>& ListOthers, std::vector<Entity*>& ListEnemies, std::vector<Entity*>& ListItems, Camera* camera)
{
	listOldEnemy.clear();
	for (auto i : ListEnemies)
	{
		if(i->getType()!=eType::BUTTRESS&&i->getType()!=eType::SPEAR&&i->getType()!=JAFAR_BOSS)
			listOldEnemy.push_back(i);
	}


	ListOthers.clear();
	ListEnemies.clear();
	ListItems.clear();

	std::unordered_map<int, Entity*> mapObject;

	int bottom = (int)((camera->getYCamera() + GAME_HEIGHT - 1) / GRID_CELL_HEIGHT);
	int top = (int)((camera->getYCamera() + 1) / GRID_CELL_HEIGHT);

	int left = (int)((camera->getXCamera() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->getXCamera() + GAME_WIDTH - 1) / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			/*for (auto k : cells[i * cols_gridMap + j + 1])*/
			for(int k=0;k< cells[i * cols_gridMap + j + 1].size();k++)
			{
				//DebugOut("cells[%d].size() = %d\n", i * cols_gridMap + j + 1, cells[i * cols_gridMap + j + 1].size());
				if (cells[i * cols_gridMap + j + 1].at(k)->getHealth() > 0.0f || cells[i * cols_gridMap + j + 1].at(k)->getVisible())
				{
					if (mapObject.find(cells[i * cols_gridMap + j + 1].at(k)->getID()) == mapObject.end())
						mapObject[cells[i * cols_gridMap + j + 1].at(k)->getID()] = cells[i * cols_gridMap + j + 1].at(k);
				}
				else
				{
					cells[i * cols_gridMap + j + 1].erase(cells[i * cols_gridMap + j + 1].begin() + k);
					k--;
				}
			}
	for (auto& x : mapObject)
	{
		switch (x.second->getKind())
		{
		case eKind::ITEM:
			ListItems.push_back(x.second);
			break;
		case eKind::ENEMY:
			ListEnemies.push_back(x.second);
			break;
		default:
			ListOthers.push_back(x.second);
			break;
		}
	}

	for (auto& enemyOld : listOldEnemy)
	{
		bool flag = false;
		for (auto& enemy : ListEnemies)
		{
			if (enemyOld->getID() == enemy->getID())
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			enemyOld->setCurrentFrame(0);
			enemyOld->setXY(enemyOld->getFirstX(), enemyOld->getFirstY());
		}
	}
}

bool Grid::CheckObjectInit(int id)
{
	if (allObjects.find(id) == allObjects.end())
		return false;
	return true;
}