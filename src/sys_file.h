#pragma once
#ifndef _SYS_FILE_H_
#define _SYS_FILE_H_

typedef enum PF_FILEMODE {
	PF_FILE_READ,
	PF_FILE_WRITE,
	PF_FILE_READWRITE,
} PF_FILEMODE;

#ifdef _WIN32 || _WIN64
#include <stdio.h>
#define PF_FILE FILE
#endif

PF_FILE* sys_openFile(const char* path, PF_FILEMODE op);
int sys_readFile(PF_FILE* handle, void* buff, int buffSize, int length);
int sys_writeFile(PF_FILE* handle, void* buff, int buffSize, int length);
int sys_seekFile(PF_FILE* handle, int offset);
void sys_closeFile(PF_FILE* handle);

#endif