#ifndef _AUDIO_H
#define _AUDIO_H

#include "dsutil.h"
#include <string>
#include "debug.h"
#include <unordered_map>
#include "constants.h"
#include "enum.h"
#include "Graphics.h"

class Audio
{
//private:
//	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device
//public:
//	Audio();
//	~Audio();
//	bool initialize(HWND hwnd);
//	void shutdownDirectSound(void);
//	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
//	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
//	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);
//	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);


private:
	std::unordered_map<eAudio, CSound* > _ArrAudio;

public:
	static Audio* __Instance;
	static Audio* getInstance();


	CSoundManager* dsound;

	void Init(HWND hwnd);
	Audio();

	void AddSound(eAudio type, std::string filename);
	void Play(eAudio type, bool isLoop = false, LONG lVolume = 0L);
	void Stop(eAudio type);
	void LoadResourceAudio();

	bool isPlaying(eAudio type);

	void StopAll();
};

#endif