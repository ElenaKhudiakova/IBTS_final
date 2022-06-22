//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH
#include <vcl.h>
//---------------------------------------------------------------------------
HANDLE CreateDeviceHandle(UnicodeString path);
bool CreateFilePointer(HANDLE FileHandle, UINT64 offset);
bool ReadData(HANDLE FileHandle, char* dataBuffer, DWORD bytesToRead);

#endif
