//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "cdiroutl"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(ScansTableStruct);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScanToggleSwitchClick(TObject *Sender)
{
	if (ScanToggleSwitch->State == tssOn) {
		ScanToggleSwitch->ThumbColor = clGreen;
		//  1 �������: ���� � ������ ������ ��������� On, �� ��� ������ ����, ������� �������� ��� ��
		// ���� ������ EmptyCluster (�� ���� �� ������ ��������) ��������, �� �������� ������������� � ���������
		// �� ���� � NoEmptyClusterDecorator (�������)

		// 2 �������: ���� ����� ����������� ����� (SearchSignToggleSwitch �������),
		//�� ���������� ��������� � signSearch (true/false)


		// ������ ������
		IteratorFS* Iterator = FileSystem->GetIterator();

		// ���������� �� ������ ��������?
		if (EmptyClusterToggleSwitch->State == tssOn) {
			Iterator = new NoEmptyClusterDecorator(Iterator);  // ������ ���������� ������ ��������
		}

		// ����� �� ����������� �����?
		bool signSearch = SearchSignToggleSwitch->State == tssOn;

		// ������ ������ ������
		// false - �������� �� ��, ��� �� ����������� �����, ��� ������ ��������
		// TForm1 (this) - ��������� �� ����� ����  , �������� � ����� ����� ����
		ReadThreadPtr = new ReadThread(false, Iterator, this, signSearch);
	} else {
		ScanToggleSwitch->ThumbColor = clMoneyGreen;

		// ��������� ������
		ReadThreadPtr->Terminate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectVolumeButtonClick(TObject *Sender)
{ // SelectDirectory ������� ���������� ����, ����� ��������� ������������ ������� ����������
	UnicodeString volumeName = L"";
	if (!SelectDirectory("�������� ����", "", volumeName)) {
		return;
	}

	// ��������� ����
	// handle - ��� ��������� �� ���������, ����������� �������� ������-�� ����������� �������, ��������,
	// ������-�� ����, ��������, �����. ������������ ��� ��������� ������� ����� ������� ��� ��������� �������� � ��� ���������.
	// HANDLE - ����������, �.�. �����, � ������� �������� ����� ���������������� ������. � ������� ������������ ����� ���������
	// �� ����, ������� ����, ����������� ������� � �.�.

// ����� �������� �������� � ��������: � ��� ������� ����� ��������,
//� HANDLE - ��� ������, ������� ��������� �� ���������� ������.

	HANDLE FileHandle = CreateDeviceHandle(volumeName);

	// ���������� �������� ������� �� �������� OEM (������� ��������)
	// FindFileSystemType ����� �� ������
	// FSType ������������ ����� �������� ������
	FSType Type = FindFileSystemType(FileHandle);

	if (Type == NULL) {
		ShowMessage(L"�������� ������� �� ��������������");
		return;
	}

	VolumeName->Caption = volumeName;
	// ����� ������������ ����������� switch-case. ��� ������� ������ ������� if-else �����������, ������� ����������
	// ���������� � ����������� ������������ ����������

	// ������� �������� �� �� �����
	switch (Type) {
	case FSType::NTFS_FS:
		FSLabel->Caption = "NTFS";
		break;
	case FSType::exFAT_FS:
		FSLabel->Caption = "exFAT";
		break;
	}

	// ������ �������� ������� � ������� ���������� ������
	FileSystem = CreateFileSystem(Type, FileHandle);

	// ����� ���������� �� ��
	FSSizeLabel->Caption = FileSystem->GetFileSystemSize()/1024;  // ������ � ��
	ClusterCountLabel->Caption = FileSystem->GetClusterCount();   // ���-�� ���������
	ClusterSizeLabel->Caption = FileSystem->GetClusterSize();     // ������ ��������

	ProgressBar1->Max = FileSystem->GetClusterCount();            // ���� ���-�� ProgressBar1 - ��� ���� ���-�� ��������� � �������

	// ���������� ������ ������������
	if (DBPath->Caption != L"") {
		ScanToggleSwitch->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	// ������� ��, ���� ��� ��� ���� �������
	if (Database != NULL) {
		sqlite3_close(Database);
	}

	// ������ ������������ ������� ���� � �� (� ���� ������ ���������� � "���������" ������ OpenTextFileDialog1)
	OpenTextFileDialog1->Execute();

	// ��������� ��, ���� ���-�� ����� �� ��� - ��������� ������
	int openResult = sqlite3_open16(OpenTextFileDialog1->FileName.w_str(), &Database);
	if (openResult != 0) {
		ShowMessage(L"�� ������� ������� ���� ������, openResult=" + openResult);
		return;
	}

	// ��������� ���� � �� � ������� �� � DBPath ��� ����������� � ����
	DBPath->Caption = OpenTextFileDialog1->FileName;

	// ���������� ������ ������������. ������������ ������ �����, �������� ���� � �� � ����� ����� ����.
	// VolumeName - ����� ����.
	if (VolumeName->Caption != L"") {
		ScanToggleSwitch->Enabled = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SigCheckListBoxClickCheck(TObject *Sender)
{   // ������ ����� ����������� ������ ���, ����� �� �������� ��������� (������� �� �������)
	// ������� ���������� �������
	SelectedSignatures.clear();

	// ���������� ������ � ���������� �����������
	for (int i = 0; i < SigCheckListBox->Count; i++) {
		// ���� ������� "�����", �� ������� ��� � ������ CheckedSignatures
		if (SigCheckListBox->Checked[i]) {
			// ��������� � ����� ������ �������� ���������
			// ������� push_back () � ��� ���� �� �������� �������� ����� ������� � ����� �������,
			// ������� ����������� ������ ������� �� 1.
			// ��� ������� �������, ����� ��������� �������� ���� ������� � �������.
			SelectedSignatures.push_back(
					SigCheckListBox->Items->Strings[i]
			);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	if (Node == NULL) return;
	ScansTableStruct* nodeData = (ScansTableStruct*) VirtualStringTree1->GetNodeData(Node);
	// ���� ��������� � typedef struct � main.h
	switch (Column)
	{
		case 0:
		{
			CellText = nodeData->Id;
			break;
		}
		case 1:
		{
			CellText = nodeData->ClusterNumber;
			break;
		}
		case 2:
		{
			CellText = nodeData->ClusterContent;
			break;
		}
		case 3:
		{
			CellText = nodeData->Signature;
			break;
		}
	}
}
//---------------------------------------------------------------------------

// ������ ������ ���� ��� �������
void __fastcall TForm1::EmptyClusterToggleSwitchClick(TObject *Sender)
{
	if (EmptyClusterToggleSwitch->State == tssOn) {
		EmptyClusterToggleSwitch->ThumbColor = clGreen;

	} else {
		EmptyClusterToggleSwitch->ThumbColor = clMoneyGreen;
	}

}
//---------------------------------------------------------------------------

// ������ ���� ��� �������� ��������/��������� CheckListBox
void __fastcall TForm1::SearchSignToggleSwitchClick(TObject *Sender)
{
	if (SearchSignToggleSwitch->State == tssOn) {
		SearchSignToggleSwitch->ThumbColor = clGreen;
		SigCheckListBox->Enabled = true;

	} else {
		SearchSignToggleSwitch->ThumbColor = clMoneyGreen;
		SigCheckListBox->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteAllButtonClick(TObject *Sender)
{
	// ������� ������ �� �������
	// ��� 1 (���������� �������)
	const char *errmsg;  // ���������� ������
	sqlite3_stmt *pStatement;    // ������ ������ � �� (����� � ���� ������)

	// ��������� �������
	// DELETE FROM scans ��� �������, ��� ��� ��������� ������� ���
	wchar_t sql[] = L"DELETE FROM scans;";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� DELETE ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return;
	}

	// ��� 2 (���������� �������)
	result = sqlite3_step(pStatement);
	// ��������� ���������
	if (result != SQLITE_DONE) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� DELETE ��� ������� scans: " + UnicodeString(errmsg));
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);

	// ������� ������� � �����
	VirtualStringTree1->Clear();

	// ��������� ������ �������� �������, ��� ��� ��� �� �������
	DeleteAllButton->Enabled = false;
	DeleteButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	// �������� ���������� ���� (�� ������)
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	if (selectedNode == NULL) return;

	// ����������� ��������� �� ����
	ScansTableStruct* nodeData = (ScansTableStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	// ������� ������ �� �������
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� �������
	wchar_t sql[] = L"DELETE FROM scans WHERE id = ?;";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� DELETE ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return;
	}

	// ����������� �������� Id ������ "?"
	// 1 �����, ��� ��� ���� "?"
	result = sqlite3_bind_int64(pStatement, 1, nodeData->Id);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� DELETE ��� ������� scans: " + UnicodeString(errmsg));
		// ��� 3 (���������� ��������� �������)
		sqlite3_finalize(pStatement);
		return;
	}

	// ��� 2 (���������� �������) (������)
	result = sqlite3_step(pStatement);
	// ��������� ���������
	if (result != SQLITE_DONE) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"������ ��� ���������� DELETE ��� ������� scans: " + UnicodeString(errmsg));
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);

	// ��������� ����������� �� �����
	VirtualStringTree1->BeginUpdate();
	VirtualStringTree1->DeleteNode(selectedNode);
	VirtualStringTree1->EndUpdate();
}
//---------------------------------------------------------------------------














