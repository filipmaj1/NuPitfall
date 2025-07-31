#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "PFCommon.h"
#include "PFMem.h"

#define GFX_INIT 0x500D

#define GFX_MAX_FONTS 2
#define GFX_MAX_GSPRITES 118
#define GFX_MAX_LSPRITES 200



void gfx_loadInit();
void gfx_drawSprite(int id, int posX, int posY, int frame);

#endif