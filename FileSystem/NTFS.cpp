//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

NTFS::NTFS(HANDLE FileHandle)
	: AbstractFileSystem(FileHandle) {
	char dataBuffer[512];
	// Позиционируемся в файле
	LARGE_INTEGER sectorOffset;
	// Смещение от начала кластера
	sectorOffset.QuadPart = 0;

	// Задаём позицию

	 // Члены структуры:
// LowPart	Определяет младшее 32 бита
// HighPart	Определяет старшие 32
// QuadPart	Определяет 64-х битное знаковое целое
	DWORD currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	if (currentPosition != sectorOffset.LowPart) {
		return;
	}

	DWORD bytesToRead = 512;				// Сколько байтов нужно прочитать
	DWORD bytesRead; 	    				// Сколько байтов удалось считать

	// Чтение данных
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

