#include "Sound.h"
#include "PFMem.h"
#include "PFAsset.h"
#include <stdio.h>

static PF_MEMMARKER soundDataStart = 0;
static pf_sound** soundList = 0;

void snd_loadInit()
{
	soundDataStart = pf_memMark();
	soundList = pf_memAlloc("PF_SoundSys_List", sizeof(pf_sound) * NUM_SOUNDS);

	for (int i = 0; i < NUM_SOUNDS; i++) 
	{
		unsigned char out[16];
		sprintf_s(out, 16, "SOUND - %03X", i);
		soundList[i] = ph_nextSound(out);
	}
}

int snd_isInit(sound_system_t** soundSys)
{
	return (soundSys && *soundSys && (*soundSys)->isInit == SND_INIT);		
}

void playSound(int id) 
{

}

void stopSound(int id)
{

}

void playMusic(int trackNum)
{

}

void stopMusic()
{

}

void playCD(int trackNum)
{

}

void stopCD()
{

}

void snd_init(sound_system_t** soundSys)
{
	PF_MEMMARKER mrk = pf_memMark();
	*soundSys = pf_memAlloc("PF_SoundSys", sizeof(soundSys));
	memset(*soundSys, 0, sizeof(sound_system_t));

	(*soundSys)->soundSysMarker = mrk;
	(*soundSys)->numSounds = NUM_SOUNDS;

	(*soundSys)->playSound = playSound;
	(*soundSys)->stopSound = stopSound;
	(*soundSys)->playMusic = playMusic;
	(*soundSys)->stopMusic = stopMusic;
	(*soundSys)->playCD = playCD;
	(*soundSys)->stopCD = stopCD;

	(*soundSys)->isInit = SND_INIT;
}