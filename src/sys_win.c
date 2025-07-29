#include "sys_file.h"
#include <errno.h>

PF_FILE* sys_openFile(const char* path, PF_FILEMODE mode)
{
	PF_FILE* handle = 0;
	errno_t result;

	if (mode == PF_FILE_READ)
		result = fopen_s(&handle, path, "rb");
	else if (mode == PF_FILE_WRITE)
		result = fopen_s(&handle, path, "wb");
	else if (mode == PF_FILE_READWRITE)
		result = fopen_s(&handle, path, "r+b");

	if (result == ENOENT)
		return -1;

	return handle;
}

int sys_readFile(PF_FILE* handle, void* buff, int buffSize, int length)
{
	return fread_s(buff, buffSize, length, 1, handle);
}

int sys_writeFile(PF_FILE* handle, void* buff, int length)
{
	return fwrite(buff, 1, length, handle);
}

int sys_seekFile(PF_FILE* handle, int offset)
{
	return fseek(handle, offset, SEEK_SET);
}

void sys_closeFile(PF_FILE* handle)
{
	fclose(handle);
}