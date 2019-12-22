#include "Audio.h"


Audio* Audio::__Instance = NULL;

Audio::Audio()
{
	
}



void Audio::LoadResourceAudio()
{
	//AddSound(eAudio::soundWhip, L"Resources/sound/usingwhip.wav");
	AddSound(eAudio::MUSIC_MAP_SULTAN, MUSIC_MAP_SULTAN_WAV);
	AddSound(eAudio::MUSIC_MAP_JAFAR, MUSIC_MAP_JAFAR_WAV);
}

bool Audio::isPlaying(eAudio type)
{
	return _ArrAudio[type]->IsSoundPlaying();
}

void Audio::StopAll()
{
	for (auto& x : _ArrAudio)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Audio::AddSound(eAudio type, std::string filename)
{
	CSound* wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut("[Audio] Load Audio that bai. eAudio = %d \n", (int)type);
		return;
	}
	_ArrAudio[type] = wave;
}

void Audio::Play(eAudio type, bool isLoop, LONG lVolume)
{
	_ArrAudio[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Audio::Stop(eAudio type)
{
	_ArrAudio[type]->Stop();
}



void Audio::Init(HWND hwnd)
{
	dsound = new CSoundManager();
	dsound->Initialize(hwnd, DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Audio* Audio::getInstance()
{
	if (__Instance == NULL)
		__Instance = new Audio();
	return __Instance;
}




#pragma region AUDIO_PROGRAMING2D

///*******************************************************************
//* shutdownDirectSound
//* Releases the DirecSound device
//*******************************************************************/
//void Audio::shutdownDirectSound(void)
//{
//	safeRelease(g_pDS);
//}
//
//Audio::Audio()
//{
//	g_pDS = NULL;
//}
//
//Audio::~Audio()
//{
//	shutdownDirectSound();
//}
//
///*******************************************************************
//* initDirectSound
//* Initializes DirectSound
//*******************************************************************/
//bool Audio::initialize(HWND hwnd)
//{
//	HRESULT hr;
//
//	hr = DirectSoundCreate8(NULL, &g_pDS, NULL);
//	if FAILED(hr)
//		return false;
//
//	// Set DirectSound cooperative level 
//	hr = g_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
//	if FAILED(hr)
//		return false;
//
//	return true;
//}
//
///*******************************************************************
//* LoadWaveToSoundBuffer
//* Loads a wave file into a DirectSound Buffer
//*******************************************************************/
//LPDIRECTSOUNDBUFFER Audio::LoadWaveToSoundBuffer(std::string wavFilename)
//{
//	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
//	CWaveFile* wavFile;
//	HRESULT hr;
//
//	wavFile = new CWaveFile();
//	wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ);
//	if (wavFile->GetSize() == 0)
//	{
//		DebugOut("Invalid file!\n");
//		return false;
//	}
//
//	DSBUFFERDESC dsbd;
//	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
//	dsbd.dwSize = sizeof(DSBUFFERDESC);
//	dsbd.dwFlags = 0;
//	dsbd.dwBufferBytes = wavFile->GetSize();
//	dsbd.guid3DAlgorithm = GUID_NULL;
//	dsbd.lpwfxFormat = wavFile->m_pwfx;
//
//	hr = g_pDS->CreateSoundBuffer(&dsbd, &apDSBuffer, NULL);
//	if FAILED(hr)
//	{
//		MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
//		return NULL;
//	}
//
//	VOID* pDSLockedBuffer = NULL; // Pointer to locked buffer memory
//	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
//	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 
//
//	hr = apDSBuffer->Lock(0, wavFile->GetSize(),
//		&pDSLockedBuffer, &dwDSLockedBufferSize,
//		NULL, NULL, 0L);
//	if FAILED(hr)
//		return NULL;
//
//	// Reset the wave file to the beginning 
//	wavFile->ResetFile();
//
//	// Read the wave file
//	hr = wavFile->Read((BYTE*)pDSLockedBuffer,
//		dwDSLockedBufferSize,
//		&dwWavDataRead);
//	// Check to make sure that this was successful
//	if FAILED(hr)
//		return NULL;
//
//	// Check to make sure the wav file is not empty
//	if (dwWavDataRead == 0)
//	{
//		// Wav is blank, so just fill with silence
//		FillMemory((BYTE*)pDSLockedBuffer,
//			dwDSLockedBufferSize,
//			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
//	}
//	else if (dwWavDataRead < dwDSLockedBufferSize)
//	{
//		// Don't repeat the wav file, just fill in silence 
//		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
//			dwDSLockedBufferSize - dwWavDataRead,
//			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
//	}
//
//	// Unlock the buffer, we don't need it anymore.
//	apDSBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);
//
//	// Clean up
//	delete wavFile;
//
//	return apDSBuffer;
//}
//
///*******************************************************************
//* playSound
//* plays a sound currently in a buffer only once
//*******************************************************************/
//void Audio::playSound(LPDIRECTSOUNDBUFFER whichBuffer)
//{
//	whichBuffer->Play(0, 0, 0);
//}
//
///*******************************************************************
//* playSoundLoop
//* plays a sound in a buffer repeatedly
//*******************************************************************/
//void Audio::playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer)
//{
//	whichBuffer->Play(0, 0, DSBPLAY_LOOPING);
//}
//
///*******************************************************************
//* stopSound
//* stops the sound in this buffer from playing
//*******************************************************************/
//void Audio::stopSound(LPDIRECTSOUNDBUFFER whichBuffer)
//{
//	whichBuffer->Stop();
//}
#pragma endregion