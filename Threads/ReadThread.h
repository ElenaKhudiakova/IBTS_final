//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vcl.h>
#include "ProcessThread.h"
#include "Main.h"
#include "ustring.h"
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class IteratorFS* Iterator;
	class ProcessThread* ProcessThreadPtr;   // ���� ������ �� ������ �����-�������
	class TForm1* Form1;
	TEvent* MyEvent;  // ���� ������ �� MyEvent ��� ����, ����� "��������" � ProcessThread
protected:
	void __fastcall Execute();
public:
	__fastcall ReadThread(bool CreateSuspended, IteratorFS* Iterator, TForm1* Form1, bool useSignatureSearch);
	void __fastcall OnStart(); // ����� ������ ������� �����
	void __fastcall OnProgress();  // ���������� ��������� �� ����� ProgressBar1
	void __fastcall OnStop();   // ����� �����������, ��������� ���������� �� �����
};
//---------------------------------------------------------------------------
#endif
