#pragma once

#define PF_MAX_MEM (10 * 1024 * 1024)

//#define PF_GFX_USE_ALPHA
#ifdef PF_GFX_USE_ALPHA
#define PF_GFX_BPP 4
#else
#define PF_GFX_BPP 3
#endif


#define DATA_LOAD_RESULT			int
#define DATA_LOAD_SUCCESS			1
#define DATA_LOAD_OUTOFMEM			-1
#define DATA_LOAD_FILENOTFOUND		-2
#define DATA_LOAD_PACKNOTFOUND		-3

typedef struct pf_font {
	unsigned short frameSize;
	unsigned short frameWidth;
	unsigned short frameHeight;
	unsigned short numFrames;

	unsigned int dataLen;
	unsigned char* data;
}pf_font;

typedef struct pf_sframe {
	unsigned int width;
	unsigned int height;
	unsigned int offsetX;
	unsigned int offsetY;
	
	unsigned int dataLen;
	unsigned char* data;
}pf_sframe;

typedef struct pf_sprite {
	unsigned int numFrames;
	pf_sframe* frames;
}pf_sprite;

typedef struct pf_sound {
	unsigned int dataLen;
	unsigned char* wavData;
}pf_sound;

typedef struct pf_bg {
	unsigned int width;
	unsigned int height;

	unsigned int layoutLen;
	unsigned short* layout;

	unsigned int tilesetLen;
	unsigned int tilesetCount;
	unsigned int tilesetWidth;
	unsigned int tilesetHeight;

	unsigned char* tileset;
}pf_bg;

typedef struct pf_lvl_data {
	unsigned int width;
	unsigned char* data;
}pf_lvl_data;

typedef struct pf_level {
	pf_bg* bgMain;
	pf_bg* bgPax;
	pf_lvl_data* det;
	pf_lvl_data* dt2;
	pf_lvl_data* trg;
	pf_lvl_data* als;
}pf_level;

typedef struct pf_game {
	pf_level level;
	pf_sprite* levelSprites;
	unsigned int numSprites;
	pf_sound* levelSounds;
	unsigned int numSounds;
};

DATA_LOAD_RESULT pf_loadInitData();