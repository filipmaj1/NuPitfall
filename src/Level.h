#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "PFCommon.h"

#define MAX_LEVELS 32

DATA_LOAD_RESULT pf_loadInitData();
DATA_LOAD_RESULT pf_loadLevelData(int levelNum);
void pf_releaseLevelData();

void lvl_drawTiles(int offsetX, int offsetY);
void lvl_drawLevelDataInfo(int posX, int posY, int* printedTest, int mouseX, int mouseY, int mouseDown, int lastOffset);


#endif