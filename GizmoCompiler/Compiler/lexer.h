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
    ConditionalStatement,
    Colon,
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
    "ConditionalStatement",
    "Colon",
};

struct token
{
    string value;
    TokenType type;
    int depth;
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