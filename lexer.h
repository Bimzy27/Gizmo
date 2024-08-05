#pragma once

#include <string>
#include <vector>

using namespace std;

enum TokenType
{
    Number,
    Identifier,
    Equals,
    BinaryOperator,
    Variable
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