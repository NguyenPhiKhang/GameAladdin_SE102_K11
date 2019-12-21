#ifndef _ENUM_H
#define _ENUM_H

#include <d3dx9.h>

// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

enum eType {
	// main character
	// animation idle
	/*ALADDIN					= 100,*/
	ALADDIN_IDLE			= 111,
	ALADDIN_ATTACK			= 112,
	ALADDIN_THROW			= 113,

	// animation run
	ALADDIN_RUN				= 121,
	ALADDIN_STOP_INERTIA	= 122,
	ALADDIN_RUN_ATTACK		= 123,
	ALADDIN_RUN_THROW		= 124,
	ALADDIN_RUN_JUMP		= 125,

	// animation glance up
	ALADDIN_GLANCE_UP		= 131,
	ALADDIN_GLANCE_ATTACK	= 132,

	// animation jump
	ALADDIN_JUMP			= 141,
	ALADDIN_JUMP_ATTACK		= 142,
	ALADDIN_JUMP_THROW		= 143,

	// animation sit
	ALADDIN_SIT				= 151,
	ALADDIN_SIT_ATTACK		= 152,
	ALADDIN_SIT_THROW		= 153,

	// animation push
	ALADDIN_PUSH			= 161,

	// animation climb
	ALADDIN_CLIMB			= 171,
	ALADDIN_CLIMB_ATTACK	= 172,
	ALADDIN_CLIMB_THROW		= 173,
	ALADDIN_CLIMB_JUMP		= 174,

	// animation hurt
	ALADDIN_HURT			= 175,

	// animation touchground
	ALADDIN_TOUCHGROUND		= 176,

	//ground
	GROUND					= 200,
	WOOD					= 220,
	IRON_STEP				= 214,
	PODIUM					= 215,

	// items
	APPLES					= 201,
	GEMS					= 202,
	BARRIERS				= 203,
	BATS					= 204,
	BUTTRESS				= 205,
	CHAINS					= 206,
	COLUMN1					= 207,
	COLUMN2					= 208,
	COLUMN3					= 209,
	COLUMN4					= 210,
	EXITS					= 211,
	GENIES					= 212,
	HEART_BALLOON			= 213,
	SKELETON				= 216,
	BONE					= 2161,
	PILLAR					= 217,
	SPEAR					= 218,
	VASE					= 219,
	STALL					= 221,
	PEDDLER					= 222,

	NAHBI					= 301,
	NAHBI_RUN				= 311,
	NAHBI_LEAD				= 321,
	NAHBI_STAB				= 331,
	NAHBI_ATTACK			= 341,
	NAHBI_BEHIT				= 351,

	HAKIM					= 401,
	HAKIM_RUN				= 411,
	HAKIM_ATTACK			= 421,
	HAKIM_BEHIT				= 431,
	HAKIM_IDLE				= 441,

	// Boss
	JAFAR_BOSS				= 601,
	SNAKE_BOSS				= 602,
	FIRE_IDLE				= 603,
	FIRE_RUN				= 604,
	STAR					= 605,


	// effect
	EXPLOSIVE_ITEM			= 501,
	EXPLOSIVE_ENEMY			= 502,
	EXPLOSIVE_APPLE_WEAPON	= 503,
	EXPLOSIVE_GENIE			= 504,
	EXPLOSIVE_BONE			= 505,

	// maps
	MAP_SULTAN				= 21,
	MAP_SULTAN_FRONT_BG		= 22,
	MAP_JAFAR				= 23,
	MAP_JAFAR_BACKGROUND	= 24,
	MAP_INTRO				= 25,

	BBOX					= 31,

	SWORD_WEAPON			= 41,
	APPLE_WEAPON			= 51,

	HEALTH_METER				= 61,
	ICON_CHANCE				= 71,
	ICON_GEM				= 81,
	ICON_APPLE				= 91,

	// font
	FONT_TOTAL				= 1001,
	FONT_SCORE				= 1002,

	//Intro 
	MENU = 9000,
	SELECTOR = 9001,
};

enum eKind {
	FLOOR = 1001,	// sàn
	ENEMY  = 2001,
	ITEM   = 3001,
	ALADDIN = 4001,
	WALL = 5001,
	COLUMN_OUT = 6001,
};


enum eAudio {
	MUSIC_MAP_SULTAN = 100,
	MUSIC_MAP_JAFAR = 101,
};

namespace graphicsNS
{
	// Some common colors
	// ARGB numbers range from 0 through 255
	// A = Alpha channel (transparency where 255 is opaque)
	// R = Red, G = Green, B = Blue
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // use to specify drawing with colorFilter
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // AND with color to get 25% alpha
	const COLOR_ARGB ALPHA40 = D3DCOLOR_ARGB(102, 255, 255, 255);  // AND with color to get 40% alpha
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // AND with color to get 50% alpha
	const COLOR_ARGB ALPHA75 = D3DCOLOR_ARGB(192, 255, 255, 255);  // AND with color to get 75% alpha
	const COLOR_ARGB ALPHA80 = D3DCOLOR_ARGB(204, 255, 255, 255);  // AND with color to get 80% alpha
	const COLOR_ARGB BACK_COLOR = BLACK;                         // background color of game
	const COLOR_ARGB TRANSCOLOR = MAGENTA;						// transparent color

	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;	// size of key arrays

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	//const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_TEXT = KEYS_DOWN + KEYS_PRESSED + TEXT_IN;
}

namespace textNS
{
	enum Alignment { LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM };
	struct FontData
	{
		UINT left;
		UINT right;
	};
	// Actual font width is 48, font height is 62
	const int FONT_BORDER = 0;      // 1 pixel wide transparent border + visible cell border on right and bottom
	const int FONT_WIDTH = 18;
	const int FONT_HEIGHT = 18;     // font is 62 pixels high
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;
	const int COLUMNS = 10;         // number of columns in font image
	const int ROWS = 1;            // number of rows in font image
	const int FRAMES = 1;           // how many frames of animation (1 = not animated)
	const double ANIM_DELAY = 0.0;  // delay between animation frames
	const int MAX_FONT_HEIGHT = 18;
	const int MIN_CHAR = 0x0030;    // minimum character code
	const int MAX_CHAR = 0x0039;    // maximum character code
	const int PROPORTIONAL_SPACING = 5; // pixels between 1:1 scaled characters
	const int TAB_SIZE = 8;
	const char UNDERLINE = '_';
	const char SOLID = 0x7F;        // solid block used for fill character ASCII $7F
	const int BOLD_SIZE = 4;        // pixel shift for bold display
}

#endif // !_ENUM_H
