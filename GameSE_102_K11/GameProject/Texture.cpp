#include "Texture.h"

//=============================================================================
// default constructor
//=============================================================================
CTexture::CTexture()
{
	initialized = false;            // set true when successfully initialized
	texture = NULL;
}

//=============================================================================
// constructor width params
//=============================================================================
CTexture::CTexture(std::string fileTexture, int column, int wFrame, int hFrame)
{
	initialize(fileTexture);
	cols = column;
	if (cols > 1)
	{
		widthFrame = wFrame;
		heightFrame = hFrame;
	}
}

//=============================================================================
// destructor
//=============================================================================
CTexture::~CTexture()
{
	safeRelease(texture);
}

//=============================================================================
// Loads the texture file(s) from disk.
// Post: returns true if successful, false if failed
//		 If file is a.txt file it is assumed to contain individual texture
//       file names, one name per line.
//=============================================================================
void CTexture::initialize(std::string filename)
{
	// load texture files
	this->filename = filename;
	hr = Graphics::getInstance()->loadTexture(filename.c_str(), 
		graphicsNS::TRANSCOLOR, widthFrame, heightFrame, texture);
	initialized = true;                    // set true when initialized
}

//=============================================================================
// called when graphics device is lost
//=============================================================================
//void CTexture::onLostDevice()
//{
//	try
//	{
//		if (!initialized)
//			return;
//		safeRelease(texture);
//	}
//	catch (...)
//	{
//		DebugOut("Warning, TextureManager onLostDevice attempted to access an invalid texture.");
//	}
//}
//
////=============================================================================
//// called when graphics device is reset
////=============================================================================
//void CTexture::onResetDevice()
//{
//	if (!initialized)
//		return;
//	// load texture files
//	hr = Graphics::getInstance()->loadTexture(filename.c_str(),
//		graphicsNS::TRANSCOLOR, widthFrame, heightFrame, texture);
//	if (FAILED(hr))
//			safeRelease(texture);
//}