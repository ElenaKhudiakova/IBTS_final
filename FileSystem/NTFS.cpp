//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

NTFS::NTFS(HANDLE FileHandle)
	: AbstractFileSystem(FileHandle) {
	char dataBuffer[512];
	// ��������������� � �����
	LARGE_INTEGER sectorOffset;
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
		NTFS_BootRecord* ntfsBR = (NTFS_BootRecord*) dataBuffer;
		clusterSize = (DWORD)(ntfsBR->SectorSize * ntfsBR->ClusterSize);
		clusterCount = (DWORD)(
				ntfsBR->SectorsVolumeCount
				* ntfsBR->SectorSize
				/ clusterSize
		);
		fileSystemSize = clusterSize*clusterCount;
	}
}

IteratorFS* NTFS::GetIterator() {
	return new NTFSIterator(this);
}

NTFSIterator::NTFSIterator(AbstractFileSystem* FileSystem)
	: IteratorFS(FileSystem)
{

}

