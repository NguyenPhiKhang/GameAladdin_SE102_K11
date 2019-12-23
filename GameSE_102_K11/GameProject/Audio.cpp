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
	AddSound(eAudio::MUSIC_SPEAR, MUSIC_SPEAR_WAV);
	AddSound(eAudio::MUSIC_PODIUM, MUSIC_PODIUM_WAV);
	AddSound(eAudio::MUSIC_SKELETON, MUSIC_SKELETON_WAV);
	AddSound(eAudio::MUSIC_NAHBI_LEAD, MUSIC_NAHBI_LEAD_WAV);
	AddSound(eAudio::MUSIC_NAHBI_ATK, MUSIC_NAHBI_ATK_WAV);
	AddSound(eAudio::MUSIC_ALADDIN_HURT, MUSIC_ALADDIN_HURT_WAV);
	AddSound(eAudio::MUSIC_ALADDIN_PUSH, MUSIC_ALADDIN_PUSH_WAV);
	AddSound(eAudio::MUSIC_APPLE_COLLECT, MUSIC_APPLE_COLLECT_WAV);
	//AddSound(eAudio::MUSIC_ALADDIN_ATK_WALL, MUSIC_ALADDIN_ATK_WALL_WAV);
	AddSound(eAudio::MUSIC_APPLE_SPLAT, MUSIC_APPLE_SPLAT_WAV);
	AddSound(eAudio::MUSIC_NAHBI_BEHIT, MUSIC_NAHBI_BEHIT_WAV);
	AddSound(eAudio::MUSIC_GENIE_WOW, MUSIC_GENIE_WOW_WAV);
	AddSound(eAudio::MUSIC_ALADDIN_THROW, MUSIC_ALADDIN_THROW_WAV);
	AddSound(eAudio::MUSIC_VASE, MUSIC_VASE_WAV);
	AddSound(eAudio::MUSIC_GEM_COLLECT, MUSIC_GEM_COLLECT_WAV);
	AddSound(eAudio::MUSIC_HEART, MUSIC_HEART_WAV);
	AddSound(eAudio::MUSIC_GENIE_SMOKE, MUSIC_GENIE_SMOKE_WAV);
	AddSound(eAudio::MUSIC_ALADDIN_ATK_HIGH, MUSIC_HIGH_SWORD_WAV);
	AddSound(eAudio::MUSIC_ALADDIN_ATK_LOW, MUSIC_LOW_SWORD_WAV);
	AddSound(eAudio::MUSIC_HAKIM_BEHIT, MUSIC_HAKIM_BEHIT_WAV);
	AddSound(eAudio::MUSIC_EXPLOSION_ENEMY, MUSIC_EXPLOSION_ENEMY_WAV);
	AddSound(eAudio::MUSIC_EXIT, MUSIC_EXIT_WAV);
	AddSound(eAudio::MUSIC_JAFAR_BEHIT, MUSIC_JAFAR_BEHIT_WAV);
	AddSound(eAudio::MUSIC_JAFAR_TRACTOR, MUSIC_JAFAR_TRACTOR_WAV);
	//AddSound(eAudio::MUSIC_HEAD_BOP,MUSIC_HEAD_BOP);
	//AddSound(eAudio::MUSIC_ALADDIN_LANDING, MUSIC_ALADDIN_LANDING_WAV);
	AddSound(eAudio::MUSIC_BONE, MUSIC_BONE_WAV);
	AddSound(eAudio::MUSIC_SELECTOR, MUSIC_MENU_SELECT_WAV);
	AddSound(eAudio::MUSIC_CHANGE, MUSIC_MUNU_CHANGE_WAV);
	AddSound(eAudio::MUSIC_MENU, MUSIC_MENU_WAV);
	AddSound(eAudio::MUSIC_INTRO, MUSIC_INTRO_WAV);
	AddSound(eAudio::MUSIC_ABU_FAN, MUSIC_ABU_FAN_WAV);
	AddSound(eAudio::MUSIC_BOOM_HUG, MUSIC_BOOM_HUG_WAV);
	AddSound(eAudio::MUSIC_BOXING_BELL, MUSIC_BOXING_WAV);
	AddSound(eAudio::MUSIC_JAFAR_LAUGH, MUSIC_JAFAR_LAUGH_WAV);
	AddSound(eAudio::MUSIC_FIRE_IDLE,MUSIC_FIRE_IDLE_WAV);
	AddSound(eAudio::MUSIC_FIRE_RUN, MUSIC_FIRE_RUN_WAV);
	AddSound(eAudio::MUSIC_REVIVAL, MUSIC_REVIVAL_WAV);
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