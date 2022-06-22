//---------------------------------------------------------------------------
#ifndef exFATH
#define exFATH
#include <cmath>
#include "AbstractFileSystem.h"
#include "Signatures.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
// Спецификация файловой системы exFAT (https://docs.microsoft.com/ru-ru/windows/win32/fileio/exfat-specification)
// Структура загрузочной записи
typedef struct {
	char JumpBoot[3];

	char OEM[8];                   				// Сигнатура ФС
	char MustBeZero[53];
	unsigned long long PartitionOffset;
	unsigned long long VolumeLength; 			// Кол-во секторов в ФС
	unsigned int FatOffset;        				// Сектор, в котором начинается FAT
	unsigned int FatLength;						// Размер FAT в секторах
	unsigned int ClusterHeapOffset;				// Сектор начала битовой карты
	unsigned int ClusterCount;					// Кол-во кластеров в ФС
	unsigned int FirstClusterOfRootDirectory;	// Кластер корневого каталога
	unsigned int VolumeSerialNumber;			// Серийный номер тома
	unsigned short FileSystemRevision;
	unsigned short VolumeFlags;

	unsigned char BytesPerSectorShift;     		// Размер сектора (степень 2)
	unsigned char SectorsPerClusterShift; 		// Кластерный множитель (степень 2)

} exFAT_BootRecord;
#pragma pack(pop)

// Класс-наследник от AbstractFileSystem
class exFAT : public AbstractFileSystem {
	public:
		exFAT(HANDLE FileHandle);   // свой конструктор
		IteratorFS* GetIterator();
};

// Декоратор итератора
class exFATIterator : public IteratorFS {
	public:
		exFATIterator(AbstractFileSystem* FileSystem);

};
#endif
