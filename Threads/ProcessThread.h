//---------------------------------------------------------------------------

#ifndef ProcessThreadH
#define ProcessThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vcl.h>
#include <cstring>
#include "Signatures.h"
#include "Main.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
class ProcessThread : public TThread
{
private:
	TEvent* MyEvent;
	DWORD bufferSize; // DWORD - 32-������ ����������� �����. �������: unsigned long int, UINT.
	class TForm1* Form1;

	char* copyBuffer; // ��� ������ � ������� ���������� �� �����������
	ClusterSignature clusterSignature;  // ����������� ��������� ��������
	bool useSignatureSearch; // ����� �� ������ ���������?

	// ������� �� ���������� �������� � ��
	bool addClusterToDB();
protected:
	void __fastcall Execute();
public:
	__fastcall ProcessThread(bool CreateSuspended, TEvent* MyEvent, DWORD bufferSize, TForm1* Form1, bool useSignatureSearch);
	void __fastcall addClustersToVST();  // �� ���������� ����� ���������� � VirtualStringTree

	char* receivedBuffer; // ��� ��
    DWORD clusterNumber;
};
//---------------------------------------------------------------------------
#endif