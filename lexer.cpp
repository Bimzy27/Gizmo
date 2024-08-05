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
        if (ch != ' ')
        {
            word += ch;
        }
        else if (!word.empty())
        {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

bool isNumber(const string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

vector<token> lexer::tokenize(const string &sourceCode)
{
    vector<token> tokens;
    vector<string> src = splitString(sourceCode);

    while (!src.empty())
    {
        if (isNumber(src.front()))
        {
            cout<<"The string contains number " << src.front() << "\n";
            tokens.push_back(token(src.front(), TokenType::Number));
            src.erase(src.begin());
        }
    }

    return tokens;
}