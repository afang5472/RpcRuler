#include "internalRpcUtils.h"
#include <psapi.h>
#include <strsafe.h>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "strsafe.lib")

#define MAX_DRIVE_INDEX 26

//--------------------------------------------------------------------------
BOOL __fastcall isStandardCharacter(_In_ const WCHAR wc)
{
	BOOL	bResult	= FALSE;

	if( ((wc >= L'a') && 
		(wc <= L'z'))

		||

		((wc >= L'A') &&
		(wc <= L'Z'))

		||

		((wc >= L'0') &&
		(wc <= L'9')) )
	{
		bResult = TRUE;
	}

	return (bResult);
}


//-------------------------------------------------------------------------
std::string narrow(
	_In_	const std::wstring& ws)
{
	//std::vector<char> buffer(ws.size());
	////std::locale loc("english");
	//std::locale loc;
	//std::use_facet< std::ctype<wchar_t> > (loc).narrow(ws.data(), ws.data() + ws.size(), '?', &buffer[0]);

	//return std::string(&buffer[0], buffer.size());

	return std::string(ws.begin(), ws.end());
}

//-------------------------------------------------------------------------
std::string get_base_filename(const TCHAR* filepath) {
	std::string strfilepath(filepath);
	size_t pos = strfilepath.rfind(_T("\\"));
	if (pos == std::string::npos)
		return strfilepath;
	if (pos == 0)
		return strfilepath;
	return strfilepath.substr(pos + 1, strfilepath.length());
}

//-------------------------------------------------------------------------
BOOL get_module_filename(HANDLE hProcess, VOID* pAddress, WCHAR *ModuleName)
{
	DWORD						DriveMask;
	WCHAR						DriveIdx;
	WCHAR						NativeLocation[RPC_MAX_LENGTH];
	WCHAR						DeviceName[RPC_MAX_LENGTH];
	WCHAR*						pPath;
	WCHAR						DosDevice[] = L"X:";
	BOOL						bResult = FALSE;


	//
	// Get the native mapped file name containing the specified address
	//
	if (!GetMappedFileNameW(hProcess, pAddress, NativeLocation, _countof(NativeLocation))) goto End;
	//
	// Get the corresponding Win32 path
	//
	DriveMask = GetLogicalDrives();
	for (DriveIdx = 0; DriveIdx < MAX_DRIVE_INDEX; DriveIdx++)
	{
		if (DriveMask & (1 << DriveIdx))
		{
			DosDevice[0] = L'A' + DriveIdx;
			if (QueryDosDeviceW(DosDevice, DeviceName, _countof(DeviceName)) != 0)
			{
				pPath = wcsstr(NativeLocation, DeviceName);
				if (pPath != NULL)
				{
					StringCbPrintfW(ModuleName, MAX_PATH * 2, L"%s%s", DosDevice, NativeLocation + wcslen(DeviceName));
					bResult = TRUE;
					break;
				}
			}
		}
	}
End:
	return bResult;
}

//--------------------------------------------------------------------------
BOOL is_file_exist(const TCHAR *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}




//-------------------------------------------------------------------------
VOID displayPtrLevel(
	_In_	const UINT uPtrLevel, 
	_Inout_	std::ostringstream& oss)
{
	for(UINT i=0; i<uPtrLevel; i++)
	{
		oss<<"*";
	}
}


//----------------------------------------------------------------------------
VOID displayErrorMessage(
	_Inout_ std::ostringstream& oss, 
	_In_	PCHAR message)
{
	oss<< "/* [ERROR] : "<< message << "*/";
}

