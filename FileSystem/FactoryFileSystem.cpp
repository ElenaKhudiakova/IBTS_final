//---------------------------------------------------------------------------

#pragma hdrstop

#include "FactoryFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


FSType FindFileSystemType(HANDLE FileHandle) {
	char dataBuffer[512];         // ��������� ������ ������
	// ��������������� � �����
	LARGE_INTEGER sectorOffset;           // LARGE_INTEGER - 64-��������� ����� �������� �� ������
	// �������� �� ������ ��������
	sectorOffset.QuadPart = 0;

	// ����� �������
    // ����� ���������:
// LowPart	���������� ������� 32 ����
// HighPart	���������� ������� 32
// QuadPart	���������� 64-� ������ �������� �����
	DWORD currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	if (currentPosition != sectorOffset.LowPart) {
		return NULL;
	}

	DWORD bytesToRead = 512;				// ������� ������ ����� ���������
	DWORD bytesRead; 	    				// ������� ������ ������� �������

	// ������ ������
	bool readResult = ReadFile(
		FileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	if (!(readResult && bytesRead == bytesToRead)) {
		return NULL;
	}

	// ��������� ������� ��������� ����� � ����������� �������
	if (strstr(dataBuffer, "NTFS") != 0) {
		return FSType::NTFS_FS;
	}

	if (strstr(dataBuffer, "EXFAT") != 0) {
		return FSType::exFAT_FS;
	}

	return NULL;
}

AbstractFileSystem* CreateFileSystem(FSType Type, HANDLE FileHandle) {
	AbstractFileSystem* FileSystem;
	switch (Type) {
		case FSType::NTFS_FS:
			FileSystem = new NTFS(FileHandle);
			break;
		case FSType::exFAT_FS:
			FileSystem = new exFAT(FileHandle);
			break;
	}

	return FileSystem;
}
