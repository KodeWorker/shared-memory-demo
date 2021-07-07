// https://blog.csdn.net/zcz_822/article/details/105858962
// https://docs.microsoft.com/zh-tw/windows/win32/memory/creating-named-shared-memory
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define BUF_SIZE 256

using namespace std;

int main()
{
    
    // write shared memory
    LPCTSTR pBuf;
    TCHAR szMsg[]=TEXT("Hi Word ?!");
    HANDLE hMapFile = CreateFileMapping(
                                        INVALID_HANDLE_VALUE,    // use paging file
                                        NULL,                    // default security
                                        PAGE_READWRITE,          // read/write access
                                        0,                       // maximum object size (high-order DWORD)
                                        BUF_SIZE,                // maximum object size (low-order DWORD)
                                        "global_share_memory");                 // name of mapping object
    if (hMapFile == NULL)
    {
        cout << "Could not create handler" << endl;
    }
    pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
                       FILE_MAP_ALL_ACCESS,  // read/write permission
                       0,
                       0,
                       BUF_SIZE);
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    UnmapViewOfFile(pBuf);

    // read shared memory	
    LPVOID pBuffer;
    HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, "global_share_memory");

    if (NULL == hMap)
	{
		cout << "No Shared Memory" << endl;
	}
	else
	{
		while (true)
		{
			Sleep(1000);
			pBuffer = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			cout << "Data string in shared memory: " << (char*)pBuffer << endl;
		}
	}
    
    system("pause");
    UnmapViewOfFile(pBuffer);
    CloseHandle(hMap);
}

