#pragma once
#ifndef _PF_MEM_H_
#define _PF_MEM_H_

#define PF_MEMMARKER void*

int pf_memInit(int totalMem);

void* pf_memAlloc(const char* label, int size);
void* pf_memAllocMore(int memSize);
PF_MEMMARKER pf_memMark();
void pf_memFree(PF_MEMMARKER marker);
void pf_memClear();

void* pf_memAllocScratch(int memSize);
void pf_memClearScratch();

void pf_memDestroy();

int pf_memNormalUsed();
int pf_memScratchUsed();
int pf_memTotalUsed();
int pf_memTotalAvailable();

#endif