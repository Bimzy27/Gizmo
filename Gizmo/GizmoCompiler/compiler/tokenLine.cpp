#include "tokenLine.h"

#include <cassert>
#include <iostream>

using namespace std;

int tokenLine::getDepth()
{
    assert(depth >= 0);
    
    return depth;
}

bool tokenLine::hasNextToken()
{
    return tokens.empty() == false;
}

int tokenLine::getTokenCount()
{
    return tokens.size();
}

token* tokenLine::getToken(int index)
{
    assert(tokens.size() > index && "Index out of range of token count.");

    return &tokens[index];
}

token* tokenLine::nextToken()
{
    assert(hasNextToken() && "There is no next token to return.");
    
    return &tokens.front();
}

void tokenLine::eraseNextToken()
{
    assert(hasNextToken() && "There is no next token to erase.");

    tokens.erase(tokens.begin());
}
