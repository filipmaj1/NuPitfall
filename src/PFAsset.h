#pragma once
#ifndef _PF_ASSET_H_
#define _PF_ASSET_H_

#include "PFCommon.h"

void ph_open(const char* phName);
pf_font* ph_nextFont(const char* name);
pf_sprite* ph_nextSprite(const char* name);
pf_sound* ph_nextSound(const char* name);
pf_bg* ph_nextBackground(const char* name);
pf_lvl_data* ph_nextLevelData(const char* name, pf_bg* bgOwner);
void ph_close();

#endif