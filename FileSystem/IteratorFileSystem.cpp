//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//IteratorFS::IteratorFS(AbstractFileSystem* FileSystem)
//	: FileSystem(FileSystem)
//{
//	// Объявляем буфер для кластера с нужным размером
//	clusterBuffer = new char[FileSystem->GetClusterSize()];
//
//	// Начальная позиция чтения
//	currentPosition = 0;
//	done = false;
//}
//
//IteratorFS::~IteratorFS() {
//	// Очистка буфера при удалении итератора
//	delete[] clusterBuffer;
//}
//
//void IteratorFS::First() {
//	// Читаем нулевой кластер
//	if (!FileSystem->ReadCluster(clusterBuffer, 0)) {
//		done = true;
//	}
//}
//
//void IteratorFS::Next() {
//	currentPosition++;
//	// Читаем кластер по номеру currentPosition
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

