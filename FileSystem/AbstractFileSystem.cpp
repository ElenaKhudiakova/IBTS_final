//---------------------------------------------------------------------------
#pragma hdrstop

#include "AbstractFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

AbstractFileSystem::AbstractFileSystem(HANDLE FileHandle)
	: FileHandle(FileHandle)
{

}

AbstractFileSystem::~AbstractFileSystem()
{
	CloseHandle(FileHandle);
}


bool AbstractFileSystem::ReadCluster(char* dataBuffer, DWORD clusterNumber)
{
	// ��������������� � �����
	LARGE_INTEGER sectorOffset;
	// �������� �� ������ ��������
	sectorOffset.QuadPart = (LONGLONG)(clusterNumber*GetClusterSize());

	// ����� �������
	DWORD currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);
	// �������� ����������������
	if (currentPosition != sectorOffset.LowPart) {
		return false;
	}

	DWORD bytesToRead = GetClusterSize();	// ������� ������ ����� ���������
	DWORD bytesRead; 	    				// ������� ������ ������� �������

	// ������ ������
	bool readResult = ReadFile(
		FileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

    // ���� �������, �� �������� ���-�� ��������� ����
	return readResult && bytesRead == bytesToRead;
}

UINT64 AbstractFileSystem::GetFileSystemSize() {
	return fileSystemSize;
}

DWORD AbstractFileSystem::GetClusterCount() {
	return clusterCount;
}

DWORD AbstractFileSystem::GetClusterSize() {
	return clusterSize;
}


IteratorFS::IteratorFS(AbstractFileSystem* FileSystem)
	: FileSystem(FileSystem)      // �������� ���������� ���������� FileSystem � class AbstractFileSystem* FileSystem � .h
{
	// ��������� ����� ��� �������� � ������ ��������
	clusterBuffer = new char[FileSystem->GetClusterSize()];

	done = false;   // ������ �� ���������
}

// ����������
IteratorFS::~IteratorFS() {
	// ������� ������ ��� �������� ���������
	delete[] clusterBuffer;
}

void IteratorFS::First() {
	// ��������� ������� ������
	currentPosition = 0;

	// ������ ������� �������
	if (!FileSystem->ReadCluster(clusterBuffer, 0)) {
		done = true;    // ���� ������ ������, �� ���� - ��������� ������
	}
}

void IteratorFS::Next() {
	currentPosition++;    //����������� ������� ������� �� 1
	// ������ ������� �� ������ currentPosition
	if (!FileSystem->ReadCluster(clusterBuffer, currentPosition)) {
		done = true;
	}
}

// �������� ���������� ������
// ���� �� �������� ������, �� ������� "currentPosition + 1", ������� �� ��� �������� �� ������� ���������?
bool IteratorFS::IsDone() {
	return done || currentPosition + 1 >= FileSystem->GetClusterCount();
}

char* IteratorFS::GetCurrent() {       // ���������� ������� ����������� ������� ��� ���������� ������
	return clusterBuffer;
}

// ��������� ������ ��� ����������
DWORD IteratorFS::GetCurrentPosition() {      // ������� �������
	return currentPosition;
}

AbstractFileSystem* IteratorFS::GetFileSystem() {     // ������� ��
	return FileSystem;
}


