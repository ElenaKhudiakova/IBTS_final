//---------------------------------------------------------------------------
#ifndef NTFSH
#define NTFSH
#include "AbstractFileSystem.h"
#include "Signatures.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM[8];                           		// ��������� ��
	unsigned short SectorSize;					// ������ ������� � ������
	unsigned char ClusterSize;                  // ���-�� �������� � ����� ��������
	char Padding2[7];
	char DeviceType;							// ��� �������� ������
	char Padding3[18];

	unsigned long SectorsVolumeCount;  			// ����� ���������� �������� � �������

} NTFS_BootRecord;
#pragma pack(pop)

// �����-��������� �� AbstractFileSystem
class NTFS : public AbstractFileSystem {
	public:
		NTFS(HANDLE FileHandle);
		IteratorFS* GetIterator();
};

// ��������� ���������
class NTFSIterator : public IteratorFS {
	public:
		NTFSIterator(AbstractFileSystem* FileSystem);

};
#endif