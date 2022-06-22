//---------------------------------------------------------------------------
#ifndef exFATH
#define exFATH
#include <cmath>
#include "AbstractFileSystem.h"
#include "Signatures.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
// ������������ �������� ������� exFAT (https://docs.microsoft.com/ru-ru/windows/win32/fileio/exfat-specification)
// ��������� ����������� ������
typedef struct {
	char JumpBoot[3];

	char OEM[8];                   				// ��������� ��
	char MustBeZero[53];
	unsigned long long PartitionOffset;
	unsigned long long VolumeLength; 			// ���-�� �������� � ��
	unsigned int FatOffset;        				// ������, � ������� ���������� FAT
	unsigned int FatLength;						// ������ FAT � ��������
	unsigned int ClusterHeapOffset;				// ������ ������ ������� �����
	unsigned int ClusterCount;					// ���-�� ��������� � ��
	unsigned int FirstClusterOfRootDirectory;	// ������� ��������� ��������
	unsigned int VolumeSerialNumber;			// �������� ����� ����
	unsigned short FileSystemRevision;
	unsigned short VolumeFlags;

	unsigned char BytesPerSectorShift;     		// ������ ������� (������� 2)
	unsigned char SectorsPerClusterShift; 		// ���������� ��������� (������� 2)

} exFAT_BootRecord;
#pragma pack(pop)

// �����-��������� �� AbstractFileSystem
class exFAT : public AbstractFileSystem {
	public:
		exFAT(HANDLE FileHandle);   // ���� �����������
		IteratorFS* GetIterator();
};

// ��������� ���������
class exFATIterator : public IteratorFS {
	public:
		exFATIterator(AbstractFileSystem* FileSystem);

};
#endif
