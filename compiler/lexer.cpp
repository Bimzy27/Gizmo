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

bool isValidIdentifier(const string &str)
{
    return isalpha(str[0]) && all_of(str.begin(), str.end(), [](char c) { return isalpha(c) || isdigit(c); });
}

bool isOperator(const string &str)
{
    return
        str == "+" ||
        str == "-";
}

bool isVariable(const string &str)
{
    return
        str == "number" ||
        str == "text";
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

        if (variables.contains(word))
        {
            tokens.push_back(token(word, TokenType::Identifier));
            src.erase(src.begin());
            continue;
        }

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
        else if (isOperator(word))
        {
            tokens.push_back(token(word, TokenType::Operator));
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
        else if (word == "(")
        {
            tokens.push_back(token(word, TokenType::OpenParen));
        }
        else if (word == ")")
        {
            tokens.push_back(token(word, TokenType::CloseParen));
        }
        else if (word == "print")
        {
            tokens.push_back(token(word, TokenType::Call));
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

        if ((ch == ' ' || ch == '\n' || ch == '(' || ch == ')') && !accumulatingText)
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