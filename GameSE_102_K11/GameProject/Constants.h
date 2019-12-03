#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <Windows.h>

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// textures images

//MAP
const char SULTAN_MAP_BANK_TEXTURE[] = "Resources\\Maps\\SultansDungeon\\Sultans_Dungeon_Map_bank.png";
const char SULTAN_FRONT_BACKGROUND[] = "Resources\\Maps\\SultansDungeon\\Front_Background_Map.png";
const char JAFAR_MAP_BANK_TEXTURE[] = "Resources\\Maps\\JafarsPalace\\Jafars_Palace_Map_bank.png";
const char JAFAR_PILLAR_SNAKE[] = "Resources\\Maps\\JafarsPalace\\pillar_snake.png";

//ALADDIN
const char BOUNDING_BOX_TEXTURE[] = "Resources\\bbox.png";
const char APPLEITEM_TEXTURE[] = "Resources\\Items\\AppleItems\\appleItem.png";
const char ALADDIN_IDLE_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_idle.png";
const char ALADDIN_RUN_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_run.png";
const char ALADDIN_STOP_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_stop_inertia.png";
const char ALADDIN_ATTACK_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_attack.png";
const char ALADDIN_THROW_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_throw.png";
const char ALADDIN_GLANCE_UP_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_glance_up.png";
const char ALADDIN_RUN_ATTACK_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_run_attack.png";
const char ALADDIN_GLANCE_ATTACK_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_glance_attack.png";
const char ALADDIN_JUMP_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_jump.png";
const char ALADDIN_JUMP_ATTACK_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_jump_attack.png";
const char ALADDIN_RUN_JUMP_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_run_jump.png";
const char ALADDIN_JUMP_THROW_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_jump_throw.png";
const char ALADDIN_RUN_THROW_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_run_throw.png";
const char ALADDIN_SIT_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_sit.png";
const char ALADDIN_SIT_ATTACK_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_sit_attack.png";
const char ALADDIN_SIT_THROW_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_sit_throw.png";
const char ALADDIN_PUSH_TEXTURE[] = "Resources\\Aladdin\\animation_aladdin_push.png";


// ITEM + ENEMY
const char BALLITEM_TEXTURE[] = "Resources\\Items\\BallItems\\animation_ball.png";
const char BATITEM_TEXTURE[] = "Resources\\Items\\BatItems\\bat.png";
const char BUTTRESSITEM_TEXTURE[] = "Resources\\Items\\ButtressItems\\animation_buttress.png";
const char COLUMN1_OUTITEM_TEXTURE[] = "Resources\\Items\\Column_OutItems\\column1.png";
const char COLUMN2_OUTITEM_TEXTURE[] = "Resources\\Items\\Column_OutItems\\column2.png";
const char COLUMN3_OUTITEM_TEXTURE[] = "Resources\\Items\\Column_OutItems\\column3.png";
const char COLUMN4_OUTITEM_TEXTURE[] = "Resources\\Items\\Column_OutItems\\column4.png";
const char EXITITEM_TEXTURE[] = "Resources\\Items\\ExitItems\\exititem.png";
const char GENIETEM_TEXTURE[] = "Resources\\Items\\GenieItems\\animation_genie.png";
const char HEART_BALLOONITEM_TEXTURE[] = "Resources\\Items\\Heart_BalloonItems\\animation_heart-balloon.png";
const char PODIUMITEM_TEXTURE[] = "Resources\\Items\\PodiumItems\\animation_podium.png";

const char SKELETON_ITEM_TEXTURE[] = "Resources\\Items\\SkeletonItems\\skeleton-right.png";
const char SPEARITEM_TEXTURE[] = "Resources\\Items\\SpearItems\\animation_spear.png";
const char VASEITEM_TEXTURE[] = "Resources\\Items\\VaseItems\\animation_vase.png";
const char STALLITEM_TEXTURE[] = "Resources\\Items\\Stall\\stall.png";
const char PEDDLERITEM_TEXTURE[] = "Resources\\Items\\Peddler\\animation_peddler.png";
const char HAKIMRITEM_TEXTURE[] = "Resources\\Items\\Hakim\\hakim.png";
const char NAHBIITEM_TEXTURE[] = "Resources\\Items\\Nahbi\\nahbi.png";



//files json
const char SULTAN_TILEMAP[] = "Resources\\Maps\\SultansDungeon\\tiledMap_SultansDungeon.json";
const char JAFAR_TILEMAP[] = "Resources\\Maps\\JafarsPalace\\tiledMap_JajarsPalace.json";
const char OBJECT_GRID_MAP_SULTAN[] = "Resources\\Items\\objects_grid_map_sultan.json";
const char OBJECT_GRID_MAP_JAFAR[] = "Resources\\Items\\objects_grid_map_jafar.json";
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
const UCHAR ALADDIN_ATTACK_KEY = 'X';
const UCHAR ALADDIN_THROW_KEY = 'Z';
const UCHAR ALADDIN_JUMP_KEY = 'C';
const UCHAR MAP_SULTAN_KEY = VK_F1;
const UCHAR MAP_JAFAR_KEY = VK_F2;


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