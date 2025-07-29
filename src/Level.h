#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "PFCommon.h"

#define MAX_LEVELS 32

DATA_LOAD_RESULT pf_loadInitData();
DATA_LOAD_RESULT pf_loadLevelData(int levelNum);
void pf_releaseLevelData();


#endif