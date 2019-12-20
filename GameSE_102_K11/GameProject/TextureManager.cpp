#include "TextureManager.h"


TextureManager* TextureManager::_instance = NULL;

TextureManager::TextureManager() {
	LoadResources();
}

//=============================================================================
// Destructor
//=============================================================================
TextureManager::~TextureManager()
{
	safeDelete(_instance);
}

//=============================================================================
// 
//=============================================================================
TextureManager* TextureManager::getIntance()
{
	if (!_instance) _instance = new TextureManager();
	return _instance;
}

//=============================================================================
// Add texture into map
//=============================================================================
void TextureManager::addTexture(eType type, LPTEXTURE texture)
{
	textures[type] = texture;
}

//=============================================================================
// Get texture
//=============================================================================
LPTEXTURE TextureManager::getTexture(eType type)
{
	return textures[type];
}

//=============================================================================
// // Load all texture in game
//=============================================================================
void TextureManager::LoadResources()
{
	// maps
	addTexture(eType::MAP_SULTAN, new CTexture(SULTAN_MAP_BANK_TEXTURE, 100, 8, 8));
	addTexture(eType::MAP_JAFAR, new CTexture(JAFAR_MAP_BANK_TEXTURE, 13, 64, 64));
	addTexture(eType::MAP_JAFAR_BACKGROUND, new CTexture(JAFAR_PILLAR_SNAKE));
	addTexture(eType::MAP_SULTAN_FRONT_BG, new CTexture(SULTAN_FRONT_BACKGROUND));

	// aladdin
	addTexture(eType::ALADDIN_IDLE,				new CTexture(ALADDIN_IDLE_TEXTURE, 10, 136, /*79*/110));						// trạng thái đứng yên
	addTexture(eType::ALADDIN_RUN,				new CTexture(ALADDIN_RUN_TEXTURE, 13, 136, /*58*/ 110));						// trạng thái đang chạy
	addTexture(eType::ALADDIN_STOP_INERTIA,		new CTexture(ALADDIN_STOP_TEXTURE, 9, 136, /*70*/110));						// trạng thái dừng có trượt
	addTexture(eType::ALADDIN_ATTACK,			new CTexture(ALADDIN_ATTACK_TEXTURE, 7, 136, /*74*/110));					// trạng thái đang đứng đánh
	addTexture(eType::ALADDIN_THROW,			new CTexture(ALADDIN_THROW_TEXTURE, 7, 136, /*63*/110));						// trạng thái đang ném táo
	addTexture(eType::ALADDIN_GLANCE_UP,		new CTexture(ALADDIN_GLANCE_UP_TEXTURE, 3, 136, /*59*/110));					// trạng thái đang ngước lên
	addTexture(eType::ALADDIN_RUN_ATTACK,		new CTexture(ALADDIN_RUN_ATTACK_TEXTURE, 6, 136, /*60*/110));				// trạng thái vừa chạy vừa đánh
	addTexture(eType::ALADDIN_GLANCE_ATTACK,	new CTexture(ALADDIN_GLANCE_ATTACK_TEXTURE, 10, 136, /*86*/110));			// trạng thái đánh khi đang ngước lên
	addTexture(eType::ALADDIN_JUMP,				new CTexture(ALADDIN_JUMP_TEXTURE, 10, 136, /*93*/110));						// trạng thái nhảy lên
	addTexture(eType::ALADDIN_JUMP_ATTACK,		new CTexture(ALADDIN_JUMP_ATTACK_TEXTURE, 7, 136, 110));						// trạng thái nhảy chém
	addTexture(eType::ALADDIN_RUN_JUMP,			new CTexture(ALADDIN_RUN_JUMP_TEXTURE, 7, 136, 110));						// trạng thái vừa chạy vừa nhảy
	addTexture(eType::ALADDIN_JUMP_THROW, 		new CTexture(ALADDIN_JUMP_THROW_TEXTURE, 7, 136, 110));						// trạng thái nhảy ném táo
	addTexture(eType::ALADDIN_RUN_THROW,		new CTexture(ALADDIN_RUN_THROW_TEXTURE, 6, 136, 110));						// trạng thái vừa chạy vừa ném táo
	addTexture(eType::ALADDIN_SIT,				new CTexture(ALADDIN_SIT_TEXTURE, 4, 136, 110));							// trạng thái ngồi
	addTexture(eType::ALADDIN_SIT_ATTACK,		new CTexture(ALADDIN_SIT_ATTACK_TEXTURE, 7, 136, 110));						// trạng thái ngồi chém
	addTexture(eType::ALADDIN_SIT_THROW,		new CTexture(ALADDIN_SIT_THROW_TEXTURE, 7, 136, 110));						// trạng thái ngồi ném táo
	addTexture(eType::ALADDIN_PUSH,				new CTexture(ALADDIN_PUSH_TEXTURE, 9, 136, 110));							// trạng thái đẩy
	addTexture(eType::ALADDIN_CLIMB,			new CTexture(ALADDIN_CLIMB_TEXTURE, 10, 136, 110));
	addTexture(eType::ALADDIN_CLIMB_ATTACK,		new CTexture(ALADDIN_CLIMB_ATTACK_TEXTURE, 8, 136, 110));
	addTexture(eType::ALADDIN_CLIMB_THROW,		new CTexture(ALADDIN_CLIMB_THROW_TEXTURE, 6, 136, 110));
	addTexture(eType::ALADDIN_CLIMB_JUMP,		new CTexture(ALADDIN_CLIMB_JUMP_TEXTURE, 9, 136, 110));
	addTexture(eType::ALADDIN_HURT,				new CTexture(ALADDIN_HURT_TEXTURE, 6, 136, 110));
	addTexture(eType::ALADDIN_TOUCHGROUND,		new CTexture(ALADDIN_TOUCHGROUND_TEXTURE, 16, 136, 110));

	// Enemy Nahbi
	addTexture(eType::NAHBI_RUN,				new CTexture(NAHBI_RUN_TEXTURE, 8, 166, 73));
	addTexture(eType::NAHBI_LEAD,				new CTexture(NAHBI_LEAD_TEXTURE, 6, 166, 73));
	addTexture(eType::NAHBI_STAB,				new CTexture(NAHBI_STAB_TEXTURE, 7, 166, 73));
	addTexture(eType::NAHBI_ATTACK,				new CTexture(NAHBI_ATTACK_TEXTURE, 6, 166, 73));
	addTexture(eType::NAHBI_BEHIT,				new CTexture(NAHBI_BEHIT_TEXTURE, 6, 166, 73));

	// Enemy Hakim
	addTexture(eType::HAKIM_RUN, new CTexture(HAKIM_RUN_TEXTURE, 8, 156, 74));
	addTexture(eType::HAKIM_ATTACK, new CTexture(HAKIM_ATTACK_TEXTURE, 6, 156, 74));
	addTexture(eType::HAKIM_BEHIT, new CTexture(HAKIM_BEHIT_TEXTURE, 9, 156, 74));
	addTexture(eType::HAKIM_IDLE, new CTexture(HAKIM_IDLE_TEXTURE));

	// Enemy Bat
	addTexture(eType::BATS, new CTexture(BAT_TEXTURE, 11, 34, 25));

	// Boss
	addTexture(eType::JAFAR_BOSS, new CTexture(BOSS_JAFAR_TEXTURE, 8, 114, 84));
	addTexture(eType::SNAKE_BOSS, new CTexture(BOSS_SNAKE_TEXTURE, 11, 114, 84));
	addTexture(eType::FIRE_IDLE, new CTexture(FiRE_IDLE_TEXTURE, 5, 35, 53));
	addTexture(eType::FIRE_RUN, new CTexture(FiRE_RUN_TEXTURE, 8, 99, 51));

	// items
	addTexture(eType::APPLES,					new CTexture(APPLEITEM_TEXTURE));
	addTexture(eType::GEMS,						new CTexture(GEMITEM_TEXTURE, 9, 32, 23));
	addTexture(eType::BUTTRESS, new CTexture(BUTTRESSITEM_TEXTURE, 28, 34, 67));
	addTexture(eType::COLUMN1, new CTexture(COLUMN1_OUTITEM_TEXTURE));
	addTexture(eType::COLUMN2, new CTexture(COLUMN2_OUTITEM_TEXTURE));
	addTexture(eType::COLUMN3, new CTexture(COLUMN3_OUTITEM_TEXTURE));
	addTexture(eType::COLUMN4, new CTexture(COLUMN4_OUTITEM_TEXTURE));
	addTexture(eType::EXITS, new CTexture(EXITITEM_TEXTURE));
	addTexture(eType::GENIES, new CTexture(GENIETEM_TEXTURE, 4, 46, 52));
	addTexture(eType::HEART_BALLOON, new CTexture(HEART_BALLOONITEM_TEXTURE, 8, 19, 25));
	addTexture(eType::PODIUM, new CTexture(PODIUMITEM_TEXTURE, 8, 40, 24));

	addTexture(eType::SKELETON, new CTexture(SKELETON_TEXTURE, 22, 112, 103));
	addTexture(eType::SPEAR, new CTexture(SPEARITEM_TEXTURE, 8, 49, 35));
	addTexture(eType::VASE, new CTexture(VASEITEM_TEXTURE, 10, 34, 34));
	addTexture(eType::STALL, new CTexture(STALLITEM_TEXTURE));
	addTexture(eType::PEDDLER, new CTexture(PEDDLERITEM_TEXTURE, 14, 74, 60));

	// Bone
	addTexture(eType::BONE, new CTexture(BONE_TEXTURE, 4, 16, 15));

	// weapon
	addTexture(eType::APPLE_WEAPON, new CTexture(APPLE_WEAPON_TEXTURE, 4, 9, 9));


	//effect
	addTexture(eType::EXPLOSIVE_ITEM, new CTexture(EXPLOSIVE_ITEMS_TEXTURE, 12, 19, 17));
	addTexture(eType::EXPLOSIVE_APPLE_WEAPON, new CTexture(EXPLOSIVE_APPLE_WEAPON_TEXTURE, 5, 31, 27));
	addTexture(eType::EXPLOSIVE_GENIE, new CTexture(EXPLOSIVE_GENIE_TEXTURE, 15, 60, 54));
	addTexture(eType::EXPLOSIVE_ENEMY, new CTexture(EXPLOSIVE_ENEMY_TEXTURE, 10, 88, 55));
	addTexture(eType::EXPLOSIVE_BONE, new CTexture(EXPLOSIVE_BONE_TEXTURE, 4, 35, 21));

	//icon
	addTexture(eType::ICON_APPLE, new CTexture(APPLEITEM_TEXTURE));
	addTexture(eType::ICON_CHANCE, new CTexture(ICON_CHANCE_TEXTURE));
	addTexture(eType::ICON_GEM, new CTexture(ICON_GEM_TEXTURE));
	addTexture(eType::HEALTH_METER, new CTexture(HEALTH_METER_TEXTURE, 4, 120, 32));

	// font
	addTexture(eType::FONT_TOTAL, new CTexture(FONT_TOTAL_TEXTURE, 10, 18, 18));
	addTexture(eType::FONT_SCORE, new CTexture(FONT_SCORE_TEXTURE, 10, 18, 18));

	// bbox
	addTexture(eType::BBOX, new CTexture(BOUNDING_BOX_TEXTURE));
}

