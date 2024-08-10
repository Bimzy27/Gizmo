#pragma once

#include <set>
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
    Call,
    OpenParen,
    CloseParen,
    Indent,
};

inline const char* TokenTypeStr[] = {
    "Number",
    "Identifier",
    "Equals",
    "Operator",
    "Variable",
    "NewLine",
    "Call",
    "OpenParen",
    "CloseParen",
    "Indent",
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
private:
    set<string> variables;
};