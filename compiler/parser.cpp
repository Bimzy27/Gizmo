#include "parser.h"

#include <iostream>

using namespace std;

programNode* parser::parse(vector<token> tokens_)
{
    program = new programNode();
    tokens = tokens_;
    while (!tokens.empty())
    {
        if (tokens.front().type == TokenType::Variable)
        {
            parseVariable();
            continue;
        }

        if (tokens.front().type == TokenType::Identifier)
        {
            parseAssignment();
            continue;
        }

        if (tokens.front().type == TokenType::Call)
        {
            parseCall();
            continue;
        }

        if (tokens.front().type == TokenType::NewLine)
        {
            tokens.erase(tokens.begin());
            continue;
        }

        cout << "Unhandled Token <-> " << TokenTypeStr[tokens.front().type] << " <-> " << tokens.front().value << "\n";
        tokens.erase(tokens.begin());
    }
    return program;
}

node* getNextAssignment(vector<token> &tokens)
{
    node* n;
    if (tokens.front().type == TokenType::Number)
    {
        int num = stoi(tokens.front().value);
        n = new numberNode(num);
    }
    else if (tokens.front().type == TokenType::Identifier)
    {
        string str = tokens.front().value;
        n = new identifierNode(str);
    }
    tokens.erase(tokens.begin());
    return n;
}

void parser::parseVariable()
{
    string type = tokens.front().value;
    tokens.erase(tokens.begin());
    string name = tokens.front().value;
    variableNode* variable = new variableNode(type, name);
    program->executions.push_back(variable);
}

void parser::parseCall()
{
    string name = tokens.front().value;
    tokens.erase(tokens.begin());
    tokens.erase(tokens.begin()); // consume (
    string varName = tokens.front().value;
    tokens.erase(tokens.begin());
    tokens.erase(tokens.begin()); // consume )
    callNode* call = new callNode(name, varName);

    program->executions.push_back(call);
}

void parser::parseAssignment()
{
    string name = tokens.front().value;
    tokens.erase(tokens.begin());

    if (tokens.front().type == TokenType::NewLine)
    {
        tokens.insert(tokens.begin(), token("0", TokenType::Number));
    }

    if (tokens.front().type == TokenType::Equals)
    {
        tokens.erase(tokens.begin());
    }

    if (tokens[1].type == TokenType::Operator)
    {
        node* leftNode = getNextAssignment(tokens);

        char op = tokens.front().value[0];
        tokens.erase(tokens.begin());

        node* rightNode = getNextAssignment(tokens);

        identifierNode* variable = new identifierNode(name);
        operatorNode* operation = new operatorNode(op, leftNode, rightNode);
        assignmentNode* assign = new assignmentNode(variable, operation);

        program->executions.push_back(assign);
    }
    else
    {
        node* val = getNextAssignment(tokens);
        identifierNode* variable = new identifierNode(name);
        assignmentNode* assign = new assignmentNode(variable, val);

        program->executions.push_back(assign);
    }
}
