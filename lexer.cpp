#include "lexer.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> splitString(const string &sourceCode)
{
    vector<string> words;
    string word;

    for (char ch : sourceCode)
    {
        if (ch == ' ' || ch == '\n')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
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

bool isNumber(const string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
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
        str == "int";
}

vector<token> lexer::tokenize(const string &sourceCode)
{
    vector<token> tokens;
    vector<string> src = splitString(sourceCode);

    for (auto &s: src) {
        cout << "Src: " << s << endl;
    }

    bool identifierNext = false;
    while (!src.empty())
    {
        string word = src.front();

        if (identifierNext)
        {
            if (isalpha(word[0]))
            {
                tokens.push_back(token(word, TokenType::Identifier));
            }
            src.erase(src.begin());
            identifierNext = false;
            continue;
        }

        if (isNumber(word))
        {
            tokens.push_back(token(word, TokenType::Number));
            src.erase(src.begin());
        }
        else if (isOperator(word))
        {
            tokens.push_back(token(word, TokenType::Operator));
            src.erase(src.begin());
        }
        else if (isVariable(word))
        {
            tokens.push_back(token(word, TokenType::Variable));
            src.erase(src.begin());
            identifierNext = true;
        }
        else if (word == "=")
        {
            tokens.push_back(token(word, TokenType::Equals));
            src.erase(src.begin());
        }
    }

    return tokens;
}