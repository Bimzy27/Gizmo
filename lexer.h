#pragma once

#include <string>
#include <vector>

using namespace std;

enum TokenType
{
    Number,
    Identifier,
    Equals,
    Operator,
    Variable,
    NewLine,
};

inline const char* TokenTypeStr[] = {
    "Number",
    "Identifier",
    "Equals",
    "Operator",
    "Variable",
    "NewLine",
};

struct token
{
    string value;
    TokenType type;
};

class lexer
{
public:
    vector<token> tokenize(const string &sourceCode);
};