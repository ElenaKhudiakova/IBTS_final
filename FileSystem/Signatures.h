//---------------------------------------------------------------------------

#ifndef SignaturesH
#define SignaturesH
#include <vector>
#include <vcl.h>
//---------------------------------------------------------------------------

// ��� ��������� � �������� ���������� � 0 ����� (�� ���� �� ������)
// ��������� ����� �����  https://ru.stackoverflow.com/questions/1128506/����������-�����������-���-�������-�-�����-������

const char PNG_SIG[8] = "\x89PNG\x0D\x0A\x1A\x0A";
const char JPEG_SIG[3] = "\xFF\xD8\xFF";
const char GIF_SIG[6] = "GIF89a";
const char PDF_SIG[7] = {'%', 'P', 'D', 'F', '\x2D', '1', '\x2E'}; // ������, ������ ��� ��� ���������� �� �������������� ������
const char FILE_SIG[4] = "FILE";

enum ClusterSignature {
	PNG=1,
	JPEG=2,
	GIF=3,
	PDF=4,
	FILEE=5   // ����� ���������� ������� �, � ����� � ���, ��� � �����������
	// ���� �����������, ��� (������) ��� ���������� �������� FILE. ��� ���� �� ��������� ��� �� ������, ��� �������� "FILE".
};

ClusterSignature FindSignature(char* dataBuffer, std::vector<UnicodeString> selected);
bool Contains(char* dataBuffer, const char* sign, int start, int len);
char* GetSignatureName(ClusterSignature clusterSignature);

#endif