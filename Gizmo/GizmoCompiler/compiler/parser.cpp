#include "parser.h"

#include <cassert>
#include <iostream>

using namespace std;

parser::parser(vector<token> tokens_): tokens(tokenCollection(&tokens_)) {}

programNode* parser::parse()
{
    program = new programNode();
    
    while (tokens.hasNextLine())
    {
        assert(tokens.hasNextLine());
        tokenLine* line = tokens.nextLine();
        parseLine(line);

        while(!parseNodes.empty())
        {
            program->executions.push_back(parseNodes[0]);
            parseNodes.erase(parseNodes.begin());
        }
    }
    return program;
}

void parser::parseLine(tokenLine* line)
{
    while (line->hasNextToken())
    {
        if (line->nextToken()->type == TokenType::Variable)
        {
            cout << "Parse Variable" << endl;
            parseVariable(line);
            continue;
        }

        if (line->nextToken()->type == TokenType::Identifier)
        {
            cout << "Parse Assignment" << endl;
            parseAssignment(line);
            continue;
        }

        if (line->nextToken()->type == TokenType::ConditionalStatement)
        {
            cout << "Parse Condition" << endl;
            parseConditionalStatement(line);
            continue;
        }

        if (line->nextToken()->type == TokenType::Call)
        {
            cout << "Parse Call" << endl;
            parseCall(line);
            continue;
        }
        
        cout << "Unhandled Token <-> " << TokenTypeStr[line->nextToken()->type] << " <-> " << line->nextToken()->value << endl;
        line->eraseNextToken();
    }

    assert(line->hasNextToken() == false);
    tokens.eraseNextLine();
}

void parser::parseVariable(tokenLine* line)
{
    string type = line->nextToken()->value;
    line->eraseNextToken();
    string name = line->nextToken()->value;
    variableNode* variable = new variableNode(type, name);
    parseNodes.push_back(variable);
}

void parser::parseCall(tokenLine* line)
{
    string name = line->nextToken()->value;
    line->eraseNextToken();
    line->eraseNextToken(); // consume (
    string varName = line->nextToken()->value;
    line->eraseNextToken();
    line->eraseNextToken(); // consume )
    callNode* call = new callNode(name, varName);

    parseNodes.push_back(call);
}

void parser::parseConditionalStatement(tokenLine* line)
{
    token conditionToken = *line->nextToken();
    
    //TODO implement conditional logic
    
    while (tokens.getLineCount() > 1 && tokens.getTokenLine(1)->getDepth() == conditionToken.depth + 1)
    {
        parseLine(tokens.getTokenLine(1));
    }
    conditionalStatementNode* condition = new conditionalStatementNode(conditionToken.value, parseNodes);
    parseNodes.clear();
    parseNodes.push_back(condition);
}

node* parser::getNextAssignment(tokenLine* line)
{
    node* n = nullptr;
    if (line->nextToken()->type == TokenType::Number)
    {
        int num = stoi(line->nextToken()->value);
        n = new numberNode(num);
    }
    else if (line->nextToken()->type == TokenType::Text)
    {
        string str = line->nextToken()->value;
        n = new textNode(str);
    }
    else if (line->nextToken()->type == TokenType::Bool)
    {
        string str = line->nextToken()->value;
        n = new boolNode(str == "true");
    }
    else if (line->nextToken()->type == TokenType::Identifier)
    {
        string str = line->nextToken()->value;
        n = new identifierNode(str);
    }
    line->eraseNextToken();
    return n;
}

node* parser::getAssignValueNode(tokenLine* line)
{
    if (line->getTokenCount() > 1)
    {
        if (line->getToken(1)->type == TokenType::RelationalOperator)
        {
            node* leftNode = getNextAssignment(line);
            string op = line->nextToken()->value;
            line->eraseNextToken();
            node* rightNode = getNextAssignment(line);

            return new relationalOperatorNode(op, leftNode, rightNode);
        }

        if (line->getToken(1)->type == TokenType::ArithmaticOperator)
        {
            node* leftNode = getNextAssignment(line);
            char op = line->nextToken()->value[0];
            line->eraseNextToken();
            node* rightNode = getNextAssignment(line);

            return new arithmaticOperatorNode(op, leftNode, rightNode);
        }
    }

    return getNextAssignment(line);
}

void parser::parseLogicOperator(assignmentNode* assign, tokenLine* line)
{
    if (line->nextToken()->type == TokenType::LogicOperator)
    {
        assign->assignments.push_back(new logicOperatorNode(line->nextToken()->value));
        line->eraseNextToken();
        assign->assignments.push_back(getAssignValueNode(line));
    }
}

void parser::parseAssignment(tokenLine* line)
{
    string name = line->nextToken()->value;
    line->eraseNextToken();

    if (line->nextToken()->type == TokenType::Equals)
    {
        line->eraseNextToken();
    }

    identifierNode* identifier = new identifierNode(name);
    assignmentNode* assign = new assignmentNode(identifier, getAssignValueNode(line));

    while (line->hasNextToken() && line->nextToken()->type == TokenType::LogicOperator)
    {
        parseLogicOperator(assign, line);
    }

    parseNodes.push_back(assign);
}
