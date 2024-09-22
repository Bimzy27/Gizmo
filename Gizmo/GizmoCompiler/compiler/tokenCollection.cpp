#include "tokenCollection.h"

#include <cassert>

#include "lexer.h"

using namespace std;

bool tokenCollection::hasNextLine()
{
    return !tokenLines.empty();
}

int tokenCollection::getLineCount()
{
    return tokenLines.size();
}

tokenLine* tokenCollection::getTokenLine(int index)
{
    assert(tokenLines.size() > index && "Index out of range of tokenLine count.");

    return &tokenLines[index];
}

tokenLine* tokenCollection::nextLine()
{
    assert(hasNextLine() && "There is no next line to return.");
    
    return &tokenLines.front();
}

void tokenCollection::eraseNextLine()
{
    assert(hasNextLine() && "There is no next line to erase.");
    
    tokenLines.erase(tokenLines.begin());
}

tokenCollection::tokenCollection(vector<token>* tokens)
{
    assert(!tokens->empty() && "An empty token collection was passed into the constructor.");
    
    while (!tokens->empty())
    {
        int depth = 0;
        while (!tokens->empty() && tokens->front().type == TokenType::Indent)
        {
            depth += 1;
            tokens->erase(tokens->begin());
        }
        vector<token> line;
        while (!tokens->empty() && tokens->front().type != TokenType::NewLine)
        {
            tokens->front().depth = depth;
            line.push_back(tokens->front());
            tokens->erase(tokens->begin());
        }
        if (!tokens->empty())
        {
            tokens->erase(tokens->begin()); // Erase new line
        }
        tokenLine ln = tokenLine(line, depth);
        tokenLines.push_back(ln);
    }
}
