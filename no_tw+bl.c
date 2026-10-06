#include <windows.h>
#include <stdio.h>

HWND hwnd_tw = NULL;    //TurboWarp
HWND hwnd_bl = NULL;    //Bilup

BOOL CALLBACK EnumAllWindowsProc(HWND hwnd,LPARAM lparam)
{
    wchar_t title[100] = {0};
    GetWindowTextW(hwnd,title,100);

    if (wcsstr(title,L"TurboWarp") != NULL)
    {
        hwnd_tw = hwnd;
    }
    if (wcsstr(title,L"Bilup") != NULL)
    {
        hwnd_bl = hwnd;
    }

    return TRUE;
}

int main()
{
    char input[100] = {0};
    Sleep(100);

    printf("Do you need to hide the console? (Default:\"No\")\n");
    printf("(yes/no):");

    scanf("%s",&input);
    if (strcmpi(input,"yes") == 0)
    {
        ShowWindow(GetConsoleWindow(),SW_HIDE);
    }
    else
    {
        printf("Let's go!\n");
    }

    while (1)
    {
        WINBOOL window = EnumWindows(EnumAllWindowsProc,0);
        if (window == TRUE)
        {
            if (hwnd_tw != NULL)
            {
                SendMessageW(hwnd_tw,WM_CLOSE,0,0);
                if (GetLastError() == 0)
                {
                    printf("Goodbye TurboWarp!\n");
                    Sleep(100);
                    hwnd_tw = NULL;
                }
                else
                {
                    printf("what...admin!?\n");
                    Sleep(800);
                }
            }

            if (hwnd_bl != NULL)
            {
                SendMessageW(hwnd_bl,WM_CLOSE,0,0);
                if (GetLastError() == 0)
                {
                    printf("Goodbye Bilup!\n");
                    Sleep(100);
                    hwnd_bl = NULL;
                }
                else
                {
                    printf("what...admin!?\n");
                    Sleep(800);
                }
            }
            
        }

        Sleep(20);
    }

    return 0;
}