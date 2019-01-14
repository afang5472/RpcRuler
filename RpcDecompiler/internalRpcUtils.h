#ifndef _RPC_UTILS_
#define _RPC_UTILS_

#include <string>
#include <locale>
#include <vector>
#include <tchar.h>
#include "RpcDecompiler.h"


//---------------------------------------------------------------------------
BOOL __fastcall isStandardCharacter(_In_ const WCHAR wc);


//--------------------------------------------------------------------------
std::string narrow(
	_In_	const std::wstring& ws);

//--------------------------------------------------------------------------
std::string get_base_filename(_In_ const TCHAR *filepath);

//--------------------------------------------------------------------------
BOOL get_module_filename(_In_ HANDLE hProcess, _In_ VOID* pAddress, _In_ WCHAR *ModuleName);

//--------------------------------------------------------------------------
BOOL is_file_exist(_In_ const TCHAR *filepath);


//-------------------------------------------------------------------------
VOID displayPtrLevel(
	_In_	const UINT uPtrLevel, 
	_Inout_	std::ostringstream& oss);

//--------------------------------------------------------------------------
VOID displayErrorMessage(
	_Inout_ std::ostringstream& oss, 
	_In_	PCHAR message);

#endif