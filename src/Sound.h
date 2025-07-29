#ifndef __SOUND_H__
#define __SOUND_H__

#include "PFCommon.h"
#include "PFMem.h"

#define NUM_SOUNDS 138
#define SND_INIT 0x500D

typedef struct sound_system_t {
	unsigned int isInit;

	pf_sound** soundList;
	unsigned int numSounds;

	PF_MEMMARKER soundSysMarker;

	void (*loadData)();
	void (*freeData)();

	void (*playSound)(int);
	void (*stopSound)(int);
	void (*playMusic)(int);
	void (*stopMusic)();
	void (*playCD)(int);
	void (*stopCD)();

}sound_system_t;

void snd_init(sound_system_t** soundSys);
int snd_isInit(sound_system_t** soundSys);

void snd_loadInit();

#endif