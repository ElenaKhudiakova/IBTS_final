//---------------------------------------------------------------------------

#ifndef NoEmptyClusterDecoratorH
#define NoEmptyClusterDecoratorH
#include "IteratorFileSystem.h"
//---------------------------------------------------------------------------

class NoEmptyClusterDecorator : public IteratorFS {
	private:
		IteratorFS* Iterator;
	public:
		NoEmptyClusterDecorator(IteratorFS* Iterator);      // ������� ����� ���� ���������, ������� ����� �������������
		void First();
		void Next();
		bool IsDone();
		char* GetCurrent();
		DWORD GetCurrentPosition();
		AbstractFileSystem* GetFileSystem();
};
#endif

//
