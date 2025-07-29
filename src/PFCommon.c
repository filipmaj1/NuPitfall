#include "PFCommon.h"
#include "Graphics.h"
#include "Sound.h"

// Loads the main data that is used across all levels. Note that is *must* be loaded in order.
DATA_LOAD_RESULT pf_loadInitData()
{
    ph_open("init");

    gfx_loadInit();
    snd_loadInit();

    ph_close();

    return DATA_LOAD_SUCCESS;
}