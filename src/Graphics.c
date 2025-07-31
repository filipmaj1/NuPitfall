#include "Graphics.h"
#include "PFAsset.h"
#include "SDLStuff.h"

extern SDLInfo sdlInfo;

static pf_font** fontList[GFX_MAX_FONTS];
static pf_sprite** spriteGlobalList[GFX_MAX_GSPRITES];
static pf_sprite** spriteLevelList[GFX_MAX_LSPRITES];

static int lastFontIndex = 0;
static int lastLoadIndex = 0;
static int levelSpritesStartIndex = 0;

void gfx_drawSprite(int id, int posX, int posY, int frameNum)
{
    pf_sprite* sprite = id < GFX_MAX_GSPRITES ? spriteGlobalList[id] : spriteLevelList[id - GFX_MAX_GSPRITES];
    pf_sframe frame = sprite->frames[frameNum % sprite->numFrames];
    
    SDL_Rect dst; dst.x = posX + frame.offsetX; dst.y = posY + frame.offsetY; dst.w = frame.width; dst.h = frame.height;
    SDL_RenderCopy(sdlInfo.renderer, frame.texture, 0, &dst);
}

void gfx_loadFont(const char* name)
{
    fontList[lastFontIndex++] = ph_nextFont(name);
}

void gfx_loadSprite(const char* name)
{
    SDL_Surface* surface;
    pf_sprite* sprite = ph_nextSprite(name);

    for (int i = 0; i < sprite->numFrames; i++)
    {
        if (sprite->frames[i].width == 0 || sprite->frames[i].height == 0)
            continue;

#ifdef PF_GFX_USE_ALPHA
        surface = SDL_CreateRGBSurfaceWithFormatFrom(sprite->frames[i].data, sprite->frames[i].width, sprite->frames[i].height, PF_GFX_BPP * 8, sprite->frames[i].width * PF_GFX_BPP, SDL_PIXELFORMAT_RGBA32);
#else
        surface = SDL_CreateRGBSurfaceWithFormatFrom(sprite->frames[i].data, sprite->frames[i].width, sprite->frames[i].height, PF_GFX_BPP * 8, sprite->frames[i].width * PF_GFX_BPP, SDL_PIXELFORMAT_RGB24);
        SDL_SetColorKey(surface, SDL_TRUE, 0);
#endif
        sprite->frames[i].texture = SDL_CreateTextureFromSurface(sdlInfo.renderer, surface);
        SDL_FreeSurface(surface);
    }

    spriteGlobalList[lastLoadIndex++] = sprite;
}

void gfx_clearLevelData()
{
    for (int i = 0; i < lastLoadIndex - GFX_MAX_GSPRITES; i++)
    {
        pf_sprite* sprite = spriteLevelList[i];
        for (int j = 0; j < sprite->numFrames; j++)
            SDL_DestroyTexture(sprite->frames[j].texture);
    }
    levelSpritesStartIndex = lastLoadIndex;
}

void gfx_loadInit()
{
    gfx_loadFont("font.pcs");
    gfx_loadFont("scoline.pcs");
    gfx_loadSprite("fxrbmrng.pc");
    gfx_loadSprite("fxrbmrot.pc");
    gfx_loadSprite("fxzdeath.pc");
    gfx_loadSprite("fxrdust2.pc");
    gfx_loadSprite("fx_deat2.pc");
    gfx_loadSprite("fx_expl3.pc");
    gfx_loadSprite("fx_hrtbt.pc");
    gfx_loadSprite("fx_mls.pc");
    gfx_loadSprite("fx_stone.pc");
    gfx_loadSprite("fx_sprk1.pc");
    gfx_loadSprite("fx_sprk2.pc");
    gfx_loadSprite("mi_1up.pc");
    gfx_loadSprite("mi_chili.pc");
    gfx_loadSprite("mi_coin.pc");
    gfx_loadSprite("mi_croc.pc");
    gfx_loadSprite("mi_gold.pc");
    gfx_loadSprite("mi_life.pc");
    gfx_loadSprite("mi_pouc2.pc");
    gfx_loadSprite("mi_ptfal.pc");
    gfx_loadSprite("mi_ring.pc");
    gfx_loadSprite("mi_silvr.pc");
    gfx_loadSprite("mi_stone.pc");
    gfx_loadSprite("mi_stonb.pc");
    gfx_loadSprite("mi_time.pc");
    gfx_loadSprite("mirbmrng.pc");
    gfx_loadSprite("obrston0.pc");
    gfx_loadSprite("ob_pouch.pc");
    gfx_loadSprite("ob_sling.pc");
    gfx_loadSprite("sc_eyes1.pc");
    gfx_loadSprite("sc_eyes2.pc");
    gfx_loadSprite("ltr_lg.pc");
    gfx_loadSprite("ltr_md.pc");
    gfx_loadSprite("ltr_sm.pc");
    gfx_loadSprite("scoline.pc");
    gfx_loadSprite("hatman.pc");
    gfx_loadSprite("hyibflip.pc");
    gfx_loadSprite("hyibland.pc");
    gfx_loadSprite("hyiblrec.pc");
    gfx_loadSprite("hyibmrng.pc");
    gfx_loadSprite("hyibng3b.pc");
    gfx_loadSprite("hyibngab.pc");
    gfx_loadSprite("hyibngac.pc");
    gfx_loadSprite("hyibngbc.pc");
    gfx_loadSprite("hyibngrv.pc");
    gfx_loadSprite("hyibung1.pc");
    gfx_loadSprite("hyibung2.pc");
    gfx_loadSprite("hyibung3.pc");
    gfx_loadSprite("hyicl2rn.pc");
    gfx_loadSprite("hyicr2cl.pc");
    gfx_loadSprite("hyicrcyc.pc");
    gfx_loadSprite("hyicrtrn.pc");
    gfx_loadSprite("hyicrwhp.pc");
    gfx_loadSprite("hyidazed.pc");
    gfx_loadSprite("hyidie.pc");
    gfx_loadSprite("hyiding.pc");
    gfx_loadSprite("hyidrope.pc");
    gfx_loadSprite("hyidvine.pc");
    gfx_loadSprite("hyidzip.pc");
    gfx_loadSprite("hyiemrg.pc");
    gfx_loadSprite("hyienter.pc");
    gfx_loadSprite("hyifall.pc");
    gfx_loadSprite("hyifcrwl.pc");
    gfx_loadSprite("hyigland.pc");
    gfx_loadSprite("hyihang.pc");
    gfx_loadSprite("hyihjump.pc");
    gfx_loadSprite("hyihshot.pc");
    gfx_loadSprite("hyihwall.pc");
    gfx_loadSprite("hyihwhip.pc");
    gfx_loadSprite("hyijp2sn.pc");
    gfx_loadSprite("hyilean.pc");
    gfx_loadSprite("hyilooka.pc");
    gfx_loadSprite("hyilsbal.pc");
    gfx_loadSprite("hyimrop2.pc");
    gfx_loadSprite("hyimzip.pc");
    gfx_loadSprite("hyininja.pc");
    gfx_loadSprite("hyipee.pc");
    gfx_loadSprite("hyipsbal.pc");
    gfx_loadSprite("hyipull.pc");
    gfx_loadSprite("hyipulup.pc");
    gfx_loadSprite("hyipush.pc");
    gfx_loadSprite("hyird2rn.pc");
    gfx_loadSprite("hyiready.pc");
    gfx_loadSprite("hyirn2cl.pc");
    gfx_loadSprite("hyirn2sn.pc");
    gfx_loadSprite("hyiroped.pc");
    gfx_loadSprite("hyirsht1.pc");
    gfx_loadSprite("hyirtrn2.pc");
    gfx_loadSprite("hyirun.pc");
    gfx_loadSprite("hyirun2.pc");
    gfx_loadSprite("hyirwhip.pc");
    gfx_loadSprite("hyirwhpr.pc");
    gfx_loadSprite("hyishoot.pc");
    gfx_loadSprite("hyisink.pc");
    gfx_loadSprite("hyiskte1.pc");
    gfx_loadSprite("hyiskte2.pc");
    gfx_loadSprite("hyiskte3.pc");
    gfx_loadSprite("hyiskte4.pc");
    gfx_loadSprite("hyislice.pc");
    gfx_loadSprite("hyisomr1.pc");
    gfx_loadSprite("hyisomr2.pc");
    gfx_loadSprite("hyisomr3.pc");
    gfx_loadSprite("hyispin.pc");
    gfx_loadSprite("hyisprng.pc");
    gfx_loadSprite("hyisspi2.pc");
    gfx_loadSprite("hyisswng.pc");
    gfx_loadSprite("hyist2cr.pc");
    gfx_loadSprite("hyist2pu.pc");
    gfx_loadSprite("hyisvine.pc");
    gfx_loadSprite("hyitrip1.pc");
    gfx_loadSprite("hyitwirl.pc");
    gfx_loadSprite("hyiurope.pc");
    gfx_loadSprite("hyivgrab.pc");
    gfx_loadSprite("hyivjump.pc");
    gfx_loadSprite("hyivwhip.pc");
    gfx_loadSprite("hyiwhip.pc");
    gfx_loadSprite("hyiwhiph.pc");
    gfx_loadSprite("hyizen.pc");
    gfx_loadSprite("hyizip.pc");

    levelSpritesStartIndex = lastLoadIndex;
}