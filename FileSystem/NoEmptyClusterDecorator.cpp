//---------------------------------------------------------------------------

#pragma hdrstop

#include "NoEmptyClusterDecorator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

NoEmptyClusterDecorator::NoEmptyClusterDecorator(IteratorFS* Iterator)
	: IteratorFS(Iterator->GetFileSystem()), Iterator(Iterator)
{

}

// ��������������� ����� First() �� IteratorFS
void NoEmptyClusterDecorator::First() {
	Iterator->First();

	while (true) {
		// ���� �� ������� ���������, �� ��������� ������
		if (Iterator->IsDone()) {
			return;
		}

		// �������� ������� �������
		char* clusterBuffer = Iterator->GetCurrent();

		// ���������
		// ���� ������ �������� ������, �� �������, ��� ���� ������� ������ (������)
		if (clusterBuffer[0] == 0x00) {
			// ���� ������� �������, �� ������ ��������� ������� � ������� �������  Next
			Iterator->Next();
		} else {
			break;
		}
	}
}    // ���� ������� �� ������, �� ����������� ������ ������� First

void NoEmptyClusterDecorator::Next() {
	Iterator->Next();

	while (true) {
		// ���� �� ������� ���������, �� ��������� ������
		if (Iterator->IsDone()) {
			return;
		}

		// �������� ������� �������
		char* clusterBuffer = Iterator->GetCurrent();

		// ���������
		// ���� ������ �������� ������, �� �������, ��� ���� ������� ������
		if (clusterBuffer[0] == 0x00) {
			// ������ ��������� �������
			Iterator->Next();
		} else {
			break;
		}
	}
}

//���������� � ����������� ���������

bool NoEmptyClusterDecorator::IsDone() {
	return Iterator->IsDone();
}

char* NoEmptyClusterDecorator::GetCurrent() {
	return Iterator->GetCurrent();
}

DWORD NoEmptyClusterDecorator::GetCurrentPosition() {      // ��� ������ ��������� � ProgressBar1
	return Iterator->GetCurrentPosition();
}

AbstractFileSystem* NoEmptyClusterDecorator::GetFileSystem() {
	return Iterator->GetFileSystem();
}

