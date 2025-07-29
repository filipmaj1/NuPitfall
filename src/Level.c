#include "Level.h"

#include "PFCommon.h"
#include "PFAsset.h"
#include "PFMem.h"

/*
* Handles loading of the various levels and data associated with them.
*/

static pf_level level;

void loadLevel0()
{
    ph_open("level00");
    level.bgMain = ph_nextBackground("forest1.bg");
    level.trg = ph_nextLevelData("forest1.trg", level.bgMain);
    level.det = ph_nextLevelData("forest1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("forest1.dt2", level.bgMain);
    level.als = ph_nextLevelData("forest1.als", level.bgMain);
    level.bgPax = ph_nextBackground("for_par.bg");
    ph_close();
}

void loadLevel1()
{
    ph_open("level01");
    level.bgMain = ph_nextBackground("waterf1.bg");
    level.trg = ph_nextLevelData("waterf1.trg", level.bgMain);
    level.det = ph_nextLevelData("waterf1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("waterf1.dt2", level.bgMain);
    level.als = ph_nextLevelData("waterf1.als", level.bgMain);
    level.bgPax = ph_nextBackground("waterf1ax.bg");
    ph_close();
}

void loadLevel2()
{
    ph_open("level02");
    level.bgMain = ph_nextBackground("mine1.bg");
    level.trg = ph_nextLevelData("mine1.trg", level.bgMain);
    level.det = ph_nextLevelData("mine1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("mine1.dt2", level.bgMain);
    level.als = ph_nextLevelData("mine1.als", level.bgMain);
    level.bgPax = ph_nextBackground("mine_lax.bg");
    ph_close();
}

void loadLevel3()
{
    ph_open("level03");
    level.bgMain = ph_nextBackground("ruins1.bg");
    level.trg = ph_nextLevelData("ruins1.trg", level.bgMain);
    level.det = ph_nextLevelData("ruins1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("ruins1.dt2", level.bgMain);
    level.als = ph_nextLevelData("ruins1.als", level.bgMain);
    level.bgPax = ph_nextBackground("clouds.bg");
    ph_close();
}

void loadLevel4()
{
    ph_open("level04");
    level.bgMain = ph_nextBackground("temple1.bg");
    level.trg = ph_nextLevelData("temple1.trg", level.bgMain);
    level.det = ph_nextLevelData("temple1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("temple1.dt2", level.bgMain);
    level.als = ph_nextLevelData("temple1.als", level.bgMain);
    level.bgPax = 0;
    ph_close();
}

void loadLevel5()
{
    ph_open("level05");
    level.bgMain = ph_nextBackground("forest2.bg");
    level.trg = ph_nextLevelData("forest2.trg", level.bgMain);
    level.det = ph_nextLevelData("forest2.det", level.bgMain);
    level.dt2 = ph_nextLevelData("forest2.dt2", level.bgMain);
    level.als = ph_nextLevelData("forest2.als", level.bgMain);
    level.bgPax = ph_nextBackground("for_par2.bg");
    ph_close();
}

void loadLevel6()
{
    ph_open("level06");
    level.bgMain = ph_nextBackground("waterf2.bg");
    level.trg = ph_nextLevelData("waterf2.trg", level.bgMain);
    level.det = ph_nextLevelData("waterf2.det", level.bgMain);
    level.dt2 = ph_nextLevelData("waterf2.dt2", level.bgMain);
    level.als = ph_nextLevelData("waterf2.als", level.bgMain);
    level.bgPax = ph_nextBackground("waterf1ax2.bg");
    ph_close();
}

void loadLevel7()
{
    ph_open("level07");
    level.bgMain = ph_nextBackground("mine2.bg");
    level.trg = ph_nextLevelData("mine2.trg", level.bgMain);
    level.det = ph_nextLevelData("mine2.det", level.bgMain);
    level.dt2 = ph_nextLevelData("mine2.dt2", level.bgMain);
    level.als = ph_nextLevelData("mine2.als", level.bgMain);
    level.bgPax = ph_nextBackground("mine_lax.bg");
    ph_close();
}

void loadLevel8()
{
    ph_open("level08");
    level.bgMain = ph_nextBackground("ruins2.bg");
    level.trg = ph_nextLevelData("ruins2.trg", level.bgMain);
    level.det = ph_nextLevelData("ruins2.det", level.bgMain);
    level.dt2 = ph_nextLevelData("ruins2.dt2", level.bgMain);
    level.als = ph_nextLevelData("ruins2.als", level.bgMain);
    level.bgPax = ph_nextBackground("clouds.bg");
    ph_close();
}

void loadLevel9()
{
    ph_open("level09");
    level.bgMain = ph_nextBackground("temple2.bg");
    level.trg = ph_nextLevelData("temple2.trg", level.bgMain);
    level.det = ph_nextLevelData("temple2.det", level.bgMain);
    level.dt2 = ph_nextLevelData("temple2.dt2", level.bgMain);
    level.als = ph_nextLevelData("temple2.als", level.bgMain);
    level.bgPax = ph_nextBackground("templax2.bg");
    ph_close();
}

void loadLevel10()
{
    ph_open("level10");
    level.bgMain = ph_nextBackground("wsarena.bg");
    level.trg = ph_nextLevelData("wsarena.trg", level.bgMain);
    level.det = ph_nextLevelData("wsarena.det", level.bgMain);
    level.dt2 = ph_nextLevelData("wsarena.dt2", level.bgMain);
    level.als = ph_nextLevelData("wsarena.als", level.bgMain);
    level.bgPax = ph_nextBackground("clouds.bg");
    ph_close();
}

void loadLevel00()
{
    ph_open("level00");
    level.bgMain = ph_nextBackground("ceil1.bg");
    level.trg = ph_nextLevelData("simon1.trg", level.bgMain);
    level.det = ph_nextLevelData("simon1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("simon1.dt2", level.bgMain);
    level.als = ph_nextLevelData("simon1.als", level.bgMain);
    //level.bgPax = ph_nextBackground("simon1.bg");
    ph_close();
}

void pf_releaseLevelData()
{

}

// Loads the data for a specific level.
DATA_LOAD_RESULT pf_loadLevelData(int levelNum)
{
    switch (levelNum)
    {
    case 0:
        loadLevel0();
        return DATA_LOAD_SUCCESS;
    case 1:
        loadLevel1();
        return DATA_LOAD_SUCCESS;
    case 2:
        loadLevel2();
        return DATA_LOAD_SUCCESS;
    case 3:
        loadLevel3();
        return DATA_LOAD_SUCCESS;
    case 4:
        loadLevel4();
        return DATA_LOAD_SUCCESS;
    case 5:
        loadLevel5();
        return DATA_LOAD_SUCCESS;
    case 6:
        loadLevel6();
        return DATA_LOAD_SUCCESS;
    case 7:
        loadLevel7();
        return DATA_LOAD_SUCCESS;
    case 8:
        loadLevel8();
        return DATA_LOAD_SUCCESS;
    case 9:
        loadLevel9();
        return DATA_LOAD_SUCCESS;
    case 10:
        loadLevel10();
        return DATA_LOAD_SUCCESS;
    case 11:
        loadLevel00();
        return DATA_LOAD_SUCCESS;
    }
}