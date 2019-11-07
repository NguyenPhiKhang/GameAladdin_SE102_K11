
#include "game.h"

// The primary class should inherit from Game class

//=============================================================================
// Constructor
//=============================================================================
Game::Game()
{
	// additional initialization is handled in later call to input->initialize()
	paused = false;             // game is not paused
	initialized = false;
	fpsOn = false;
	fps = 0.0f;
}

//=============================================================================
// Destructor
//=============================================================================
Game::~Game()
{
	deleteAll();                // free all reserved memory
	ShowCursor(true);           // show cursor
}

//=============================================================================
// Window message handler
//=============================================================================
LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized)     // do not process messages if not initialized
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);					  //tell Windows to kill this program
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
			Input::getInstance()->keyDown(wParam);
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:        // key up 
			Input::getInstance()->keyUp(wParam);
			return 0;
		case WM_CHAR:                           // character entered
			Input::getInstance()->keyIn(wParam);
			return 0;
		case WM_DEVICECHANGE:                   // check for controller insert
			Input::getInstance()->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);    // let Windows handle it
}

//=============================================================================
// Initializes the game
// throws GameError on error
//=============================================================================
void Game::initialize(HWND hw)
{
	hwnd = hw;                                  // save window handle

	// initialize graphics
	// throws GameError
	Graphics::getInstance()->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);

	// initialize input, do not capture mouse
	Input::getInstance()->initialize(hwnd, false);             // throws GameError

	// attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		DebugOut("Error initializing high resolution timer");

	QueryPerformanceCounter(&timeStart);        // get starting time

	srand((unsigned int)time(NULL));

	initialized = true;
}

//=============================================================================
// Render game items
//=============================================================================
void Game::renderGame()
{
	//start rendering
	if (SUCCEEDED(Graphics::getInstance()->beginScene()))
	{
		render();           // call render() in derived object

		//stop rendering
		Graphics::getInstance()->endScene();
	}
	handleLostGraphicsDevice();

	//display the back buffer on the screen
	Graphics::getInstance()->showBackbuffer();
}

//=============================================================================
// Handle lost graphics device
//=============================================================================
void Game::handleLostGraphicsDevice()
{
	// test for and handle lost device
	hr = Graphics::getInstance()->getDeviceState();
	if (FAILED(hr))                  // if graphics device is not in a valid state
	{
		// if the device is lost and not available for reset
		if (hr == D3DERR_DEVICELOST)
		{
			DebugOut("D3DERR DEVICE LOST");
			Sleep(100);             // yield cpu time (100 mili-seconds)
			return;
		}
		// the device was lost but is now available for reset
		else if (hr == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			hr = Graphics::getInstance()->reset(); // attempt to reset graphics device
			if (FAILED(hr))          // if reset failed
				return;
			resetAll();
		}
		else
			return;                 // other device error
	}
}

//=============================================================================
// Toggle window or fullscreen mode
//=============================================================================
void Game::setDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
	releaseAll();                   // free all user created surfaces
	Graphics::getInstance()->changeDisplayMode(mode);
	resetAll();                     // recreate surfaces
}

//=============================================================================
// Call repeatedly by the main message loop in WinMain
//=============================================================================
void Game::run(HWND hwnd)
{
	//char s[50];
	if (Graphics::getInstance() == NULL)            // if graphics not initialized
		return;

	// calculate elapsed time of last frame, save in frameTime
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// Power saving code, requires winmm.lib
	// if not enough time has elapsed for desired frame rate
	if (frameTime < MIN_FRAME_TIME)
	{
		sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);         // Request 1mS resolution for windows timer
		Sleep(sleepTime);           // release cpu for sleepTime
		timeEndPeriod(1);           // End 1mS timer resolution
		return;
	}

	if (frameTime > 0.0f)
		fps = (fps * 0.99f) + (0.01f / frameTime);  // average fps
	if (frameTime > MAX_FRAME_TIME)     // if frame rate is very slow
		frameTime = MAX_FRAME_TIME;     // limit maximum frameTime
	timeStart = timeEnd;

	// update(), ai(), and collisions() are pure virtual functions.
	// These functions must be provided in the class that inherits from Game.
	if (!paused)                    // if not paused
	{
		update(frameTime);                   // update all game items
		//ai();                       // artificial intelligence
		//collisions();               // handle collisions
		Input::getInstance()->vibrateControllers(frameTime); // handle controller vibration
	}
	renderGame();                   // draw all game items
	Input::getInstance()->readControllers();       // read state of controllers

	// if Alt+Enter toggle fullscreen/window
	if (Input::getInstance()->isKeyDown(ALT_KEY) && Input::getInstance()->wasKeyPressed(ENTER_KEY))
		setDisplayMode(graphicsNS::TOGGLE); // toggle fullscreen/window

	// if Esc key, set window mode 
	if (Input::getInstance()->isKeyDown(ESC_KEY))
		//setDisplayMode(graphicsNS::WINDOW); // set window mode
		exitGame();

	// Clear input
	// Call this after all key checks are done
	Input::getInstance()->clear(inputNS::KEYS_PRESSED);
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Game::releaseAll()
{}

//=============================================================================
// Recreate all surfaces and reset all entities.
//=============================================================================
void Game::resetAll()
{}

//=============================================================================
// Delete all reserved memory
//=============================================================================
void Game::deleteAll()
{
	releaseAll();               // call onLostDevice() for every graphics item
	/*safeDelete(graphics);
	safeDelete(input);*/
	initialized = false;
}

