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

        if (tokens.front().type == TokenType::ConditionalStatement)
        {
            parseConditionalStatement();
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

void parser::parseConditionalStatement()
{
    string type = tokens.front().value;
    tokens.erase(tokens.begin());
    tokens.erase(tokens.begin()); //erase :
    int depth = 0;
    while (tokens.front().type == TokenType::Indent)
    {
        depth++;
        tokens.erase(tokens.begin());
    }
    vector<node*> nested;
    //TODO implement this
    /*while (tokens.front())
    {
        
    }*/
    /*conditionalStatementNode* condition = new conditionalStatementNode(type, depth, nested);*/
}

node* getNextAssignment(vector<token> &tokens)
{
    node* n = nullptr;
    if (tokens.front().type == TokenType::Number)
    {
        int num = stoi(tokens.front().value);
        n = new numberNode(num);
    }
    else if (tokens.front().type == TokenType::Text)
    {
        string str = tokens.front().value;
        n = new textNode(str);
    }
    else if (tokens.front().type == TokenType::Bool)
    {
        string str = tokens.front().value;
        n = new boolNode(str == "true");
    }
    else if (tokens.front().type == TokenType::Identifier)
    {
        string str = tokens.front().value;
        n = new identifierNode(str);
    }
    tokens.erase(tokens.begin());
    return n;
}

node* parser::getAssignValueNode()
{
    if (tokens.size() > 1)
    {
        if (tokens[1].type == TokenType::RelationalOperator)
        {
            node* leftNode = getNextAssignment(tokens);
            string op = tokens.front().value;
            tokens.erase(tokens.begin());
            node* rightNode = getNextAssignment(tokens);

            return new relationalOperatorNode(op, leftNode, rightNode);
        }

        if (tokens[1].type == TokenType::ArithmaticOperator)
        {
            node* leftNode = getNextAssignment(tokens);
            char op = tokens.front().value[0];
            tokens.erase(tokens.begin());
            node* rightNode = getNextAssignment(tokens);

            return new arithmaticOperatorNode(op, leftNode, rightNode);
        }
    }

    return getNextAssignment(tokens);
}

void parser::parseLogicOperator(assignmentNode* assign)
{
    if (tokens.front().type == TokenType::LogicOperator)
    {
        assign->assignments.push_back(new logicOperatorNode(tokens.front().value));
        tokens.erase(tokens.begin());
        assign->assignments.push_back(getAssignValueNode());
    }
}

void parser::parseAssignment()
{
    string name = tokens.front().value;
    tokens.erase(tokens.begin());

    if (tokens.front().type == TokenType::NewLine)
    {
        return;
    }

    if (tokens.front().type == TokenType::Equals)
    {
        tokens.erase(tokens.begin());
    }

    identifierNode* identifier = new identifierNode(name);
    assignmentNode* assign = new assignmentNode(identifier, getAssignValueNode());;

    while (tokens.size() > 0 && tokens.front().type == TokenType::LogicOperator)
    {
        parseLogicOperator(assign);
    }

    program->executions.push_back(assign);
}
