#include <stdio.h>
//#include <stdlib.h>
#include <windows.h>
#include <shlwapi.h>

int main(int argc, char *argv[])
{
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind;
  DWORD nBufferLength;
  LPTSTR lpBuffer;
  TCHAR tchBuffer[MAX_PATH];
  nBufferLength = MAX_PATH;
  lpBuffer = tchBuffer;
  GetCurrentDirectory(nBufferLength, lpBuffer);
  lstrcat(lpBuffer, "\\*.*");
  printf ("Target dir is %s.\n", lpBuffer);
  tchBuffer[MAX_PATH - 1] = '\0';

  hFind = FindFirstFile(lpBuffer, &FindFileData);
  if (hFind == INVALID_HANDLE_VALUE)
  {
            printf ("INVALID_HANDLE_VALUE\n");
  }

  BOOL Done = FALSE;
  while (!Done)
  {
        if (FindFileData.dwFileAttributes &= FILE_ATTRIBUTE_DIRECTORY)
        {
                printf ("< %s >\n", FindFileData.cFileName);
        }
        else
        {
            TCHAR tchNewName[MAX_PATH];
            lstrcpy(tchNewName, FindFileData.cFileName);
            lstrcat(tchNewName, ".hidden");
            printf ("Renaming %s\n", FindFileData.cFileName);
            //MoveFile(FindFileData.cFileName, lpNewName);
            printf ("%s\n", PathFindExtensionA(tchNewName));
        }
        FindNextFile(hFind, &FindFileData);
        Done = GetLastError() == ERROR_NO_MORE_FILES;
  }
  FindClose(hFind);
}

