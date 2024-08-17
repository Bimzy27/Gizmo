#pragma once

#include <set>
#include <string>
#include <vector>

using namespace std;

enum TokenType
{
    Number,
    Text,
    Bool,
    Identifier,
    Equals,
    ArithmaticOperator,
    RelationalOperator,
    LogicOperator,
    Variable,
    NewLine,
    Call,
    OpenParen,
    CloseParen,
    Indent,
};

inline const char* TokenTypeStr[] = {
    "Number",
    "Text",
    "Bool",
    "Identifier",
    "Equals",
    "ArithmaticOperator",
    "RelationalOperator",
    "LogicOperator",
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
    vector<string> splitString(const string &sourceCode);
    set<string> variables;
    bool accumulatingText = false;
};