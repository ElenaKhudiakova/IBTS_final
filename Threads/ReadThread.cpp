//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ReadThread::ReadThread(bool CreateSuspended, IteratorFS* Iterator, TForm1* Form1, bool useSignatureSearch)
	: TThread(CreateSuspended), Iterator(Iterator), Form1(Form1)
{
	FreeOnTerminate = true; // ��� �������� ������ �������� ��������, ����� ��� �������� ������ ���� ��������������� ��������
	this->MyEvent = new TEvent(NULL, true, false, "", false);   // this ���������� ��� ������ �� ����� ����, ��� ������������ �����������
	this->ProcessThreadPtr = new ProcessThread(true, MyEvent, Iterator->GetFileSystem()->GetClusterSize(), Form1, useSignatureSearch);
}
// TEvent(NULL, true, false, "", false) ����� �� ������
// ProcessThread(true, MyEvent, Iterator->GetFileSystem()->GetClusterSize(), Form1, useSignatureSearch);
// true - �������� �� ��, ��� ������� ����� ������� �� ������� ProcessThreadPtr->Start()
// Iterator->GetFileSystem()->GetClusterSize() - �������� ������ ��������
// Form1 - ��� ����� � ������
// useSignatureSearch  - �������� �� ������, ����� �� ������ ���������
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
	//---- Place thread code here ----
	Synchronize(&OnStart);
	ProcessThreadPtr->Start(); // ��������� �����, ������� ����� ������������ ������

	// ������� ������ ��������� - ������� � ����� ����������, ��� ���� ��� ������ ������ ������� � ProcessThread
	// ����� ����������� ������� "�� ��������� �� ������?",
	// ������ ��������� - ���� ������ ���������, �� ��� ���������� ��� ��������� ��������
	for (Iterator->First(); !Iterator->IsDone(); Iterator->Next()) {
		if (Terminated) break;

		// ������� ������� ������ ��������� �������
		ProcessThreadPtr->receivedBuffer = Iterator->GetCurrent();
		ProcessThreadPtr->clusterNumber = Iterator->GetCurrentPosition(); // clusterNumber - ������� �������

		Synchronize(&OnProgress);

		// ��������� ������ (������ ����� �������� ������������ ���������� �������)
		MyEvent->SetEvent();

		// ���� ���� - ������� ������ ������ (MyEvent->ResetEvent) �� ������� ������
		while (MyEvent->WaitFor(0) == wrSignaled)
		{
			// ���� ������ ������ ��������� ������������� �� �����
			if(Terminated) break;
		}
	}

	ProcessThreadPtr->Terminate();   // ��������� ����� ��������

	Synchronize(&OnStop);
	ProcessThreadPtr->WaitFor();  // ����, ���� ProcessThread �� ���������� (������)

	delete ProcessThreadPtr;   // ������� ��������� �� ����� (������)
}
//---------------------------------------------------------------------------

void __fastcall ReadThread::OnStart() {
	Form1->DeleteAllButton->Enabled = false;
	Form1->DeleteButton->Enabled = false;
	Form1->EmptyClusterToggleSwitch->Enabled = false;
	Form1->SearchSignToggleSwitch->Enabled = false;
}

void __fastcall ReadThread::OnProgress() {
	Form1->ProgressBar1->Position = Iterator->GetCurrentPosition();
	Form1->ProgressLabel->Caption = UnicodeString(Iterator->GetCurrentPosition());
// ������� ������� �������� � ���������
//	Form1->ProgressLabel->Caption = UnicodeString(
//			100
//			*(float)(Iterator->currentPosition+1)
//			/(float)(Iterator->FileSystem->GetClusterCount())
//	) + L"%";
}

void __fastcall ReadThread::OnStop() {
	Form1->ProgressBar1->Position = Form1->ProgressBar1->Max;   // ��������� �� �����
	Form1->ProgressLabel->Caption = Iterator->GetFileSystem()->GetClusterCount(); // ������� ��������� ����� ���������
	Form1->ScanToggleSwitch->State = tssOff;    // ���������  Switch, �� ���� ������ �� ����� "�����������"
	Form1->DeleteAllButton->Enabled = true;  // ������� ������ �������� �������
	Form1->DeleteButton->Enabled = true;
	Form1->EmptyClusterToggleSwitch->Enabled = true;  // ������������ ������ �� ������������
	Form1->SearchSignToggleSwitch->Enabled = true;
}
