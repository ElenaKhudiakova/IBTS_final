//---------------------------------------------------------------------------
#ifndef AbstractFileSystemH
#define AbstractFileSystemH
#include <vcl.h>
//---------------------------------------------------------------------------

class IteratorFS {
	protected:
		class AbstractFileSystem* FileSystem;
		DWORD currentPosition;   // DWORD - 32-?????? ??????????? ?????  // currentPosition - ??????? ???????
		char* clusterBuffer;     // ????????????? (??????????) ??? ??????    // ??????, ? ??????? ???????? ??????
		bool done;               // ?????????? ??? ?????? bool, ??????/????    // ???? ? ?????????? ??????
	public:
		IteratorFS(AbstractFileSystem* FileSystem);

		virtual void First();   // ??????????? ?????, ??? ??? ???????????? ??????????? ???????
		virtual void Next();
		virtual bool IsDone();
		virtual char* GetCurrent();
		virtual DWORD GetCurrentPosition();
		virtual AbstractFileSystem* GetFileSystem();

		~IteratorFS();   //  ??????????
};


// Public ? ?????? ?????? ???? ?????? ???????, ??? ????? ??????????? ??????? ??????.
// Protected ? ?????? ?????? ???????, ??????????? ?? ???????. ?? ????, ??????????? ?????? ???????? ????????? ??????
// ? ????? ????????? ??? ??????. ??? ?????? ?????? ?????? ??????? ?? ?????.
// Private ? ?????? ?????? ?????? ?????? (?.?. ????????-?????? ??????? ??????) ? ??????? (friend) ??????? ?????? -
// ??? ????????, ??? ? ???????. ?????? ??????????? ?????? ?? ???????? ??????? ? ???? ?????? ??????.
// ? ??? ?????? ?????? ?????? ??????? ?? ?????.

// ??????????? ?????
class AbstractFileSystem {
	private:
		HANDLE FileHandle;
	protected:    // ????/?????????? ???????? ?? ??????????? (?????????, ????? ???????? ?????????? ????????)
		UINT64 fileSystemSize; // UINT64 = unsigned __int64
		DWORD clusterCount;
		DWORD clusterSize;    // 	DWORD = unsigned long

		// ???????????
		// protected, ?????? ??? ?? ?? ?????? ????? ?????? ???????????
		AbstractFileSystem(HANDLE FileHandle);

	public:   //   public ??? ?????????? ????????? ?? ?????? ?????
		// ?????? ???????? ??????? (? ??????)
		UINT64 GetFileSystemSize();
		// ?????????? ????????? ? ???????? ???????
		DWORD GetClusterCount();
		// ?????? ???????? ???????? ??????? (? ??????)
		DWORD GetClusterSize();

		// ????? ???????? ????????? (?????? ?????)
		virtual IteratorFS* GetIterator() = 0; // 0, ?????? ??? ??? ??????? ?????????? (0 - pure-specifier, ??????)
		// IteratorFS* (????????? ?? ??????), ? ?? IteratorFS, ????? ?? ????????? ?????????? ??????????? AbstractFileSystem()

		// ??????????? ????? ?????? ????????
		virtual bool ReadCluster(char* dataBuffer, DWORD clusterNumber); // ??? 0, ??? ??? ??????????? ? AbstractFileSystem.cpp

		// ??????????
		~AbstractFileSystem();
};

#endif
