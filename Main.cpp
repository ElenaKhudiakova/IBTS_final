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
		//  1 условие: если у данной кнопки состояние On, то она меняет цвет, создает итератор для ФС
		// Если кнопка EmptyCluster (то есть не пустые кластеры) включена, то итератор оборачивается в декоратор
		// то есть в NoEmptyClusterDecorator (обертка)

		// 2 условие: если нужен сигнатурный поиск (SearchSignToggleSwitch включен),
		//то записываем состояние в signSearch (true/false)


		// Запуск потока
		IteratorFS* Iterator = FileSystem->GetIterator();

		// Пропускаем ли пустые кластеры?
		if (EmptyClusterToggleSwitch->State == tssOn) {
			Iterator = new NoEmptyClusterDecorator(Iterator);  // внутрь декоратора кладем итератор
		}

		// Нужен ли сигнатурный поиск?
		bool signSearch = SearchSignToggleSwitch->State == tssOn;

		// Запуск потока чтения
		// false - отвечает за та, что он запускается сразу, как только создался
		// TForm1 (this) - ссылаемся на самих себя  , передаем в поток самих себя
		ReadThreadPtr = new ReadThread(false, Iterator, this, signSearch);
	} else {
		ScanToggleSwitch->ThumbColor = clMoneyGreen;

		// Остановка потока
		ReadThreadPtr->Terminate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectVolumeButtonClick(TObject *Sender)
{ // SelectDirectory выводит диалоговое окно, чтобы позволить пользователю выбрать директорию
	UnicodeString volumeName = L"";
	if (!SelectDirectory("Выберите диск", "", volumeName)) {
		return;
	}

	// Открываем диск
	// handle - это указатель на структуру, описывающую свойства какого-то конкретного объекта, например,
	// какого-то окна, процесса, файла. Используется для изменения свойств этого объекта или получения сведений о его свойствах.
	// HANDLE - дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс. С помощью дескприторов можно ссылаться
	// на окна, объекты ядра, графические объекты и т.п.

// Можно провести аналогию с массивом: у нас имеется набор ресурсов,
//а HANDLE - это индекс, который указывает на конкретный ресурс.

	HANDLE FileHandle = CreateDeviceHandle(volumeName);

	// Определяем файловую систему по названию OEM (кодовая страница)
	// FindFileSystemType взята из лекций
	// FSType перечисление типов файловых систем
	FSType Type = FindFileSystemType(FileHandle);

	if (Type == NULL) {
		ShowMessage(L"Файловая система не поддерживается");
		return;
	}

	VolumeName->Caption = volumeName;
	// Здесь используется конструкция switch-case. Это удобная замена длинной if-else конструкции, которая сравнивает
	// переменную с несколькими константными значениями

	// Выводим название ФС на форму
	switch (Type) {
	case FSType::NTFS_FS:
		FSLabel->Caption = "NTFS";
		break;
	case FSType::exFAT_FS:
		FSLabel->Caption = "exFAT";
		break;
	}

	// Создаём файловую систему с помощью фабричного метода
	FileSystem = CreateFileSystem(Type, FileHandle);

	// Вывод информации по ФС
	FSSizeLabel->Caption = FileSystem->GetFileSystemSize()/1024;  // размер в Мб
	ClusterCountLabel->Caption = FileSystem->GetClusterCount();   // кол-во кластеров
	ClusterSizeLabel->Caption = FileSystem->GetClusterSize();     // размер кластера

	ProgressBar1->Max = FileSystem->GetClusterCount();            // макс кол-во ProgressBar1 - это макс кол-во кластеров в системе

	// Активируем кнопку сканирования
	if (DBPath->Caption != L"") {
		ScanToggleSwitch->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	// Закрыть БД, если она уже была открыта
	if (Database != NULL) {
		sqlite3_close(Database);
	}

	// Просим пользователя выбрать файл с БД (в этот момент обращаемся к "фантомной" кнопке OpenTextFileDialog1)
	OpenTextFileDialog1->Execute();

	// Открываем БД, если что-то пошло не так - блокируем работу
	int openResult = sqlite3_open16(OpenTextFileDialog1->FileName.w_str(), &Database);
	if (openResult != 0) {
		ShowMessage(L"Не удалось открыть базу данных, openResult=" + openResult);
		return;
	}

	// Сохраняем путь к БД и выводим ее в DBPath для отображения в окне
	DBPath->Caption = OpenTextFileDialog1->FileName;

	// Активируем кнопку сканирования. Активируется только тогда, прописан путь к БД и стоит метка тома.
	// VolumeName - Метка тома.
	if (VolumeName->Caption != L"") {
		ScanToggleSwitch->Enabled = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SigCheckListBoxClickCheck(TObject *Sender)
{   // Данная форма обновляется каждый раз, когда мы выбираем сигнатуру (кликаем на галочку)
	// Удаляем содержимое вектора
	SelectedSignatures.clear();

	// Обновление списка с выбранными сигнатурами
	for (int i = 0; i < SigCheckListBox->Count; i++) {
		// Если элемент "нажат", то добавим его в вектор CheckedSignatures
		if (SigCheckListBox->Checked[i]) {
			// Вставляем в конец списка название сигнатуры
			// Функция push_back () — это один из способов вставить новый элемент в конец вектора,
			// который увеличивает размер вектора на 1.
			// Эта функция полезна, когда требуется добавить один элемент к вектору.
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
	// Поля прописаны в typedef struct в main.h
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

// Просто меняем цвет при нажатии
void __fastcall TForm1::EmptyClusterToggleSwitchClick(TObject *Sender)
{
	if (EmptyClusterToggleSwitch->State == tssOn) {
		EmptyClusterToggleSwitch->ThumbColor = clGreen;

	} else {
		EmptyClusterToggleSwitch->ThumbColor = clMoneyGreen;
	}

}
//---------------------------------------------------------------------------

// Меняем цвет при нажатиии включаем/выключаем CheckListBox
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
	// Удаляем записи из таблицы
	// Шаг 1 (подготовка запроса)
	const char *errmsg;  // Переменная ошибки
	sqlite3_stmt *pStatement;    // Запись ответа в БД (ответ в виде данных)

	// Формируем запросы
	// DELETE FROM scans без условия, так как требуется удалить ВСЕ
	wchar_t sql[] = L"DELETE FROM scans;";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"Ошибка при выполнении DELETE для таблицы scans: " + UnicodeString(errmsg));
		// Шаг 3 (завершение обработки запроса)
		sqlite3_finalize(pStatement);
		return;
	}

	// Шаг 2 (выполнение запроса)
	result = sqlite3_step(pStatement);
	// Проверяем результат
	if (result != SQLITE_DONE) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"Ошибка при выполнении DELETE для таблицы scans: " + UnicodeString(errmsg));
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);

	// Очищаем элемент в форме
	VirtualStringTree1->Clear();

	// Отключаем кнопки удаления записей, так как уже всё удалено
	DeleteAllButton->Enabled = false;
	DeleteButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	// Получаем выделенный узел (из лекции)
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	if (selectedNode == NULL) return;

	// Накладываем структуру на узел
	ScansTableStruct* nodeData = (ScansTableStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	// Удаляем запись из таблицы
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запросы
	wchar_t sql[] = L"DELETE FROM scans WHERE id = ?;";

	int result = sqlite3_prepare16_v2(Form1->Database, sql, -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"Ошибка при выполнении DELETE для таблицы scans: " + UnicodeString(errmsg));
		// Шаг 3 (завершение обработки запроса)
		sqlite3_finalize(pStatement);
		return;
	}

	// Подставляем значения Id вместо "?"
	// 1 место, так как один "?"
	result = sqlite3_bind_int64(pStatement, 1, nodeData->Id);
	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"Ошибка при выполнении DELETE для таблицы scans: " + UnicodeString(errmsg));
		// Шаг 3 (завершение обработки запроса)
		sqlite3_finalize(pStatement);
		return;
	}

	// Шаг 2 (выполнение запроса) (лекция)
	result = sqlite3_step(pStatement);
	// Проверяем результат
	if (result != SQLITE_DONE) {
		errmsg = sqlite3_errmsg(Form1->Database);
		ShowMessage(L"Ошибка при выполнении DELETE для таблицы scans: " + UnicodeString(errmsg));
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);

	// Обновляем отображение на форме
	VirtualStringTree1->BeginUpdate();
	VirtualStringTree1->DeleteNode(selectedNode);
	VirtualStringTree1->EndUpdate();
}
//---------------------------------------------------------------------------














