//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//IteratorFS::IteratorFS(AbstractFileSystem* FileSystem)
//	: FileSystem(FileSystem)
//{
//	// ��������� ����� ��� �������� � ������ ��������
//	clusterBuffer = new char[FileSystem->GetClusterSize()];
//
//	// ��������� ������� ������
//	currentPosition = 0;
//	done = false;
//}
//
//IteratorFS::~IteratorFS() {
//	// ������� ������ ��� �������� ���������
//	delete[] clusterBuffer;
//}
//
//void IteratorFS::First() {
//	// ������ ������� �������
//	if (!FileSystem->ReadCluster(clusterBuffer, 0)) {
//		done = true;
//	}
//}
//
//void IteratorFS::Next() {
//	currentPosition++;
//	// ������ ������� �� ������ currentPosition
//	if (!FileSystem->ReadCluster(clusterBuffer, currentPosition)) {
//		done = true;
//	}
//}
//
//bool IteratorFS::IsDone() {
//	return done || currentPosition + 1 >= FileSystem->GetClusterCount();
//}
//
//char* IteratorFS::GetCurrent() {
//	return clusterBuffer;
//}

