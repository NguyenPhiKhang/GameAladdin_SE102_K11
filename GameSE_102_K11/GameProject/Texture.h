#ifndef _TEXTURE_H       // Prevent multiple definitions if this 
#define _TEXTURE_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "graphics.h"
#include "constants.h"

class CTexture
{
	// TextureManager properties
private:
	UINT				widthFrame;      // width frame of sprite in pixels
	UINT				heightFrame;    // height frame of sprite in pixels
	UINT				cols;
	LPDIRECT3DTEXTURE9	texture;		// pointer to texture
	std::string			filename;		// file texture
	bool				initialized;    // true when successfully initialized
	HRESULT				hr;             // standard return type

public:
	// Constructor
	CTexture();
	CTexture(std::string filetex, int column = 1, int wFrame=0, int hFrame=0);

	// Destructor
	~CTexture();	// Returns a pointer to the texture n
	LPDIRECT3DTEXTURE9 getTexture() const { return texture; }

	// Returns the texture width n
	UINT getWidthFrame() const { return widthFrame; }

	// Return the texture height
	UINT getHeightFrame() const { return heightFrame; }

	UINT getCols() const { return cols; }

	// Initialize the textureManager
	void initialize(std::string filename);

	//// Release resources
	//void onLostDevice();

	//// Restore resourses
	//void onResetDevice();
};

typedef CTexture* LPTEXTURE;
#endif
