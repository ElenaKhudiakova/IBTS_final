//---------------------------------------------------------------------------

#pragma hdrstop

#include "FactoryFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


FSType FindFileSystemType(HANDLE FileHandle) {
	char dataBuffer[512];         // Считываем первый сектор
	// Позиционируемся в файле
	LARGE_INTEGER sectorOffset;           // LARGE_INTEGER - 64-разрядное целое значение со знаком
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
		return NULL;
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

	if (!(readResult && bytesRead == bytesToRead)) {
		return NULL;
	}

	// Проверяем наличие ключевого слова в загрузочном секторе
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
