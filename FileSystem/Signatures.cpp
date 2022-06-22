//---------------------------------------------------------------------------

#pragma hdrstop

#include "Signatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ClusterSignature FindSignature(char* dataBuffer, std::vector<UnicodeString> SelectedSignatures) {

	for(int i = 0; i < SelectedSignatures.size(); i++) {
		UnicodeString selected = SelectedSignatures[i];
		// ������� wcscmp () ������������ ��� ��������� ���� ���������������� �����. ���� ��� ����� - ������������ ����.
		// ��� ���� ���� �� ����������� ������ ����� ������� (false), �� ������ ����� ������� ��� �� �����������.
		if (wcscmp(selected.c_str(), L"PNG") == 0 && Contains(dataBuffer, PNG_SIG, 0, 8)) {
			return ClusterSignature::PNG;
		}

		if (wcscmp(selected.c_str(), L"JPEG") == 0 && Contains(dataBuffer, JPEG_SIG, 0, 3)) {
			return ClusterSignature::JPEG;
		}

		if (wcscmp(selected.c_str(), L"GIF") == 0 && Contains(dataBuffer, GIF_SIG, 0, 6)) {
			return ClusterSignature::GIF;
		}

		if (wcscmp(selected.c_str(), L"PDF") == 0 && Contains(dataBuffer, PDF_SIG, 0, 7)) {
			return ClusterSignature::PDF;
		}

		if (wcscmp(selected.c_str(), L"FILE") == 0 && Contains(dataBuffer, FILE_SIG, 0, 4)) {
			return ClusterSignature::FILEE;
		}
	}

	return NULL;
}

// ���������� bool ��� ���������� ��� ������. ���������� ����� ���� ����� ���������
// ����� ��� �������� � true (������=1) � false (����=0).
bool Contains(char* dataBuffer, const char* sign, int start, int len) {
	for (int i = start; i < len-start; i++) {
		if (dataBuffer[i] != sign[i]) {
			return false;
		}
	}

	return true;
}

char* GetSignatureName(ClusterSignature clusterSignature) {
	switch (clusterSignature) {
	case ClusterSignature::PNG:  // ���������� ���������� ����������, �� ���� ���������� �������� ���������� (::)
		return "PNG";
		break;
	case ClusterSignature::JPEG:
		return "JPEG";
		break;
	case ClusterSignature::GIF:
		return "GIF";
		break;
	case ClusterSignature::PDF:
		return "PDF";
		break;
	case ClusterSignature::FILEE:
		return "FILE";
		break;
	default:
		return NULL;
	}
}
 // ����������� switch-case � ��� ������� ������ ������� if-else �����������,
 // ������� ���������� ���������� � ����������� ������������ ����������.
