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
void TextureManager::AddTexture(eType type, LPTEXTURE texture)
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

}

