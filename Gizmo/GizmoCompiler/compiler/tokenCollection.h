#pragma once
#include <vector>

#include "tokenLine.h"

using namespace std;

class tokenCollection
{
public:
    bool hasNextLine();
    int getLineCount();
    tokenLine* getTokenLine(int index);
    tokenLine* nextLine();
    void eraseNextLine();
    tokenCollection(vector<token>* tokens);
private:
    vector<tokenLine> tokenLines;
};
