#pragma once
#include "parser.h"

using namespace std;

class codeGenerator {
public:
    string generate(programNode* root);
private:
    string visitProgram(const programNode& node);
};
