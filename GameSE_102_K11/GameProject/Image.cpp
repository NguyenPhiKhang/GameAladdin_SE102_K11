#include "Image.h"

//=============================================================================
// default constructor
//=============================================================================
Image::Image()
{
	initialized = false;            // set true when successfully initialized
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       // used to select one frame from multi-frame image
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;      // the sprite texture (picture)
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0f;               // default to 1 second per frame of animation
	animTimer = 0.0f;
	visible = true;                 // the image is visible
	loop = true;                    // loop frames
	animComplete = false;
	colorFilter = graphicsNS::WHITE; // WHITE for no change
}

//=============================================================================
// destructor
//=============================================================================
Image::~Image()
{
}

//=============================================================================
// Initialize the Image.
// Post: returns true if successful, false if failed
// pointer to Graphics
// width of Image in pixels  (0 = use full texture width)
// height of Image in pixels (0 = use full texture height)
// number of columns in texture (1 to n) (0 same as 1)
// pointer to TextureManager
//=============================================================================
bool Image::initialize(LPTEXTURE textureM)
{
	try {
		cols = textureM->getCols();

		spriteData.texture = textureM->getTexture();
		spriteData.width = textureM->getWidthFrame();
		spriteData.height = textureM->getHeightFrame();
	
		// configure spriteData.rect to draw currentFrame
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		// right edge + 1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		// bottom edge + 1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...) { return false; }
	initialized = true;                                // successfully initialized
	return true;
}

//=============================================================================
// Draw the image using color as filter
// The color parameter is optional, WHITE is assigned as default in image.h
// The textureN parameter is optional, 0 is default.
// Pre : spriteBegin() is called
// Post: spriteEnd() is called
//=============================================================================
void Image::draw(COLOR_ARGB color)
{
	if (!visible || Graphics::getInstance() == NULL)
		return; 
	if (color == graphicsNS::FILTER)                     // if draw with filter
		Graphics::getInstance()->drawSprite(spriteData, colorFilter);  // use colorFilter
	else
		Graphics::getInstance()->drawSprite(spriteData, color);        // use color as filter
}

//=============================================================================
// Draw this image using the specified SpriteData.
//   The current SpriteData.rect is used to select the texture.
// Pre : spriteBegin() is called
// Post: spriteEnd() is called
//=============================================================================
void Image::draw(SpriteData sd, COLOR_ARGB color)
{
	if (!visible || Graphics::getInstance() == NULL)
		return;
	spriteData.rect = sd.rect;                  // use this Images rect to select texture
	//spriteData.texture = textureManager->getTexture();  // get fresh texture incase onReset() was called

	if (color == graphicsNS::FILTER)             // if draw with filter
		Graphics::getInstance()->drawSprite(sd, colorFilter);  // use colorFilter
	else
		Graphics::getInstance()->drawSprite(sd, color);        // use color as filter
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Image::update(float frameTime)
{
	if (endFrame - startFrame > 0)          // if animated sprite
	{
		animTimer += frameTime;             // total elapsed time
		if (animTimer > frameDelay)
		{
			animTimer = 0.0f;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)            // if looping animation
					currentFrame = startFrame;
				else                        // not looping animation
				{
					currentFrame = startFrame;
					animComplete = true;    // animation complete
				}
			}
			setRect();                      // set spriteData.rect
		}
	}
}

//=============================================================================
// Set the current frame of the image
//=============================================================================
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect();                          // set spriteData.rect
	}
}

//=============================================================================
//  Set spriteData.rect to draw currentFrame
//=============================================================================
inline void Image::setRect()
{
	// configure spriteData.rect to draw currentFrame
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// right edge + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// bottom edge + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}

