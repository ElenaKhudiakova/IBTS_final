//---------------------------------------------------------------------------

#pragma hdrstop

#include "exFAT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

exFAT::exFAT(HANDLE FileHandle)
	: AbstractFileSystem(FileHandle) {
	char dataBuffer[512];
	// ��������������� � �����
	LARGE_INTEGER sectorOffset;       // LARGE_INTEGER - 64-��������� ����� �������� �� ������
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
		return;
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

	if (readResult && bytesRead == bytesToRead) {
		exFAT_BootRecord* exfatBR = (exFAT_BootRecord*) dataBuffer;
		clusterCount = (DWORD)(exfatBR->ClusterCount);
		clusterSize = (DWORD)(
				pow((double)2, exfatBR->BytesPerSectorShift)        //	pow - ���������� � �������
				* pow((double)2, exfatBR->SectorsPerClusterShift)    // � ����������� ������� ����������� �� ���� �������, � ������� ������
		);
		fileSystemSize = (UINT64)(clusterCount*clusterSize);
	}
}

// � ����������� �� main.h "class AbstractFileSystem* FileSystem" ���������� ����� exFATIterator
IteratorFS* exFAT::GetIterator() {
	return new exFATIterator(this);
}
// ��������� ���������� �������� ��� ������ ��

exFATIterator::exFATIterator(AbstractFileSystem* FileSystem)
	: IteratorFS(FileSystem)
{

}
