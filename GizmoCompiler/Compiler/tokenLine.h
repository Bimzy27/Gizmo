#pragma once
#include <vector>

#include "lexer.h"

using namespace std;

class tokenLine
{
public:
    int getDepth();
    bool hasNextToken();
    int getTokenCount();
    token* getToken(int index);
    token* nextToken();
    void eraseNextToken();
    tokenLine(vector<token> _tokens, int _depth) : tokens(_tokens), depth(_depth) {}
private:
    vector<token> tokens;
    int depth;
};
