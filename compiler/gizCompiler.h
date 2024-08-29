#pragma once
#include <string>

using namespace std;

class gizCompiler
{
public:
    void compile(string projectFile);
};

#define LIB_API(RetType) extern "C" __declspec(dllexport) RetType

LIB_API(void) Compile(string gizmoProjectPath);