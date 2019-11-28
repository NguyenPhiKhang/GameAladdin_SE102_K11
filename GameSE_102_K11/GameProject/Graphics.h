#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include "Constants.h"
#include "debug.h"
#include "enum.h"


// SpriteData: The properties required by Graphics::drawSprite to draw a sprite
struct SpriteData
{
	int					id;				// id of entity to distinguish other entity
	int					width;			// width of sprite in pixels
	int					height;			// height of sprite in pixels
	float				x;				// screen location (top left corner of sprite)
	float				y;
	float				scale;			// <1 smaller, >1 bigger
	float				angle;			// rotation angle in radians
	RECT				rect;			// used to select an image from a larger texture
	bool				flipHorizontal; // true to flip sprite horizontally (mirror)
	bool				flipVertical;   // true to flip sprite vertically
	int					direction;		// direction of sprite
	float				xViewport;		// position of sprite in viewport(camera)
	float				yViewport;
	LPDIRECT3DTEXTURE9  texture;		// pointer to texture
};
//typedef SpriteData* LPSPRITEDATA;

class Graphics
{
private:
	// DirectX pointers and stuff
	static Graphics* _instance;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	LPD3DXSPRITE   spriteHandler;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// other variables
	HRESULT     result;         // standard Windows return codes
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // background color

	// (For internal engine use only. No user serviceable parts inside.)
	// Initialize D3D presentation parameters
	void    initD3Dpp();
	// Constructor
	Graphics();

public:

	// Destructor
	virtual ~Graphics();

	static Graphics* getInstance();

	// Releases direct3d and device3d.
	void    releaseAll();

	// Initialize DirectX graphics
	// Throws GameError on error
	// Pre: hw = handle to window
	//      width = width in pixels
	//      height = height in pixels
	//      fullscreen = true for full screen, false for window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// Load the texture into default D3D memory (normal texture use)
	// For internal engine use only. Use the TextureManager class to load game textures.
	// Pre: filename = name of texture file.
	//      transcolor = transparent color
	// Post: width and height = size of texture
	//       texture points to texture
	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LPDIRECT3DTEXTURE9& texture);

	// Load the texture into system memory (system memory is lockable)
   // Provides direct access to pixel data. Use the TextureManager class to load textures for display.
   // Pre: filename = name of texture file.
   //      transcolor = transparent color
   // Post: width and height = size of texture
   //       texture points to texture
	HRESULT loadTextureSystemMem(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LPDIRECT3DTEXTURE9& texture);

	// Display the offscreen backbuffer to the screen.
	HRESULT showBackbuffer();

	// Checks the adapter to see if it is compatible with the BackBuffer height,
	// width and refresh rate specified in d3dpp. Fills in the pMode structure with
	// the format of the compatible mode, if found.
	// Pre: d3dpp is initialized.
	// Post: Returns true if compatible mode found and pMode structure is filled.
	//       Returns false if no compatible mode found.
	bool    isAdapterCompatible();

	// Draw the sprite described in SpriteData structure.
	// color is optional, it is applied as a filter, WHITE is default (no change).
	// Creates a sprite Begin/End pair.
	// Pre: spriteData.rect defines the portion of spriteData.texture to draw
	//      spriteData.rect.right must be right edge + 1
	//      spriteData.rect.bottom must be bottom edge + 1
	void    drawSprite(const SpriteData& spriteData,           // sprite to draw
		COLOR_ARGB color = graphicsNS::BLUE);      // default to white color filter (no change)

	void	drawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, COLOR_ARGB color_filter);

	// Reset the graphics device.
	HRESULT reset();

	// Toggle, fullscreen or window display mode
	// Pre: All user created D3DPOOL_DEFAULT surfaces are freed.
	// Post: All user surfaces are recreated.
	void    changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	// get functions
	// Return direct3d.
	LPDIRECT3D9   getD3D() { return d3d; }

	// Return device3d.
	LPDIRECT3DDEVICE9 get3Ddevice() { return d3ddev; }

	// Return sprite
	LPD3DXSPRITE  getSpriteHandler() { return spriteHandler; }

	// Return handle to device context (window).
	HDC     getDC() { return GetDC(hwnd); }

	// Test for lost device
	HRESULT getDeviceState();

	// Return fullscreen
	bool    getFullscreen() { return fullscreen; }

	// Set color used to clear screen
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	//=============================================================================
	// Clear backbuffer and BeginScene()
	//=============================================================================
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (d3d == NULL)
			return result;
		// clear backbuffer to backColor, 
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, backColor, 1.0F, 0);
		result = d3ddev->BeginScene();          // begin scene for drawing
		return result;
	}

	//=============================================================================
	// EndScene()
	//=============================================================================
	HRESULT endScene()
	{
		result = E_FAIL;
		if (d3ddev)
			result = d3ddev->EndScene();
		return result;
	}

	//=============================================================================
	// Sprite Begin
	//=============================================================================
	void spriteBegin()
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	}

	//=============================================================================
	// Sprite End
	//=============================================================================
	void spriteEnd()
	{
		spriteHandler->End();
	}

};

#endif