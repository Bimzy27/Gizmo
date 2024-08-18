#include "lexer.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isNumber(const string &str)
{
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isText(const string &str)
{
    return str.back() == '"' && str.front() == '"';
}

bool isBool(const string &str)
{
    return str == "true" || str == "false";
}

bool isValidIdentifier(const string &str)
{
    return isalpha(str[0]) && all_of(str.begin(), str.end(), [](char c) { return isalpha(c) || isdigit(c); });
}

bool isArithmaticOperator(const string &str)
{
    return
        str == "+" ||
        str == "-";
}

bool isRelationalOperator(const string &str)
{
    return
        str == ">" ||
        str == "<" ||
        str == ">=" ||
        str == "<=" ||
        str == "!=" ||
        str == "==";
}

bool isLogicOperator(const string &str)
{
    return
        str == "or" ||
        str == "and";
}

bool isVariable(const string &str)
{
    return
        str == "number" ||
        str == "text" ||
        str == "bool";
}

bool isCall(const string &str)
{
    return
        str == "write" ||
        str == "writeLine";
}

bool isConditionalStatement(const string &str)
{
    return
        str == "if" ||
        str == "else if" ||
        str == "else";
}

void logWord(string &word)
{
    if (word == "\n")
    {
        cout << "Word: " << "newLine" << endl;
    }
    else
    {
        cout << "Word: " << word << endl;
    }
}

vector<token> lexer::tokenize(const string &sourceCode)
{
    vector<token> tokens;
    vector<string> src = splitString(sourceCode);

    bool identifierNext = false;
    while (!src.empty())
    {
        string word = src.front();
        logWord(word);

        if (identifierNext)
        {
            if (isValidIdentifier(word))
            {
                tokens.push_back(token(word, TokenType::Identifier));
                variables.insert(word);
            }
            identifierNext = false;
            src.erase(src.begin());
            continue;
        }

        if (word == "\n")
        {
            tokens.push_back(token(word, TokenType::NewLine));
        }
        else if (isNumber(word))
        {
            tokens.push_back(token(word, TokenType::Number));
        }
        else if (isText(word))
        {
            tokens.push_back(token(word, TokenType::Text));
        }
        else if (isBool(word))
        {
            tokens.push_back(token(word, TokenType::Bool));
        }
        else if (isArithmaticOperator(word))
        {
            tokens.push_back(token(word, TokenType::ArithmaticOperator));
        }
        else if (isRelationalOperator(word))
        {
            tokens.push_back(token(word, TokenType::RelationalOperator));
        }
        else if (isLogicOperator(word))
        {
            tokens.push_back(token(word, TokenType::LogicOperator));
        }
        else if (isVariable(word))
        {
            tokens.push_back(token(word, TokenType::Variable));
            identifierNext = true;
        }
        else if (word == "=")
        {
            tokens.push_back(token(word, TokenType::Equals));
        }
        else if (word == ":")
        {
            tokens.push_back(token(word, TokenType::Colon));
        }
        else if (word == "(")
        {
            tokens.push_back(token(word, TokenType::OpenParen));
        }
        else if (word == ")")
        {
            tokens.push_back(token(word, TokenType::CloseParen));
        }
        else if (isCall(word))
        {
            tokens.push_back(token(word, TokenType::Call));
        }
        else if (isConditionalStatement(word))
        {
            tokens.push_back(token(word, TokenType::ConditionalStatement));
        }
        else if (variables.contains(word))
        {
            tokens.push_back(token(word, TokenType::Identifier));
        }

        src.erase(src.begin());
    }

    return tokens;
}

vector<string> lexer::splitString(const string &sourceCode)
{
    vector<string> words;
    string word;

    for (char ch : sourceCode)
    {
        if (ch == '"')
        {
            if (accumulatingText)
            {
                word += ch;
                words.push_back(word);
                word.clear();
                accumulatingText = false;
            }
            else
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word.clear();
                }
                word += ch;
                accumulatingText = true;
            }
            continue;
        }

        if (word == "else" && ch == ' ')
        {
            word += ch;
            continue;
        }

        if (ch == '\t')
        {
            cout << "TAB FOUND!" << endl;
            //TODO implement indents into lexer to support conditional statements
        }

        if ((ch == ' ' || ch == '\n' || ch == ':' || ch == '(' || ch == ')') && !accumulatingText)
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }

            if (ch == '\n')
            {
                words.push_back("\n");
            }
            else if (ch == '(')
            {
                words.push_back("(");
            }
            else if (ch == ':')
            {
                words.push_back(":");
            }
            else if (ch == ')')
            {
                words.push_back(")");
            }
        }
        else
        {
            word += ch;
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}