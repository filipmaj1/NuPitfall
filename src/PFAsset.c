#include "sys_file.h"

#include "PFAsset.h"
#include "PFCommon.h"
#include "PFMem.h"

#include <string.h>

/*
* Asset loaders for the various Pitfall filetypes.
* PH: Linear file bundle containing a list of files.
* PCS: Font file containing a font tilemap.
* PC: Sprite file containing a list of sprite frames.
* BG: Background file, stores data as a tilemap and is used to render both the background and foreground layers.
* DET: Collision map file used to define the points where the entities can stand. Pure Y/X data.
* DT2: Path file for things like ziplines and slides. Pure Y/X data.
* TRG: Collision map for various trigger points like ziplines, damage spikes, hollow trunks, and slides.
* ALS: Actor List (Alien List?) file defining all entity positions.
* WAV: Standard sound wave file.
*/

static PF_FILE* phFileHandle;
static char phFilePath[128];

typedef struct pcs_header_t {
	unsigned int signature;
	unsigned int paletteOffset;

	unsigned short numColors;
	unsigned short frameSize;
	unsigned short frameWidth;
	unsigned short frameHeight;
} pcs_header_t;

typedef struct pc_header_t {
	unsigned int signature;
	unsigned int paletteOffset;
	unsigned short numColors;
	unsigned short numFrames;
} pc_header_t;

typedef struct pc_frameHeader_t {
	unsigned int width;
	unsigned int height;
	unsigned int offsetX;
	unsigned int offsetY;
} pc_frameHeader_t;

typedef struct bg_header_t {
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int tileMapOffset;
	unsigned int paletteOffset;
	unsigned int numColors;
} bg_header_t;

void skipFile();
int loadFilePH(void** tempBuff);
int loadFileLocal(const char* name, void** tempBuff);

// Open a PH file. This is a simple sequence of files, so the order is
// extremly important!!! Must follow a ph_close() once complete.
// Param: phName - The name of the ph file to open in the assets folder.
void ph_open(const char* phName)
{
	sprintf_s(phFilePath, 128, "./assets/%s.ph", phName);
	phFileHandle = sys_openFile(phFilePath, PF_FILE_READ);

	if (phFileHandle == -1)
	{
		phFileHandle = 0;
		return 0;
	}
}

// Load font from PH file; converts it from indexed to RGB/A bitmap.
// Param: name - Filename for memory debugging purposes.
pf_font* ph_nextFont(const char* name)
{
	int fileSizeResult;
	unsigned char* tempBuff = 0;
	pcs_header_t* fontHeader = 0;
	pf_font* font = 0;
	unsigned int gfxDataSize;
	unsigned char colorIndex;
	PF_MEMMARKER backup;

	// Load local if possible, otherwise load from the PF file
	fileSizeResult = loadFileLocal(name, &tempBuff);
	if (fileSizeResult < 0)
		fileSizeResult = loadFilePH(&tempBuff);
	
	if (fileSizeResult >= 0 && tempBuff != 0)
	{
		// Sig Check
		fontHeader = (pcs_header_t*)tempBuff;
		if (fontHeader->signature != 0x34561234)
		{
			pf_memClearScratch();
			return 0;
		}

		// Setup font obj
		gfxDataSize = (fontHeader->paletteOffset - 0x10);
		backup = pf_memMark();
		font = pf_memAlloc(name, sizeof(pf_font) + (PF_GFX_BPP * gfxDataSize));
		font->frameSize = fontHeader->frameSize;
		font->frameWidth = fontHeader->frameWidth;
		font->frameHeight = fontHeader->frameHeight;
		font->numFrames = gfxDataSize / font->frameSize;
		font->dataLen = (PF_GFX_BPP * gfxDataSize);
		font->data = font + 1;

		// Convert from indexed palette to RGBA
		for (int i = 0; i < (fontHeader->paletteOffset - 0x10); i++)
		{
			colorIndex = tempBuff[0x10 + i];

			// Something is wrong; gtfo.
			if (colorIndex > fontHeader->numColors)
			{
				pf_memFree(backup);
				break;
			}

			if (colorIndex == 0)
			{
				font->data[(i * PF_GFX_BPP)] = 0;
				font->data[(i * PF_GFX_BPP) + 1] = 0;
				font->data[(i * PF_GFX_BPP) + 2] = 0;
#ifdef PF_GFX_USE_ALPHA
				font->data[(i * PF_GFX_BPP) + 3] = 0;
#endif
			}
			else 
			{
				colorIndex--;
				font->data[(i * PF_GFX_BPP)] = tempBuff[fontHeader->paletteOffset + (colorIndex * 3)];
				font->data[(i * PF_GFX_BPP) + 1] = tempBuff[fontHeader->paletteOffset + (colorIndex * 3) + 1];
				font->data[(i * PF_GFX_BPP) + 2] = tempBuff[fontHeader->paletteOffset + (colorIndex * 3) + 2];
#ifdef PF_GFX_USE_ALPHA
				font->data[(i * PF_GFX_BPP) + 3] = 0xFF;
#endif
			}
		}
	}
	pf_memClearScratch();

	return font;
}

// Load sprite from PH file; converts it from RLE indexed to RGB/A bitmap.
// Param: name - Filename for memory debugging purposes.
pf_sprite* ph_nextSprite(const char* name)
{
	int fileSizeResult;
	unsigned char* tempBuff = 0;
	pc_header_t* spriteHeader = 0;
	unsigned char* paletteOffsetTable = 0;
	unsigned int* frameOffsetTable = 0;
	pc_frameHeader_t* frameHeader = 0;

	int memSize = 0;
	unsigned char colorIndex;
	PF_MEMMARKER backup;
	unsigned char* dataScanner = 0;

	pf_sprite* sprite = 0;
	pf_sframe* frame;
	unsigned char* frameData = 0;
	int dstPixelCounter;
	int rowTracker;

	// Load local if possible, otherwise load from the PF file
	fileSizeResult = loadFileLocal(name, &tempBuff);
	if (fileSizeResult < 0)
		fileSizeResult = loadFilePH(&tempBuff);

	if (fileSizeResult >= 0 && tempBuff != 0)
	{
		// Sig Check
		spriteHeader = (pc_header_t*)tempBuff;
		if (spriteHeader->signature != 0x34561234)
		{
			pf_memClearScratch();
			return -1;
		}

		frameOffsetTable = tempBuff + sizeof(pc_header_t);
		paletteOffsetTable = tempBuff + spriteHeader->paletteOffset;

		// Integrity Check
		if (spriteHeader->paletteOffset + (3 * spriteHeader->numColors) > fileSizeResult)
		{
			pf_memClearScratch();
			return -2;
		}

		// Allocate sprite
		backup = pf_memMark();
		sprite = pf_memAlloc(name, sizeof(pf_sprite));

		if (sprite == 0)
		{
			pf_memClearScratch();
			pf_memFree(backup);
			return -3;
		}

		sprite->numFrames = spriteHeader->numFrames;
		sprite->frames = pf_memAllocMore(spriteHeader->numFrames * sizeof(pf_sframe));

		if (sprite->frames == 0)
		{
			pf_memClearScratch();
			pf_memFree(backup);
			return -4;
		}

		// Load in frames
		for (int i = 0; i < spriteHeader->numFrames; i++)
		{
			frameHeader = tempBuff + frameOffsetTable[i];
			frame = &sprite->frames[i];

			frame->width = frameHeader->width;
			frame->height = frameHeader->height;
			frame->offsetX = frameHeader->offsetX;
			frame->offsetY = frameHeader->offsetY;

			frame->dataLen = PF_GFX_BPP * frame->width * frame->height;
			frame->data = pf_memAllocMore(frame->dataLen);

			if (frame->data == 0)
			{
				pf_memClearScratch();
				pf_memFree(backup);
				return -5;
			}

			// Transform indexed to RGBA
			dataScanner = frameHeader + 1;
			dstPixelCounter = 0;
			rowTracker = 0;
			while (*dataScanner != 0x7e) {
				// RLE Start Transparency
				if (*dataScanner < 0x7f)
				{
					for (int j = 0; j < *dataScanner; j++)
					{
						frame->data[(PF_GFX_BPP * dstPixelCounter)] = 0;
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 1] = 0;
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 2] = 0;
#ifdef PF_GFX_USE_ALPHA
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 3] = 0;
#endif
						rowTracker++;
						dstPixelCounter++;
					}
					dataScanner++;
				}
				// Non-RLE Color Data
				else if (*dataScanner > 0x7f)
				{
					int numPixels = *dataScanner - 0x7f;
					dataScanner++;
					for (int j = 0; j < numPixels; j++)
					{
						frame->data[(PF_GFX_BPP * dstPixelCounter)] = paletteOffsetTable[(*dataScanner * 3)];
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 1] = paletteOffsetTable[(*dataScanner * 3) + 1];
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 2] = paletteOffsetTable[(*dataScanner * 3) + 2];
#ifdef PF_GFX_USE_ALPHA
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 3] = 0xFF;
#endif
						dataScanner++;
						dstPixelCounter++;
						rowTracker++;
					}
				}
				// RLE End Transparency
				else if (*dataScanner == 0x7f)
				{
					for (rowTracker; rowTracker < frame->width; rowTracker++)
					{
						frame->data[(PF_GFX_BPP * dstPixelCounter)] = 0;
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 1] = 0;
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 2] = 0;
#ifdef PF_GFX_USE_ALPHA
						frame->data[(PF_GFX_BPP * dstPixelCounter) + 3] = 0;
#endif
						dstPixelCounter++;
					}
					dataScanner++;
					rowTracker = 0;
				}
			}
		}
	}

	pf_memClearScratch();
	return sprite;
}

// Load sound from PH file; standard wave.
// Param: name - Filename for memory debugging purposes.
pf_sound* ph_nextSound(const char* name)
{
	int fileSizeResult;
	unsigned char* tempBuff = 0;
	pf_sound* sound = 0;
	PF_MEMMARKER backup;

	// Load local if possible, otherwise load from the PF file
	fileSizeResult = loadFileLocal(name, &tempBuff);
	if (fileSizeResult < 0)
		fileSizeResult = loadFilePH(&tempBuff);

	if (fileSizeResult >= 0)
	{
		// Sig Check
		if (tempBuff != 0x46464952)
		{
			pf_memClearScratch();
			return 0;
		}

		// Setup sound obj
		sound = pf_memAlloc(name, sizeof(pf_sound) + fileSizeResult);

		if (sound != 0)
		{
			sound->dataLen = fileSizeResult;
			sound->wavData = sound + 1;
		}
		else
			sound = 0;
	}
	pf_memClearScratch();

	return sound;
}

int calcTilesetWidth(int numTiles)
{
	int width = numTiles;
	int test = numTiles;
	int count = 1;

	do
	{
		width = test;
		test = width >> 1;
		count = count << 1;
	} while (test > count);

	return count;
}

// Load a background (layer 1) from PH file.
// Param: name - Filename for memory debugging purposes.
pf_bg* ph_nextBackground(const char* name)
{
	int fileSizeResult;
	unsigned char* tempBuff = 0;
	pf_bg* background = 0;
	unsigned char colorIndex;
	PF_MEMMARKER backup;

	bg_header_t* bgHeader;
	unsigned short* mapData;
	unsigned char* tileMap;
	unsigned char* paletteData;

	// Load local if possible, otherwise load from the PF file
	fileSizeResult = loadFileLocal(name, &tempBuff);
	if (fileSizeResult < 0)
		fileSizeResult = loadFilePH(&tempBuff);

	if (fileSizeResult >= 0)
	{
		// Setup offsets
		bgHeader = (bg_header_t*)tempBuff;
		mapData = tempBuff + 0x14;
		tileMap = tempBuff + bgHeader->tileMapOffset;
		paletteData = tempBuff + bgHeader->paletteOffset;

		backup = pf_memMark();
		background = pf_memAlloc(name, sizeof(pf_bg));
		background->width = bgHeader->mapWidth;
		background->height = bgHeader->mapHeight;

		background->layoutLen = 2 * bgHeader->mapWidth * bgHeader->mapHeight;
		background->layout = pf_memAllocMore(background->layoutLen);

		background->tilesetCount = (bgHeader->paletteOffset - bgHeader->tileMapOffset) / 64;
		background->tilesetWidth = calcTilesetWidth(background->tilesetCount);
		background->tilesetHeight = background->tilesetWidth + ((background->tilesetWidth * background->tilesetWidth) - background->tilesetCount ? 1 : 0);

		// Copy Data and Indexed RGB -> RGB
		// Ugh, also linear to 2D tilest cause TeXtUrE LiMiTs
		unsigned int tx = 0, ty = 0;
		unsigned int px = 0, py = 0;
		int pixelTilesetWidth = background->tilesetWidth * 8;
		int pixelTilesetHeight = background->tilesetHeight * 8;

		memcpy_s(background->layout, background->layoutLen, mapData, background->layoutLen);

		background->tilesetLen = pixelTilesetWidth * pixelTilesetHeight * PF_GFX_BPP;
		background->tileset = pf_memAllocMore(background->tilesetLen);
		memset(background->tileset, 0, background->tilesetLen);

		for (int i = 0; i < bgHeader->paletteOffset - bgHeader->tileMapOffset; i++)
		{
			colorIndex = tileMap[i];

			// Something is wrong; gtfo.
			if (colorIndex > bgHeader->numColors)
			{
				background = 0;
				pf_memFree(backup);
				break;
			}

			int indx = ((ty * 8 * pixelTilesetWidth) + (py * pixelTilesetWidth)) + (tx * 8) + px;

			if (colorIndex == 0)
			{
				background->tileset[(indx * PF_GFX_BPP)] = 0;
				background->tileset[(indx * PF_GFX_BPP) + 1] = 0;
				background->tileset[(indx * PF_GFX_BPP) + 2] = 0;
#ifdef PF_GFX_USE_ALPHA
				background->tileset[(indx * PF_GFX_BPP) + 3] = 0;
#endif
			}
			else
			{
				colorIndex--;
				background->tileset[(indx * PF_GFX_BPP)] = paletteData[(colorIndex * 3)];
				background->tileset[(indx * PF_GFX_BPP) + 1] = paletteData[(colorIndex * 3) + 1];
				background->tileset[(indx * PF_GFX_BPP) + 2] = paletteData[(colorIndex * 3) + 2];
#ifdef PF_GFX_USE_ALPHA
				background->tileset[(indx * PF_GFX_BPP) + 3] = 0xFF;
#endif
			}

			px++;
			if (px >= 8)
			{
				px = 0;
				py++;
			}
			if (py >= 8)
			{
				px = py = 0;
				tx++;
				if (tx >= background->tilesetWidth)
				{
					tx = 0;
					ty++;
				}
			}
		}
	}

	pf_memClearScratch();

	return background;
}

// Load the next det, dt2, als, or trg file from the PH file.
// Param: name - Filename for memory debugging purposes.
pf_lvl_data* ph_nextLevelData(const char* name, pf_bg* bgOwner)
{
	int bgHalfWidth = bgOwner->width / 2;
	int fileSizeResult;
	unsigned char* tempBuff = 0;

	unsigned short* yPos = 0;
	unsigned int* padding = 0;
	unsigned char* xPosData = 0;

	PF_MEMMARKER backup;

	pf_lvl_data* lvlData = 0;

	// Load local if possible, otherwise load from the PF file
	fileSizeResult = loadFileLocal(name, &tempBuff);
	if (fileSizeResult < 0)
		fileSizeResult = loadFilePH(&tempBuff);

	if (fileSizeResult >= 0)
	{
		yPos = (unsigned short*)tempBuff;
		padding = (unsigned int*)(tempBuff + (bgHalfWidth * 2));
		xPosData = (unsigned char*)(padding + 5);

		// Verify sizes and offsets
		if (bgHalfWidth * 2 > fileSizeResult)
		{
			pf_memClearScratch();
			return 0;
		}
		for (int i = 0; i < bgHalfWidth; i++)
		{
			if (yPos[i] > tempBuff)
			{
				pf_memClearScratch();
				return 0;
			}
		}
		for (int i = 0; i < 0x5; i++)
		{
			if (padding[i])
			{
				pf_memClearScratch();
				return 0;
			}
		}

		// Allocate and copy data
		backup = pf_memMark();
		lvlData = pf_memAlloc(name, sizeof(pf_lvl_data));
		lvlData->width = bgHalfWidth;
		lvlData->data = pf_memAllocMore(fileSizeResult);

		memcpy(lvlData->data, tempBuff, fileSizeResult);
	}

	pf_memClearScratch();

	return lvlData;
}

// Close the currently opened PH file.
void ph_close()
{
	sys_closeFile(phFileHandle);
	phFileHandle = 0;
}

void skipFile()
{
	int fileSize;
	sys_readFile(phFileHandle, &fileSize, 4, 4);
	sys_seekFile(phFileHandle, fileSize);
}

int loadFilePH(void** tempBuff)
{
	int fileSize;

	if (!sys_readFile(phFileHandle, &fileSize, 4, 4))
		return -1;

	*tempBuff = (unsigned char*)pf_memAllocScratch(fileSize);

	if (!sys_readFile(phFileHandle, *tempBuff, fileSize, fileSize))
		return -2;

	return fileSize;
}

int loadFileLocal(const char* name, void** tempBuff)
{
	PF_FILE* localFile;
	int fileSize;
	int stringLen;
	char fullPath[128 + 20];

	// Change the ph path to point to the local file
	strcpy_s(fullPath, 148, phFilePath);
	stringLen = strlen(fullPath);
	fullPath[stringLen - 3] = '/';
	fullPath[stringLen - 2] = 0;
	strcat_s(fullPath, 148, name);

	// Try to open if it exists
	localFile = sys_openFile(fullPath, PF_FILE_READ);
	if (localFile == -1)
		return -1;

	// Load
	if (!sys_readFile(localFile, &fileSize, 4, 4))
	{
		sys_closeFile(localFile);
		return -1;
	}

	*tempBuff = (unsigned char*)pf_memAllocScratch(fileSize);

	if (!sys_readFile(localFile, *tempBuff, fileSize, fileSize))
	{
		sys_closeFile(localFile);
		return -2;
	}

	sys_closeFile(localFile);

	// Skip the file in the ph archive if it got loaded locally.
	skipFile();

	return fileSize;
}