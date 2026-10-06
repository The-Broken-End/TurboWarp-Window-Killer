#include <windows.h>
#include <stdio.h>

BOOL is_exit_tww = FALSE;
HWND hwnd_tw = NULL;

BOOL CALLBACK EnumAllWindowsProc(HWND hwnd,LPARAM lparam)
{
    wchar_t title[100] = {0};
    GetWindowTextW(hwnd,title,100);

    if (wcsstr(title,L"TurboWarp") != NULL)
    {
        is_exit_tww = TRUE;
        hwnd_tw = hwnd;
        return FALSE;
    }

    is_exit_tww = FALSE;
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
        EnumWindows(EnumAllWindowsProc,0);
        if (is_exit_tww == TRUE)
        {
            SendMessageW(hwnd_tw,WM_CLOSE,0,0);
            if (GetLastError() == 0)
            {
                printf("Goodbye TurboWarp!\n");
                Sleep(100);
            }
            else
            {
                printf("what...admin!?\n");
                Sleep(800);
            }
        }
        Sleep(20);
    }

    return 0;
}