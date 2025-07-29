#include "PFMem.h"
#include <stdlib.h>
#include <string.h>

static unsigned char* memoryStart = 0;
static unsigned char* scratchStart = 0;

static unsigned char* currentPosition = 0;
static unsigned char* currentScratchPosition = 0;

static int totalMemorySize;

int pf_memInit(int totalMem)
{
	memoryStart = malloc(totalMem);

	if (memoryStart == 0)
		return 0;

	scratchStart = memoryStart + totalMem;
	totalMemorySize = totalMem;

	currentPosition = memoryStart;
	currentScratchPosition = scratchStart;

	memset(memoryStart, 0xAA, totalMem);
}

void* pf_memAlloc(const char* label, int memSize)
{
	if (currentPosition + 0x10 + memSize >= currentScratchPosition)
		return 0;

	void* ptr = currentPosition + 0x10;

	memcpy(currentPosition, label, 0x10);
	currentPosition[0xF] = 0;
	currentPosition += 0x10 + memSize;

	return ptr;
}

void* pf_memAllocMore(int memSize)
{
	if (currentPosition + memSize >= currentScratchPosition)
		return 0;

	void* ptr = currentPosition;
	currentPosition += memSize;
	return ptr;
}

void* pf_memAllocScratch(int memSize)
{
	if (currentScratchPosition - memSize <= currentPosition)
		return 0;

	void* ptr = currentScratchPosition - memSize;
	currentScratchPosition -= memSize;

	return ptr;
}

PF_MEMMARKER pf_memMark()
{
	return currentPosition;
}

void pf_memFree(PF_MEMMARKER marker)
{
	currentPosition = marker;
}

void pf_memClear()
{
	currentPosition = memoryStart;
}

void pf_memClearScratch()
{
	currentScratchPosition = scratchStart;
}

void pf_memDestroy()
{
	free(memoryStart);
	memoryStart = 0;
	scratchStart = 0;
	currentPosition = 0;
	currentScratchPosition = 0;
	totalMemorySize = 0;
}

int pf_memNormalUsed()
{
	return currentPosition - memoryStart;
}

int pf_memScratchUsed()
{
	return scratchStart - currentScratchPosition;
}

int pf_memTotalUsed()
{
	return pf_memNormalUsed() + pf_memScratchUsed();
}

int pf_memTotalAvailable()
{
	return totalMemorySize;
}