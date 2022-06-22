//---------------------------------------------------------------------------
///// ����� ������� ��� ������/////
#pragma hdrstop

#include "Utils.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)

HANDLE CreateDeviceHandle(UnicodeString path) {
	wchar_t deviceName[20];
	// �������� �� path ������ ������ ������
	swprintf(deviceName, L"\\\\.\\%c:", path.w_str()[0]);

	// ������ handle ��� �����
	HANDLE fileHandle = CreateFileW(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return fileHandle;
}

bool CreateFilePointer(HANDLE FileHandle, UINT64 offset) {
	// ��������������� � �����
	LARGE_INTEGER sectorOffset;
	// �������� �� ������ ��������
	sectorOffset.QuadPart = offset;

	// ����� �������
	DWORD currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

 	return currentPosition == sectorOffset.LowPart;
}

bool ReadData(HANDLE FileHandle, char* dataBuffer, DWORD bytesToRead) {
	DWORD bytesRead; 	    	// ������� ������ ������� �������

	// ������ ������
	bool readResult = ReadFile(
		FileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	// ���������� true, ���� �� ������ ���������
	return readResult && bytesRead == bytesToRead;
}
