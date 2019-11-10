#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "Texture.h"
#include <unordered_map>
#include <string>
#include "Constants.h"
#include "enum.h"

class TextureManager
{
private:
	static TextureManager* _instance;
	std::unordered_map<eType, LPTEXTURE> textures;
	TextureManager();
public:
	~TextureManager();
	static TextureManager* getIntance();
	void addTexture(eType type, LPTEXTURE texture);
	LPTEXTURE getTexture(eType type);

	// Load all texture in game
	void LoadResources();
};


#endif 