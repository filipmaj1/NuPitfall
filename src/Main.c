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

int x = 0;
int y = 0;
void render()
{
    SDL_SetRenderDrawColor(sdlInfo.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlInfo.renderer);

    lvl_drawTiles(offsetX, offsetY);
   // lvl_drawLevelDataInfo(offsetX, offsetY, &printedTest, mouseX, mouseY, mouseDown, &lastOffset);
    gfx_drawSprite(119, 60, 280, x);

    y = (y + 1) % 3;
    if (y == 0)
        x++;

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

int main(int argc, char* argv[])
{
    printf("Starting SDL\n");

	initSDL(&sdlInfo);

    pf_memInit(PF_MAX_MEM);
    pf_loadInitData();
    pf_loadLevelData(2);
    printf("Total mem used after loading: %d bytes.\n", pf_memNormalUsed());

	printf("Entering loop\n");

	while (1)
	{
		render();
		doInput();
		SDL_Delay(16);
	}

	return 0;
}