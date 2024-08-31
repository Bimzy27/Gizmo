#include <string>
#include <windows.h>

#include "compiler/gizCompiler.h"

#define EXPORTED_METHOD extern "C" __declspec(dllexport)

EXPORTED_METHOD
void Compile(const char* projectFilePath)
{
    gizCompiler comp;
    comp.compile(projectFilePath);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
	
    return TRUE;
}

