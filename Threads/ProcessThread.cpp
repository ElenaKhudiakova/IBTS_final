//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ProcessThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ProcessThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ProcessThread::ProcessThread(bool CreateSuspended, TEvent* MyEvent, DWORD bufferSize, TForm1* Form1, bool useSignatureSearch)
 : TThread(CreateSuspended), MyEvent(MyEvent), bufferSize(bufferSize), Form1(Form1), useSignatureSearch(useSignatureSearch)
{
	FreeOnTerminate = true; // ������� ��� ����������
	receivedBuffer = new char[bufferSize];  // ��������� ������
	copyBuffer = new char[bufferSize];
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
	//---- Place thread code here ----
	while (!Terminated)
	{
		// ��������� ���������� �� ���� (� ��������� � 0 ��)
		if (MyEvent->WaitFor(0) == wrSignaled)   // �������� 0 ���. wrsignaled, ���� ��������� ����������� �������, wrTimeout, ���� �� ����� ����-���� ������ �� ���������.
		{
			// �������� �����
			memcpy(copyBuffer, receivedBuffer, bufferSize);

			// ���������� ���� �������, ����� ReadThread ��������� ������
			MyEvent->ResetEvent();

			// �������� � copyBuffer
			if (useSignatureSearch) {
				clusterSignature = FindSignature(copyBuffer, Form1->SelectedSignatures); // ���� ��������� �� ���������� � �����
				if (clusterSignature == NULL) {
					continue; // ���� ��������� �� �������, �� ������ ������������
				}
			}

			// ������� ������ � ��
			addClusterToDB();
		}
	}  // ��� ��� ���� ������� ��� �������, �� ������� �� ��������� ����� �� ����� �����������.
    // ��-�� ����� ���� ����������� "� ��������" �� ��� ���, ���� ReadThread ����� �� �������� ������ MyEvent->SetEvent();

	Synchronize(&addClustersToVST);

	delete[] receivedBuffer, copyBuffer;
}
//---------------------------------------------------------------------------

bool ProcessThread::addClusterToDB() {
	// ��� 1 (���������� �������)
	const char* errmsg;  // ���������� ������
	sqlite3_stmt* pStatement; // ������ ������ � �� (����� � ���� ������)

	// ��������� ������� � ���� ������
	wchar_t sql[] = L"INSERT INTO scans (cluster_number, cluster_content, signature) VALUES (?, ?, ?);";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� INSERT ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return false;
	}

	// ����������� �������� ������ ?, ?, ?
	result = sqlite3_bind_int64(pStatement, 1, clusterNumber);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� INSERT ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return false;
	}

	result = sqlite3_bind_blob(pStatement, 2, copyBuffer, bufferSize, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� INSERT ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return false;
	}


	result = sqlite3_bind_text(pStatement, 3, GetSignatureName(clusterSignature), -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� INSERT ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return false;
	}

	// ��� 2 (���������� �������)
	result = sqlite3_step(pStatement);

	// ��������� ���������
	if (result != SQLITE_DONE) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� INSERT ��� ������� scans: " + UnicodeString(errmsg));

		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return false;
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);

	return true;
}

void  __fastcall ProcessThread::addClustersToVST() {
	TVirtualStringTree* VST = Form1->VirtualStringTree1;

	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� ������ � ����������� �������� �� ���������
	wchar_t sql[] = L"SELECT id, cluster_number, cluster_content, signature FROM scans;";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		VST->Clear();
		VST->BeginUpdate();

		// ��� 2 (���������� ������� � ��������� ���������� ��� ��������� �����)
		while (true) {
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			PVirtualNode entryNode = VST->AddChild(VST->RootNode);
			ScansTableStruct* nodeData = (ScansTableStruct*) VST->GetNodeData(entryNode);

			nodeData->Id = sqlite3_column_int64(pStatement, 0);
			nodeData->ClusterNumber = sqlite3_column_int64(pStatement, 1);
			nodeData->ClusterContent = UnicodeString(
					(char*) sqlite3_column_blob(pStatement, 2), // ���������� ��������
					sqlite3_column_bytes(pStatement, 2) // ���-�� ����, ������� ����� ��������� � ����������
			);
			nodeData->Signature = UnicodeString((char*)sqlite3_column_text(pStatement, 3));
		}

		VST->EndUpdate();
	} else {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� SELECT ��� ������� scans: " + UnicodeString(errmsg));
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}
