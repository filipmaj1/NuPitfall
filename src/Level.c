#include "Level.h"

#include "PFCommon.h"
#include "PFAsset.h"
#include "PFMem.h"

/*
* Handles loading of the various levels and data associated with them.
*/

static pf_level level;
static SDL_Surface* surface;


void drawBG(int posX, int posY, int tile)
{
    int flip = 0;
    if ((tile & 0x4000) != 0)
        flip |= SDL_FLIP_HORIZONTAL;
    if ((tile & 0x2000) != 0)
        flip |= SDL_FLIP_VERTICAL;

    int tileNum = tile & 0xFFF;
    int scale = 1;
    SDL_Rect src; src.x = (tileNum % level.bgMain->tilesetWidth) * 8; src.y = (tileNum / level.bgMain->tilesetWidth) * 8; src.w = 8; src.h = 8;
    SDL_Rect dst; dst.x = posX * 8 * scale; dst.y = posY * 8 * scale; dst.w = 8 * scale; dst.h = 8 * scale;
    SDL_RenderCopyEx(sdlInfo.renderer, level.bgMain->texture, &src, &dst, 0, 0, flip);
}


void lvl_drawTiles(int offsetX, int offsetY)
{
    for (int y = 0; y < level.bgMain->height; y++)
    {
        for (int x = 0; x < level.bgMain->width; x++)
        {
            drawBG(offsetX + x, offsetY + y, level.bgMain->layout[(y * level.bgMain->width) + x]);
        }
    }
}

void lvl_drawLevelDataInfo(int posX, int posY, int* printedTest, int mouseX, int mouseY, int mouseDown, int* lastOffset)
{
    SDL_Rect dst;
    pf_lvl_data* data = level.trg;
    int scale = 1;


    if (!data)
        return;

    for (int x = 0; x < data->width; x++)
    {
        if (((short*)data->data)[x] != 0)
        {
            unsigned short offset = ((short*)data->data)[x];
            offset = offset << 8 | offset >> 8;
            unsigned short* yData = data->data + offset;

            while ((*((unsigned char*)yData)) != 0xFF)
            {
                unsigned short yCoord = *yData & 0xFF;
                dst.x = ((posX * 8) + (x * 8 * 2)) * scale; dst.y = ((posY * 8) + (yCoord * 8 * 2)) * scale; dst.w = 16 * scale; dst.h = 16 * scale;

                if (mouseDown && lastOffset != (unsigned char*)yData - (unsigned char*)data->data && mouseX != -1 && mouseX >= dst.x && mouseX <= dst.x + dst.w)
                {
                    if (mouseY != -1 && mouseY >= dst.y && mouseY <= dst.y + dst.h)
                    {
                        //printf("Touching obj. Offset: 0x%x, Val: 0x%x, Name: %s\n", (unsigned char*)yData - (unsigned char*)data->data, (*yData >> 8) & 0xFF, entName((*yData >> 8) & 0xFF));
                        printf("Touching obj. Offset: 0x%x, Val: 0x%x\n", (unsigned char*)yData - (unsigned char*)data->data, (*yData >> 8) & 0xFF);
                        lastOffset = (unsigned char*)yData - (unsigned char*)data->data;
                    }
                }

                if (!*printedTest && entName((*yData >> 8) & 0xFF) == 0)
                {
                    *printedTest = 1;
                    printf("%x, ", (*yData >> 8) & 0xFF);
                }

                if ((*yData >> 8) & 0xFF == 0xF)
                {
                    SDL_SetRenderDrawColor(sdlInfo.renderer, 255, 255, 0, 255);
                    printf("HERE");
                }
                else
                    SDL_SetRenderDrawColor(sdlInfo.renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(sdlInfo.renderer, &dst);
                yData++;
            }
        }
    }
    *printedTest = 1;
}

void loadSDLTexture()
{
#ifdef PF_GFX_USE_ALPHA
    surface = SDL_CreateRGBSurfaceWithFormatFrom(level.bgMain->tileset, 100, 100, PF_GFX_BPP * 8, 8 * PF_GFX_BPP, SDL_PIXELFORMAT_RGBA32);
#else
    surface = SDL_CreateRGBSurfaceWithFormatFrom(level.bgMain->tileset, level.bgMain->tilesetWidth * 8, level.bgMain->tilesetHeight * 8, PF_GFX_BPP * 8, level.bgMain->tilesetWidth * 8 * PF_GFX_BPP, SDL_PIXELFORMAT_RGB24);
    SDL_SetColorKey(surface, SDL_TRUE, 0);
#endif

    level.bgMain->texture = SDL_CreateTextureFromSurface(sdlInfo.renderer, surface);
    SDL_FreeSurface(surface);
}

void loadLevel0()
{
    ph_open("level00");

    level.bgMain = ph_nextBackground("forest1.bg");
    level.trg = ph_nextLevelData("forest1.trg", level.bgMain);
    level.det = ph_nextLevelData("forest1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("forest1.dt2", level.bgMain);
    level.als = ph_nextLevelData("forest1.als", level.bgMain);
    level.bgPax = ph_nextBackground("for_par.bg");
    loadSDLTexture();

    gfx_loadSprite("fx_leaf1");
    gfx_loadSprite("fxzleaf2");
    gfx_loadSprite("fx_leaf3");
    gfx_loadSprite("fx_leaf4");
    gfx_loadSprite("jguleap");
    gfx_loadSprite("jgumis");
    gfx_loadSprite("jgurevr");
    gfx_loadSprite("jgurun");
    gfx_loadSprite("jgulow");
    gfx_loadSprite("jgurn2lo");
    gfx_loadSprite("jguroar");
    gfx_loadSprite("mkzrun");
    gfx_loadSprite("mkzrn2st");
    gfx_loadSprite("mkzhvine");
    gfx_loadSprite("mkzbounc");
    gfx_loadSprite("mkzturn");
    gfx_loadSprite("mkztos");
    gfx_loadSprite("mi_go");
    gfx_loadSprite("mi_prcnt");
    gfx_loadSprite("ob_bunge");
    gfx_loadSprite("ob_bung");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("obrpit1");
    gfx_loadSprite("obrcactu");
    gfx_loadSprite("obrbrnch");
    gfx_loadSprite("plzexpl");
    gfx_loadSprite("plzspik");
    gfx_loadSprite("r_f");
    gfx_loadSprite("rope");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimis");
    gfx_loadSprite("tszbody1");
    gfx_loadSprite("tszhang");
    gfx_loadSprite("tszup");
    gfx_loadSprite("tszspit");
    gfx_loadSprite("tszlimp");
    gfx_loadSprite("whirun");
    gfx_loadSprite("whitos");
    gfx_loadSprite("whiroll");
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
    loadSDLTexture();

    gfx_loadSprite("fx_drip1");
    gfx_loadSprite("fx_leaf1");
    gfx_loadSprite("fxzleaf2");
    gfx_loadSprite("fx_leaf3");
    gfx_loadSprite("fx_leaf4");
    gfx_loadSprite("fxifeath");
    gfx_loadSprite("hkifly");
    gfx_loadSprite("hkiturn");
    gfx_loadSprite("hkidive");
    gfx_loadSprite("hkistun");
    gfx_loadSprite("hkiglide");
    gfx_loadSprite("mkztoss");
    gfx_loadSprite("mkzbounc");
    gfx_loadSprite("mkzturn");
    gfx_loadSprite("mkzrun");
    gfx_loadSprite("mkzrn2st");
    gfx_loadSprite("mkzhvine");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("ob_bunge");
    gfx_loadSprite("obrcactu");
    gfx_loadSprite("obzfrock");
    gfx_loadSprite("ob_bungs");
    gfx_loadSprite("ropes");
    gfx_loadSprite("r_w");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("stifly");
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
    loadSDLTexture();

    gfx_loadSprite("btfhang");
    gfx_loadSprite("btzface");
    gfx_loadSprite("btzfly");
    gfx_loadSprite("fxivortx");
    gfx_loadSprite("fxzexpl2");
    gfx_loadSprite("fxzspark");
    gfx_loadSprite("ob_mcar");
    gfx_loadSprite("ob_scar");
    gfx_loadSprite("ob_chute");
    gfx_loadSprite("ob_float");
    gfx_loadSprite("ob_whelz");
    gfx_loadSprite("ob_ceil");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("obivweb");
    gfx_loadSprite("obzlever");
    gfx_loadSprite("obztnt");
    gfx_loadSprite("obzleve3");
    gfx_loadSprite("rtz1run");
    gfx_loadSprite("rtzup");
    gfx_loadSprite("rtzrun");
    gfx_loadSprite("rtzfall");
    gfx_loadSprite("rtzturn");
    gfx_loadSprite("r_m");
    gfx_loadSprite("sp_walk");
    gfx_loadSprite("sp_jump");

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
    loadSDLTexture();

    gfx_loadSprite("btrfly");
    gfx_loadSprite("btrface");
    gfx_loadSprite("btrhang");
    gfx_loadSprite("fxifeath");
    gfx_loadSprite("fxzpots3");
    gfx_loadSprite("fxzpots2");
    gfx_loadSprite("fxfpltof");
    gfx_loadSprite("fxivortx");
    gfx_loadSprite("gargrok");
    gfx_loadSprite("hkifly");
    gfx_loadSprite("hkiturn");
    gfx_loadSprite("hkidive");
    gfx_loadSprite("hkistun");
    gfx_loadSprite("hkiglide");
    gfx_loadSprite("jgustill");
    gfx_loadSprite("jgustone");
    gfx_loadSprite("jguroar");
    gfx_loadSprite("jgurun");
    gfx_loadSprite("jgurevrs");
    gfx_loadSprite("jgurn2lo");
    gfx_loadSprite("jgulow");
    gfx_loadSprite("jguleap");
    gfx_loadSprite("jgumiss");
    gfx_loadSprite("mi_prcnt");
    gfx_loadSprite("ob_door");
    gfx_loadSprite("obftung");
    gfx_loadSprite("obrgarg");
    gfx_loadSprite("obfleve2");
    gfx_loadSprite("obrpit2a");
    gfx_loadSprite("ob_spik1");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("obrpit2b");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("obzaxe");
    gfx_loadSprite("ob_spik2");
    gfx_loadSprite("rtzrun");
    gfx_loadSprite("rtzturn");
    gfx_loadSprite("r_r");
    gfx_loadSprite("scorp");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("sn_dot");
    gfx_loadSprite("snix_dot");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("skijaw");
    gfx_loadSprite("skimorph");
    gfx_loadSprite("skiwalk");
    gfx_loadSprite("skzarm");
    gfx_loadSprite("skzantic");
    gfx_loadSprite("skichop");
    gfx_loadSprite("sk0chop");
    gfx_loadSprite("skiturn");
    gfx_loadSprite("skirib");
    gfx_loadSprite("skithrow");
    gfx_loadSprite("skiready");
    gfx_loadSprite("skiroll");
    gfx_loadSprite("skzbone");
    gfx_loadSprite("skidie");
    gfx_loadSprite("tszhang");
    gfx_loadSprite("tszbody1");
    gfx_loadSprite("tszup");
    gfx_loadSprite("tszspit");
    gfx_loadSprite("tszlimp");

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
    loadSDLTexture();

    gfx_loadSprite("btfhang");
    gfx_loadSprite("btzfly");
    gfx_loadSprite("btzface");
    gfx_loadSprite("fxzpots1");
    gfx_loadSprite("fxzpots2");
    gfx_loadSprite("fxzpots3");
    gfx_loadSprite("fxgtorch");
    gfx_loadSprite("fxzfirej");
    gfx_loadSprite("fxzexpl2");
    gfx_loadSprite("fxrfirep");
    gfx_loadSprite("fx0firep");
    gfx_loadSprite("fxzfireb");
    gfx_loadSprite("fxifirer");
    gfx_loadSprite("fxivortx");
    gfx_loadSprite("obtpit2a");
    gfx_loadSprite("obfbston");
    gfx_loadSprite("ob_door");
    gfx_loadSprite("obzlever");
    gfx_loadSprite("ob_chute");
    gfx_loadSprite("obivweb");
    gfx_loadSprite("ob_spik1");
    gfx_loadSprite("obrwhee1");
    gfx_loadSprite("obzspear");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("ob_door3");
    gfx_loadSprite("ob_float");
    gfx_loadSprite("obtpit2b");
    gfx_loadSprite("obrwhee2");
    gfx_loadSprite("r_t");
    gfx_loadSprite("rtz1run");
    gfx_loadSprite("rtzturn");
    gfx_loadSprite("sp_walk");
    gfx_loadSprite("sp_jump");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("tgrharro");
    gfx_loadSprite("tgrturn");
    gfx_loadSprite("tgrlarro");
    gfx_loadSprite("tgrpeel");
    gfx_loadSprite("tprapea2");
    gfx_loadSprite("tgrwalk");
    gfx_loadSprite("tprhigh");
    gfx_loadSprite("tgfarrow");
    gfx_loadSprite("tpzhit");

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
    loadSDLTexture();

    gfx_loadSprite("fxleaf12");
    gfx_loadSprite("fxleaf22");
    gfx_loadSprite("fx_leaf3");
    gfx_loadSprite("fxleaf42");
    gfx_loadSprite("mkzrun");
    gfx_loadSprite("mkzrn2st");
    gfx_loadSprite("mkzturn");
    gfx_loadSprite("mkzhvine");
    gfx_loadSprite("mkztoss");
    gfx_loadSprite("mkzbounc");
    gfx_loadSprite("obfpit2a");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("obbrnch2");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("obfpit2b");
    gfx_loadSprite("obrcactu");
    gfx_loadSprite("plzexpl");
    gfx_loadSprite("plzspik");
    gfx_loadSprite("ropes2");
    gfx_loadSprite("r_f2");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("tszhang");
    gfx_loadSprite("tszbody1");
    gfx_loadSprite("tszup");
    gfx_loadSprite("tszspit");
    gfx_loadSprite("tszlimp");
    gfx_loadSprite("whirun");
    gfx_loadSprite("whitoss");
    gfx_loadSprite("whiroll");

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
    loadSDLTexture();

    gfx_loadSprite("crzopen");
    gfx_loadSprite("crzrippl");
    gfx_loadSprite("crzjump");
    gfx_loadSprite("crzdive");
    gfx_loadSprite("fx_leaf1");
    gfx_loadSprite("fxzleaf2");
    gfx_loadSprite("fx_leaf3");
    gfx_loadSprite("fx_leaf4");
    gfx_loadSprite("fx_rippl");
    gfx_loadSprite("fx_drip1");
    gfx_loadSprite("fxisplsh");
    gfx_loadSprite("fxifeath");
    gfx_loadSprite("hkifly");
    gfx_loadSprite("hkiturn");
    gfx_loadSprite("hkiglide");
    gfx_loadSprite("hkidive");
    gfx_loadSprite("hkistun");
    gfx_loadSprite("mkzrun");
    gfx_loadSprite("mkzrn2st");
    gfx_loadSprite("mkzhvine");
    gfx_loadSprite("mkzturn");
    gfx_loadSprite("mkztoss");
    gfx_loadSprite("mkzbounc");
    gfx_loadSprite("obiturtl");
    gfx_loadSprite("obrcactu");
    gfx_loadSprite("ob_bunge");
    gfx_loadSprite("ob_bungs");
    gfx_loadSprite("stifly");
    gfx_loadSprite("scffish");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("ropes");
    gfx_loadSprite("r_w");

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
    loadSDLTexture();

    gfx_loadSprite("m2_text");
    gfx_loadSprite("ob_scar");
    gfx_loadSprite("ob_whelz");
    gfx_loadSprite("obztnt");
    gfx_loadSprite("ob_liter");
    gfx_loadSprite("ob_lite");
    gfx_loadSprite("ob_mcar");
    gfx_loadSprite("mi_go");
    gfx_loadSprite("skiready");
    gfx_loadSprite("tpzhit");
    gfx_loadSprite("gvrvapor");

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
    loadSDLTexture();

    gfx_loadSprite("fxifeath");
    gfx_loadSprite("fxzexpl2");
    gfx_loadSprite("fxpltof2");
    gfx_loadSprite("fxzpots1");
    gfx_loadSprite("fxzpots2");
    gfx_loadSprite("fxzpots3");
    gfx_loadSprite("fxivortx");
    gfx_loadSprite("gargrok2");
    gfx_loadSprite("hkiglide");
    gfx_loadSprite("hkiturn");
    gfx_loadSprite("hkistun");
    gfx_loadSprite("hkifly");
    gfx_loadSprite("hkidive");
    gfx_loadSprite("jguroar");
    gfx_loadSprite("jgurun");
    gfx_loadSprite("jgurevrs");
    gfx_loadSprite("jgulow");
    gfx_loadSprite("jgurn2lo");
    gfx_loadSprite("jguleap");
    gfx_loadSprite("jgumiss");
    gfx_loadSprite("jmzmorfa");
    gfx_loadSprite("jmzmorfb");
    gfx_loadSprite("jmzready");
    gfx_loadSprite("jmzswipe");
    gfx_loadSprite("jm0swipe");
    gfx_loadSprite("jm1swipe");
    gfx_loadSprite("jmzmorf2");
    gfx_loadSprite("obftung2");
    gfx_loadSprite("obfpit2a");
    gfx_loadSprite("obrgarg2");
    gfx_loadSprite("obzaxe1");
    gfx_loadSprite("ob_spik1");
    gfx_loadSprite("obfpit2b");
    gfx_loadSprite("obleve22");
    gfx_loadSprite("ob_door2");
    gfx_loadSprite("ob_spik2");
    gfx_loadSprite("mi_prcnt");
    gfx_loadSprite("r_r2");
    gfx_loadSprite("rtz1run");
    gfx_loadSprite("rtzturn");
    gfx_loadSprite("skiready");
    gfx_loadSprite("skirib");
    gfx_loadSprite("skithrow");
    gfx_loadSprite("skzbone");
    gfx_loadSprite("skiturn");
    gfx_loadSprite("skidie");
    gfx_loadSprite("skijaw");
    gfx_loadSprite("skzarm");
    gfx_loadSprite("skzantic");
    gfx_loadSprite("skichop");
    gfx_loadSprite("sk0chop");
    gfx_loadSprite("skimorph");
    gfx_loadSprite("skiroll");
    gfx_loadSprite("skiwalk");
    gfx_loadSprite("sn_dot");
    gfx_loadSprite("snix_dot");
    gfx_loadSprite("snislthr");
    gfx_loadSprite("sn_hole");
    gfx_loadSprite("sniturn");
    gfx_loadSprite("snixhole");
    gfx_loadSprite("snilunge");
    gfx_loadSprite("snuhit");
    gfx_loadSprite("snimiss");
    gfx_loadSprite("tszhang");
    gfx_loadSprite("tszbody1");
    gfx_loadSprite("tszup");
    gfx_loadSprite("tszspit");
    gfx_loadSprite("tszlimp");

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
    loadSDLTexture();

    gfx_loadSprite("btfhang");
    gfx_loadSprite("btzfly");
    gfx_loadSprite("btzface");
    gfx_loadSprite("fxzpots1");
    gfx_loadSprite("fxzpots2");
    gfx_loadSprite("fxzpots3");
    gfx_loadSprite("fxgtorch");
    gfx_loadSprite("fxzfireb");
    gfx_loadSprite("ob_door");
    gfx_loadSprite("obzlever");
    gfx_loadSprite("obzsball");
    gfx_loadSprite("ob_chute");
    gfx_loadSprite("obftung");
    gfx_loadSprite("obivweb");
    gfx_loadSprite("obihweb");
    gfx_loadSprite("obiaweb");
    gfx_loadSprite("ob_door3");
    gfx_loadSprite("obichain");
    gfx_loadSprite("ob_float");
    gfx_loadSprite("obrwhee1");
    gfx_loadSprite("obrwhee2");
    gfx_loadSprite("r_t");
    gfx_loadSprite("tprapea2");
    gfx_loadSprite("tgrpeel");
    gfx_loadSprite("tprhigh");
    gfx_loadSprite("tpzhit");
    gfx_loadSprite("tgrharro");
    gfx_loadSprite("tgrturn");
    gfx_loadSprite("tgrlarro");
    gfx_loadSprite("tgrwalk");
    gfx_loadSprite("tgfarrow");

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
    loadSDLTexture();

    gfx_loadSprite("bosss");
    gfx_loadSprite("mi_prcnt");

    ph_close();
}

void loadLevel11()
{
    ph_open("level00");

    level.bgMain = ph_nextBackground("ceil1.bg");
    level.trg = ph_nextLevelData("simon1.trg", level.bgMain);
    level.det = ph_nextLevelData("simon1.det", level.bgMain);
    level.dt2 = ph_nextLevelData("simon1.dt2", level.bgMain);
    level.als = ph_nextLevelData("simon1.als", level.bgMain);
    //level.bgPax = ph_nextBackground("simon1.bg");
    loadSDLTexture();

    gfx_loadSprite("abc");
    gfx_loadSprite("abc1");
    gfx_loadSprite("obzlever");
    gfx_loadSprite("ob_door");
    gfx_loadSprite("ob_door3");
    gfx_loadSprite("hurry");

    ph_close();
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
    }
}