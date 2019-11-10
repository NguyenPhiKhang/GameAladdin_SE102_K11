#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <Windows.h>

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// textures images
const char SULTAN_MAP_BANK_TEXTURE[] = "Resources\\Maps\\SultansDungeon\\Sultans_Dungeon_Map_bank.png";
const char APPLEITEM_TEXTURE[] = "Resources\\Items\\AppleItems\\appleItem.png";
const char ALADDIN_IDLE_TEXTURE[] = "Resources\\Aladdin\\IDLE\\animation_aladdin_idle.png";
const char ALADDIN_RUN_TEXTURE[] = "Resources\\Aladdin\\RUN\\animation_aladdin_run.png";

//files json
const char SULTAN_TILEMAP[] = "Resources\\Maps\\SultansDungeon\\tiledMap_SultansDungeon.json";
const char APPLEITEM_POSITION[] = "Resources\\Items\\AppleItems\\appleItem_position.json";

// window
const char CLASS_NAME[] = "ALADDIN";
const char GAME_TITLE[] = "ALADDIN";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 320;				// width of game in pixels
const UINT GAME_HEIGHT = 240;               // height of game in pixels
const UINT GAME_POSX = 50;					// position x of window game
const UINT GAME_POSY = 50;					// position y of window game

// game
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key
const UCHAR ALADDIN_UP_KEY = VK_UP;
const UCHAR ALADDIN_DOWN_KEY = VK_DOWN;
const UCHAR ALADDIN_LEFT_KEY = VK_LEFT;
const UCHAR ALADDIN_RIGHT_KEY = VK_RIGHT;


//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
	if (ptr)
		ptr->onLostDevice();
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
	if (ptr)
		ptr->onResetDevice();
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif