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

	// aladdin
	addTexture(eType::ALADDIN_IDLE, new CTexture(ALADDIN_IDLE_TEXTURE, 39, 62, 79)); // trạng thái đứng yên
	addTexture(eType::ALADDIN_RUN, new CTexture(ALADDIN_RUN_TEXTURE, 13, 55, 58)); // trạng thái đang chạy

	// items
	addTexture(eType::APPLES, new CTexture(APPLEITEM_TEXTURE));
}

