#include <stdlib.h>
#include <stdio.h>
#include "SDLStuff.h"
#include "PFCommon.h"
#include "PFAsset.h"
#include "PFMem.h"

/* Cheats */
// eighttracksrule - Disable CD
// vampire - God Mode
// flylikeaneagle - NoClip
// beammeup - Show Pos Coords
// framerate - Show FPS
// mijmrowhtrae - Atari Level becomes Earthworm Jim level
// paidtoplaygames - Shows credits to the testers
// iidqd - Shows developers; joke about doom

// ALS Entity Ids
/*
0x04 - Quicksand
0x05 - Stone Bag Floating?
0x07 - Stone Bag
0x13 - Bounce Web
0x17 - Gland
0x39 - Checkpoint Totem
0x40 - Heart
0x47 - Super Stone Ammo
0x5A - Coin
0x5B - Silver
0x5C - Ring


0x6E - Snake Hole
0x74 - Snake
0x82 - Walking Monkey
0xA6 - Boar
0xB1 - Needle Spitter Thing
0xDC - Leaf FX
0xEF - Glowing Eyes FX
*/

/*
TRG IDs

0x01 - Ceiling State
0x02 - 
0x06 - Slip 
0x08 - Ledge Left
0x09 - Ledge Right
0x0C - Zipline
0x19 - Ladder Related
0x1A - Ladder Related
0x1D - Peg Whip
0x1F - Pain Spikes
0x5F - End Level
0x64 - Teleport
0x74 - Teleport Destination
*/

unsigned char* entName(unsigned char byte)
{
    switch (byte)
    {
        case 0x03: return "Tarpit";
        case 0x04: return "Quicksand";
        case 0x05: return "Floating Stone Ammo Pouch";
        case 0x06: return "Helper Stone Ammo Pouch"; //Only appears when ammo < 10
        case 0x07: return "Stone Ammo Pouch";
        case 0x08: return "Stump Jump Pad";
        case 0x0A: return "Tongue Platform";
        case 0x0B: return "Switch";
        case 0x0C: return "Start Infinite Wheels";
        case 0x0D: return "Start Infinite Minecarts";
        case 0x0F: return "*Unk";
        case 0x10: return "Mine Cart";
        case 0x11: return "Ride Cart (Right)";
        case 0x12: return "Exploding Barrel";
        case 0x13: return "Bounce Web Horizontal";
        case 0x14: return "Bounce Web Angled (Right)";
        case 0x15: return "Swing Vine (Short)"; // Listed as 0000 - Check E6 again
        case 0x16: return "Swing Vine (Long)"; // Listed as 0000 - Check E6 again
        case 0x17: return "Gland";
        case 0x18: return "Ride Cart (Left)";
        case 0x1A: return "One-Way Door (Right)";
        case 0x1B: return "One-Way Door (Left)";
        case 0x1C: return "Thrusting Flail Trap (Unused?)";
        case 0x1D: return "Flail Trap (In/Out)";
        case 0x1F: return "Fall Branch (Left)";
        case 0x21: return "Lvl4 Temp Platform";
        case 0x22: return "Duplicate of 0x23 (Unused)";
        case 0x23: return "Lvl5 Temp Platform";
        case 0x24: return "Bounce Web Angled (Left)";
        case 0x25: return "Bounce Web Vertical";
        case 0x26: return "Lvl4 Switch (B)";
        case 0x28: return "Falling Rocks FX";
        case 0x29: return "Lvl4 Switch (C)";
        case 0x2A: return "Lvl4 Switch Left (A)";
        case 0x2B: return "Floor Door";
        case 0x2C: return "Door (Right)";
        case 0x2D: return "Fall Branch (Right)";
        case 0x2E: return "*Warp";
        case 0x31: return "Fall Rock Platform";
        case 0x32: return "*Uses tongue sprite";
        case 0x34: return "Unused";
        case 0x35: return "Lvl3 Unk (Cart Trigger?)";
        case 0x36: return "Checkpoint Totem (Right)";
        case 0x37: return "Lv4 Floor Spike";
        case 0x38: return "Lv4 Ceiling Spike";
        case 0x39: return "Checkpoint Totem (Left)";
        case 0x3A: return "Flail Trap (Rotate)";
        case 0x3B: return "Swinging Fire";
        case 0x3D: return "Flame Trap";
        case 0x3F: return "Door (Left)";
        case 0x40: return "Heart";
        case 0x41: return "Heart Duplicate (Unused)";
        case 0x42: return "Heart Duplicate (Unused)";
        case 0x43: return "Lvl4 Switch (A)";
        case 0x44: return "Copan Temple Jump Secret";
        case 0x45: return "!!!Dead Entity!!!";
        case 0x46: return "Bonus Warp";
        case 0x47: return "Super Stone Ammo";
        case 0x48: return "Boomerang";
        case 0x4A: return "Possibly Bonus Level Related";
        case 0x4F: return "Ceiling Spike (Proximity)";
        case 0x50: return "Jump Pepper";
        case 0x51: return "Super Heart";
        case 0x54: return "Time Stop";
        case 0x58: return "Gold Bar";
        case 0x59: return "1 Up";
        case 0x5A: return "Coin";
        case 0x5B: return "Silver Bar";
        case 0x5C: return "Ring";
        case 0x5E: return "Giant Rolling Stone";
        case 0x60: return "Lv1 Jaguar Boss";
        case 0x61: return "Lv4 Jaguar Boss";
        case 0x63: return "Lv8 Jaguar Boss";
        case 0x65: return "Bug";
        case 0x6E: return "Floor Snake Hole";
        case 0x6F: return "Wall Snake Hole";
        case 0x70: return "Bat";
        case 0x71: return "Bat Pair";
        case 0x72: return "Unused";
        case 0x73: return "Hanging Snake (Lvl4)";
        case 0x74: return "Snake (Floor Hole)";
        case 0x75: return "Snake (Wall Hole)";
        case 0x7A: return "Rat";
        case 0x7B: return "Rat Trio";
        case 0x7C: return "Rope Rat 1";
        case 0x7D: return "Snake (No hole)";
        case 0x7F: return "Rope Rat 2";
        case 0x80: return "Hawk";
        case 0x81: return "Hawk 2";
        case 0x82: return "Walking Monkey";
        case 0x84: return "Hanging Monkey (Right)";
        case 0x85: return "Hanging Monkey (Left)";
        case 0x87: return "Snake (Floor Hole 2)";
        case 0x88: return "Unused";
        case 0x8A: return "Crock Moving Right then Left (Unused)";
        case 0x8B: return "Crock - Open Jaw";
        case 0x8C: return "Crock Jumping Higher (Unused)";
        case 0x8D: return "Crock Jumping";
        case 0x8E: return "Crock Moving Right";
        case 0x8F: return "Crock Moving Left (Unused)";
        case 0x90: return "Skeleton Warrior (Morphing)";
        case 0x91: return "Skeleton Warrior (Sniping)";
        case 0x92: return "Skeleton Warrior (Running)";
        case 0x93: return "Skeleton Warrior - Unused Version";
        case 0x94: return "Bouncing Skull";
        case 0x95: return "Swinging Statue";
        case 0x96: return "Hanging Snake";
        case 0x97: return "Axe Throwing Gargoyle";
        case 0x9A: return "Mayan Archer";
        case 0x9E: return "Mayan Sorcerer";
        case 0xA1: return "Turtle Platform";
        case 0xA6: return "Boar";
        case 0xB0: return "Needle Spitter Thing (Floor)";
        case 0xB1: return "Needle Spitter Thing (Ceiling)";
        case 0xB2: return "Floor Spider";
        case 0xB3: return "Ceiling Spider";
        case 0xBB: return "Crock (Left)";
        case 0xBE: return "Atari Scorpion";
        case 0xBF: return "Warrior Spirit Boss";
        case 0xC9: return "Temple Floating Platform";
        case 0xCE: return "Continue Sign";
        case 0xD3: return "Floor Pot (A)";
        case 0xD4: return "Floor Pot (B)";
        case 0xD5: return "Hanging Pot";
        case 0xD6: return "Unused";
        case 0xD9: return "Fish FX";
        case 0xDC: return "Leaf FX";
        case 0xE0: return "Water Drip FX";
        case 0xE3: return "Torch FX (Right)";
        case 0xE4: return "Water Drip FX/Torch FX (Left)";
        case 0xE6: return "!!!Dead Entity!!!";
        case 0xEA: return "Swining Vine Base FX";
        case 0xEB: return "Vine FX";
        case 0xEF: return "Glowing Eyes FX";
        case 0xF0: return "Letter - P";
        case 0xF1: return "Letter - I";
        case 0xF2: return "Letter - T";
        case 0xF3: return "Letter - F";
        case 0xF4: return "Letter - A";
        case 0xF5: return "Letter - L";
        case 0xF6: return "Letter - L";
        default: return 0;
    }
}

pf_sprite* test;
pf_level level;

SDL_Surface* surface;
SDL_Surface* surfaceBG;
SDL_Texture* texture;
SDL_Texture* textureBG;

int offsetX = 0, offsetY = 0;

int scale = 1;

int mouseX, mouseY;
int lastOffset = 0;
int mouseDown = 0;
int printedTest = 0;

void pf_loadInit()
{
    ph_open("init");
    ph_nextFont("font.pcs");
    ph_nextFont("scoline.pcs");
    ph_nextSprite("fxrbmrng.pc");
    ph_nextSprite("fxrbmrot.pc");
    ph_nextSprite("fxzdeath.pc");
    ph_nextSprite("fxrdust2.pc");
    ph_nextSprite("fx_deat2.pc");
    ph_nextSprite("fx_expl3.pc");
    ph_nextSprite("fx_hrtbt.pc");
    ph_nextSprite("fx_mls.pc");
    ph_nextSprite("fx_stone.pc");
    ph_nextSprite("fx_sprk1.pc");
    ph_nextSprite("fx_sprk2.pc");
    ph_nextSprite("mi_1up.pc");
    ph_nextSprite("mi_chili.pc");
    ph_nextSprite("mi_coin.pc");
    ph_nextSprite("mi_croc.pc");
    ph_nextSprite("mi_gold.pc");
    ph_nextSprite("mi_life.pc");
    ph_nextSprite("mi_pouc2.pc");
    test= ph_nextSprite("mi_ptfal.pc");
    ph_nextSprite("mi_ring.pc");
    ph_nextSprite("mi_silvr.pc");
    ph_nextSprite("mi_stone.pc");
    ph_nextSprite("mi_stonb.pc");
    ph_nextSprite("mi_time.pc");
    ph_nextSprite("mirbmrng.pc");
    ph_nextSprite("obrston0.pc");
    ph_nextSprite("ob_pouch.pc");
    ph_nextSprite("ob_sling.pc");
    ph_nextSprite("sc_eyes1.pc");
    ph_nextSprite("sc_eyes2.pc");
    ph_nextSprite("ltr_lg.pc");
    ph_nextSprite("ltr_md.pc");
    ph_nextSprite("ltr_sm.pc");
    ph_nextSprite("scoline.pc");
    ph_nextSprite("hatman.pc");
    ph_nextSprite("hyibflip.pc");
    ph_nextSprite("hyibland.pc");
    ph_nextSprite("hyiblrec.pc");
    ph_nextSprite("hyibmrng.pc");
    ph_nextSprite("hyibng3b.pc");
    ph_nextSprite("hyibngab.pc");
    ph_nextSprite("hyibngac.pc");
    ph_nextSprite("hyibngbc.pc");
    ph_nextSprite("hyibngrv.pc");
    ph_nextSprite("hyibung1.pc");
    ph_nextSprite("hyibung2.pc");
    ph_nextSprite("hyibung3.pc");
     ph_nextSprite("hyicl2rn.pc");
    ph_nextSprite("hyicr2cl.pc");
    ph_nextSprite("hyicrcyc.pc");
    ph_nextSprite("hyicrtrn.pc");
    ph_nextSprite("hyicrwhp.pc");
    ph_nextSprite("hyidazed.pc");
    ph_nextSprite("hyidie.pc");
    ph_nextSprite("hyiding.pc");
    ph_nextSprite("hyidrope.pc");
    ph_nextSprite("hyidvine.pc");
    ph_nextSprite("hyidzip.pc");
    ph_nextSprite("hyiemrg.pc");
    ph_nextSprite("hyienter.pc");
    ph_nextSprite("hyifall.pc");
    ph_nextSprite("hyifcrwl.pc");
    ph_nextSprite("hyigland.pc");
    ph_nextSprite("hyihang.pc");
    ph_nextSprite("hyihjump.pc");
    ph_nextSprite("hyihshot.pc");
    ph_nextSprite("hyihwall.pc");
    ph_nextSprite("hyihwhip.pc");
    ph_nextSprite("hyijp2sn.pc");
    ph_nextSprite("hyilean.pc");
    ph_nextSprite("hyilooka.pc");
    ph_nextSprite("hyilsbal.pc");
    ph_nextSprite("hyimrop2.pc");
    ph_nextSprite("hyimzip.pc");
    ph_nextSprite("hyininja.pc");
    ph_nextSprite("hyipee.pc");
    ph_nextSprite("hyipsbal.pc");
    ph_nextSprite("hyipull.pc");
    ph_nextSprite("hyipulup.pc");
    ph_nextSprite("hyipush.pc");
    ph_nextSprite("hyird2rn.pc");
    ph_nextSprite("hyiready.pc");
    ph_nextSprite("hyirn2cl.pc");
    ph_nextSprite("hyirn2sn.pc");
    ph_nextSprite("hyiroped.pc");
    ph_nextSprite("hyirsht1.pc");
    ph_nextSprite("hyirtrn2.pc");
    ph_nextSprite("hyirun.pc");
    ph_nextSprite("hyirun2.pc");
    ph_nextSprite("hyirwhip.pc");
    ph_nextSprite("hyirwhpr.pc");
    ph_nextSprite("hyishoot.pc");
    ph_nextSprite("hyisink.pc");
    ph_nextSprite("hyiskte1.pc");
    ph_nextSprite("hyiskte2.pc");
    ph_nextSprite("hyiskte3.pc");
    ph_nextSprite("hyiskte4.pc");
    ph_nextSprite("hyislice.pc");
    ph_nextSprite("hyisomr1.pc");
    ph_nextSprite("hyisomr2.pc");
    ph_nextSprite("hyisomr3.pc");
    ph_nextSprite("hyispin.pc");
    ph_nextSprite("hyisprng.pc");
    ph_nextSprite("hyisspi2.pc");
    ph_nextSprite("hyisswng.pc");
    ph_nextSprite("hyist2cr.pc");
    ph_nextSprite("hyist2pu.pc");
    ph_nextSprite("hyisvine.pc");
    ph_nextSprite("hyitrip1.pc");
    ph_nextSprite("hyitwirl.pc");
    ph_nextSprite("hyiurope.pc");
    ph_nextSprite("hyivgrab.pc");
    ph_nextSprite("hyivjump.pc");
    ph_nextSprite("hyivwhip.pc");
    ph_nextSprite("hyiwhip.pc");
    ph_nextSprite("hyiwhiph.pc");
    ph_nextSprite("hyizen.pc");
    ph_nextSprite("hyizip.pc");
    ph_close();
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

void loadLevel11()
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

void drawSprite(int posX, int posY, pf_sprite* sprite, int frame)
{
    int x = 0, y = 0;
    for (int i = 0; i < sprite->numFrames; i++)
    {
        SDL_Rect dst; dst.x = posX; dst.y = posY; dst.w = sprite->frames[frame].width * 4; dst.h = sprite->frames[frame].height * 4;

        x++;
        if (x > 10)
        {
            x = 0;
            y++;
        }

        SDL_RenderCopy(sdlInfo.renderer, texture, 0, &dst);
        printf("%s\n", SDL_GetError());
    }
}

void drawBG(int posX, int posY, int tileNum)
{
    SDL_Rect src; src.x = (tileNum % level.bgMain->tilesetWidth) * 8; src.y = (tileNum / level.bgMain->tilesetWidth) * 8; src.w = 8; src.h = 8;
    SDL_Rect dst; dst.x = posX*8 * scale; dst.y = posY*8 * scale; dst.w = 8 * scale; dst.h = 8 * scale;
    
    SDL_RenderCopy(sdlInfo.renderer, textureBG, &src, &dst);
}

void drawLevelData(int posX, int posY, pf_lvl_data* data)
{
    SDL_Rect dst; 

    if (!data)
        return;

    for (int x = 0; x < data->width; x++)
    {
        if (((short*)data->data)[x] != 0)
        {
            unsigned short offset = ((short*)data->data)[x];
            offset = offset << 8 | offset >> 8;
            unsigned short* yData= data->data + offset;

            while ((*((unsigned char*)yData)) != 0xFF)
            {
                unsigned short yCoord = *yData & 0xFF;
                dst.x = ((posX * 8) + (x * 8 * 2 )) * scale; dst.y = ((posY * 8) + (yCoord * 8*2)) * scale; dst.w = 16 * scale; dst.h = 16 * scale;

                if (mouseDown && lastOffset != (unsigned char*)yData - (unsigned char*)data->data && mouseX != -1 && mouseX >= dst.x && mouseX <= dst.x + dst.w)
                {
                    if (mouseY != -1 && mouseY >= dst.y && mouseY <= dst.y + dst.h)
                    {
                        //printf("Touching obj. Offset: 0x%x, Val: 0x%x, Name: %s\n", (unsigned char*)yData - (unsigned char*)data->data, (*yData >> 8) & 0xFF, entName((*yData >> 8) & 0xFF));
                        printf("Touching obj. Offset: 0x%x, Val: 0x%x\n", (unsigned char*)yData - (unsigned char*)data->data, (*yData >> 8) & 0xFF);
                        lastOffset = (unsigned char*)yData - (unsigned char*)data->data;
                    }
                }

                if (!printedTest && entName((*yData >> 8) & 0xFF) == 0)
                {
                    printedTest = 1;
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
    printedTest = 1;


}

void render()
{
    SDL_SetRenderDrawColor(sdlInfo.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlInfo.renderer);

    for (int y = 0; y < level.bgMain->height; y++)
    {
        for (int x = 0; x < level.bgMain->width; x++)
        {
            drawBG(offsetX + x, offsetY + y, level.bgMain->layout[(y * level.bgMain->width) + x] & 0xFFF);
        }
    }

    drawLevelData(offsetX, offsetY, level.trg);
   // drawSprite(10, 10, test, 0);


    SDL_RenderPresent(sdlInfo.renderer);
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{

        SDL_GetMouseState(&mouseX, &mouseY);
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
                offsetX++;
				break;
			case SDLK_RIGHT:
                offsetX--;
				break;
			case SDLK_UP:
                offsetY++;
				break;
			case SDLK_DOWN:
                offsetY--;
				break;
            case SDLK_PAGEUP:
                scale++;
                break;
            case SDLK_PAGEDOWN:
                scale--;
                if (scale <= 0)
                    scale = 1;
                break;
			default:
				break;
			}
			break;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown = 1;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDown = 0;
            lastOffset = 0;
            break;
		case SDL_QUIT:
			exit(0); 
			break;

		default:
			break;
		}
	}
}

void loadSprite(pf_sprite* test, int frame)
{
#ifdef PF_GFX_USE_ALPHA
    surface = SDL_CreateRGBSurfaceWithFormatFrom(test->frames[frame].data, test->frames[frame].width, test->frames[frame].height, PF_GFX_BPP * 8, test->frames[frame].width * PF_GFX_BPP, SDL_PIXELFORMAT_RGBA32);
#else
    surface = SDL_CreateRGBSurfaceWithFormatFrom(test->frames[frame].data, test->frames[frame].width, test->frames[frame].height, PF_GFX_BPP * 8, test->frames[frame].width * PF_GFX_BPP, SDL_PIXELFORMAT_RGB24);
#endif
    texture = SDL_CreateTextureFromSurface(sdlInfo.renderer, surface);
}

int main(int argc, char* argv[])
{
    printf("Starting SDL\n");

	initSDL(&sdlInfo);

    pf_memInit(PF_MAX_MEM);
    pf_loadInit();
    loadLevel2();
    printf("Total mem used after loading: %d bytes.\n", pf_memNormalUsed());

    loadSprite(test, 0);

#ifdef PF_GFX_USE_ALPHA
    surfaceBG = SDL_CreateRGBSurfaceWithFormatFrom(level.bgMain->tileset, 100, 100, PF_GFX_BPP * 8, 8 * PF_GFX_BPP, SDL_PIXELFORMAT_RGBA32);
#else
    surfaceBG = SDL_CreateRGBSurfaceWithFormatFrom(level.bgMain->tileset, level.bgMain->tilesetWidth * 8, level.bgMain->tilesetHeight * 8, PF_GFX_BPP * 8, level.bgMain->tilesetWidth * 8 * PF_GFX_BPP, SDL_PIXELFORMAT_RGB24);
#endif
    printf("%s\n", SDL_GetError());
    textureBG = SDL_CreateTextureFromSurface(sdlInfo.renderer, surfaceBG);
    printf("%s\n", SDL_GetError());

	printf("Entering loop\n");

	while (1)
	{
		render();
		doInput();
		SDL_Delay(16);
	}

	return 0;
}