//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.FileCtrl.hpp>
#include "cdiroutl.h"
#include <Vcl.Grids.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.CategoryButtons.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <vector>
#include "sqlite3.h"
#include "FactoryFileSystem.h"
#include "Utils.h"
#include "ReadThread.h"
#include "NoEmptyClusterDecorator.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TToggleSwitch *ScanToggleSwitch;
	TLabel *Label1;
	TLabel *Label2;
	TToggleSwitch *EmptyClusterToggleSwitch;
	TProgressBar *ProgressBar1;
	TToggleSwitch *SearchSignToggleSwitch;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *FSSizeLabel;
	TLabel *ClusterCountLabel;
	TLabel *ClusterSizeLabel;
	TButton *DeleteButton;
	TButton *DeleteAllButton;
	TButton *SelectVolumeButton;
	TLabel *DBPath;
	TLabel *VolumeName;
	TCheckListBox *SigCheckListBox;
	TLabel *Label12;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TButton *Button3;
	TLabel *FSLabel;
	TLabel *ProgressLabel;
	TToggleSwitch *ToggleSwitch1;
	void __fastcall ScanToggleSwitchClick(TObject *Sender);
	void __fastcall SelectVolumeButtonClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall SigCheckListBoxClickCheck(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall EmptyClusterToggleSwitchClick(TObject *Sender);
	void __fastcall SearchSignToggleSwitchClick(TObject *Sender);
	void __fastcall DeleteAllButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	// ?????? ????????? ???????? ?????? (???? ?????????? ??? ?????????, ??????? ???? ???????? ? CheckListBox)
	std::vector<UnicodeString> SelectedSignatures;  // ??????, ????????? ?? ???-?? ????????? ????????, ???? UnicodeString
	// ?????? ?? ??
	sqlite3* Database;
	// ?????? ?? ???????? ???????
	class AbstractFileSystem* FileSystem;  // ???? NTFS, ???? exFAT
	class ReadThread* ReadThreadPtr;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

// ????????? ??????? ? ??
/*
CREATE TABLE "scans" (
	"id"	INTEGER NOT NULL UNIQUE,
	"cluster_number"	INTEGER,
	"cluster_content"	BLOB,
	"signature"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
)
*/
typedef struct {
	DWORD Id;
	DWORD ClusterNumber;
	UnicodeString ClusterContent;
	UnicodeString Signature;
} ScansTableStruct;

#endif
