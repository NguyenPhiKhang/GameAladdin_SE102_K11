#ifndef _INPUT_H	// Prevent multiple definitions if this
#define _INPUT_H	// file is included in more than one place

class Input;

#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "debug.h"
#include "enum.h"

// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------


const DWORD MAX_CONTROLLERS = 4; // Maximum number of controllers supported by XInput
struct ControllerState
{
	XINPUT_STATE		state;
	XINPUT_VIBRATION	vibration;
	float				vibrateTimeLeft;    // mSec
	float				vibrateTimeRight;   // mSec
	bool				connected;
};

class Input
{
private:
	static Input* _instance;
	bool keysDown[inputNS::KEYS_ARRAY_LEN];			// true if specified key is down
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];		// true if specified key was pressed
	std::string textIn;								// user entered text
	char charIn;									// last character entered
	bool newLine;									// true on start of new line
	ControllerState controllers[MAX_CONTROLLERS];	// state of controllers

	// Constructor
	Input();
public:

	static Input* getInstance();

	// Destructor
	~Input();

	// initialize input
	void initialize(HWND, bool);

	// Save key down state
	void keyDown(WPARAM);

	// Save key up state
	void keyUp(WPARAM);

	// Save the char just entered in textIn string
	void keyIn(WPARAM);

	// Returns true if the specified VIRTUAL KEY is down, otherwise false.
	bool isKeyDown(UCHAR vkey) const;

	// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool wasKeyPressed(UCHAR vkey) const;

	// Return true if any key was pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool anyKeyPressed() const;

	// Clear the specified key press
	void clearKeyPress(UCHAR vkey);

	// Clear specified input buffers where what is any combination of
	// KEYS_DOWN, KEYS_PRESSED, MOUSE, TEXT_IN or KEYS_MOUSE_TEXT.
	// Use OR '|' operator to combine parmeters.
	void clear(UCHAR what);

	// Clears key, mouse and text input data
	void clearAll() { clear(inputNS::KEYS_TEXT); }

	// Clear text input buffer
	void clearTextIn() { textIn.clear(); }

	// Return text input as a string
	std::string getTextIn() { return textIn; }

	// Return last character entered
	char getCharIn() { return charIn; }

	// Update connection status of game controllers.
	void checkControllers();

	// Save input from connected game controllers.
	void readControllers();

	// Return state of specified game controller.
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}

	// Vibrates the connected controllers for the desired time.
	void vibrateControllers(float frameTime);
};


#endif