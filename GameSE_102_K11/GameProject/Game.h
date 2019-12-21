#ifndef _GAME_H
#define _GAME_H

#include <Windows.h>
#include <time.h>
#include <string>
#include "Graphics.h"
#include "Constants.h"
#include "Input.h"
#include "Audio.h"

class Game
{
protected:
	Audio* audio;
	Input* input;
	HWND    hwnd;               // window handle
	HRESULT hr;                 // standard return type
	LARGE_INTEGER timeStart;    // Performance Counter start value
	LARGE_INTEGER timeEnd;      // Performance Counter end value
	LARGE_INTEGER timerFreq;    // Performance Counter frequency
	float   frameTime;          // time required for last frame
	float   fps;                // frames per second
	bool fpsOn;					// true to display fps
	DWORD   sleepTime;          // number of milli-seconds to sleep between frames
	bool    paused;             // true if game is paused
	bool    initialized;

	//bool	checkKeyDown;		
	bool	isPress;			// check key state down ( up, down, right, left, x, z, c)

	int		CountKeyAttack;		// don't allow attack when hold key
	int		CountKeyThrow;		// don't allow throw when hold key
	int		CountKeyJump;		// don't allow jump when hold key
	float	sumTimeKeyUp;		
	float	sumTimeKeyDown;

	bool	isDebugRenderBBox;
	bool	isKeyUpApple;
	bool	isKeyUPHealth;
	
public:
	// Constructor
	Game();
	// Destructor
	virtual ~Game();

	// Member functions

	// Window message handler
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Initialize the game
	// Pre: hwnd is handle to window
	virtual void initialize(HWND hwnd);

	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND);

	// Call when the graphics device was lost.
	// Release all reserved video memory so graphics device may be reset.
	virtual void releaseAll();

	// Recreate all surfaces and reset all entities.
	virtual void resetAll();

	// Delete all reserved memory.
	virtual void deleteAll();

	// Render game items.
	virtual void renderGame();

	// Handle lost graphics device
	virtual void handleLostGraphicsDevice();

	// Set display mode (fullscreen, window or toggle)
	void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	// Exit the game
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	// Pure virtual function declarations
	// These functions MUST be written in any class that inherits from Game

	// Update game items.
	virtual void update(float frametime) = 0;

	LARGE_INTEGER getTimeFreq() { return timerFreq; }

	// Perform AI calculations.
	//virtual void ai() = 0;

	// Check for collisions.
	//virtual void collisions() = 0;

	// Render graphics.
	// Call graphics->spriteBegin();
	//   draw sprites
	// Call graphics->spriteEnd();
	//   draw non-sprites
	virtual void render() = 0;

	// set key press is true if isPress true
	void setIsPress(bool isPress) { this->isPress = isPress; };
	// return true if has any key down satisfy key states
	bool getIsPress() { return isPress; }
	// return count Key attack
	int getCountKeyAttack() { return CountKeyAttack; }
	// return count key throw
	int getCountKeyThrow() { return CountKeyThrow; }
	//return count key jump
	int getCountKeyJump() { return CountKeyJump; }
	//
	float getSumTimeKeyUp() { return sumTimeKeyUp; }
	//
	float getSumTimeKeyDown() { return sumTimeKeyDown; }

	virtual void setMapCurrent(eType type, bool isChange=false) = 0;
};

#endif