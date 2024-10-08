#pragma once
#include "lexer.h"
#include "tokenCollection.h"

using namespace std;

class node
{
public:
    virtual ~node(){}
    virtual string getType() const = 0;
};

class numberNode : public node
{
public:
    numberNode(int value_) : value(value_) {}
    string getType() const override
    {
        return "number";
    }
    int value;
};

class textNode : public node
{
public:
    textNode(string value_) : value(value_) {}
    string getType() const override
    {
        return "text";
    }
    string value;
};


class boolNode : public node
{
public:
    boolNode(bool value_) : value(value_) {}
    string getType() const override
    {
        return "bool";
    }
    bool value;
};

class arithmaticOperatorNode : public node
{
public:
    arithmaticOperatorNode(char op_, node* left_, node* right_) : op(op_), left(left_), right(right_) {}
    string getType() const override
    {
        return "arithmaticOperator";
    }

    char op;
    node* left;
    node* right;
};

class relationalOperatorNode : public node
{
public:
    relationalOperatorNode(string op_, node* left_, node* right_) : op(op_), left(left_), right(right_) {}
    string getType() const override
    {
        return "relationalOperator";
    }

    string op;
    node* left;
    node* right;
};

class logicOperatorNode : public node
{
public:
    logicOperatorNode(string op_) : op(op_) {}
    string getType() const override
    {
        return "logicOperator";
    }

    string op;
};

class variableNode : public node
{
public:
    variableNode(string type_, string name_) : type(type_), name(name_) {}
    string getType() const override
    {
        return "variable";
    }

    string type;
    string name;
};

class identifierNode : public node
{
public:
    identifierNode(string name_) : name(name_) {}
    string getType() const override
    {
        return "identifier";
    }

    string name;
};

class assignmentNode : public node
{
public:
    assignmentNode(identifierNode* varName_, vector<node*> assignments_) : varName(varName_), assignments(assignments_) {}
    assignmentNode(identifierNode* varName_, node* assignment_) : varName(varName_), assignments({assignment_}) {}
    string getType() const override
    {
        return "assignment";
    }

    identifierNode* varName;
    vector<node*> assignments;
};

class conditionalStatementNode : public node
{
public:
    conditionalStatementNode(string conditionType_, vector<node*> nested_) : conditionType(conditionType_), nested(nested_) {}
    string getType() const override
    {
        return "conditionalStatement";
    }

    string conditionType;
    vector<node*> nested;
};

class callNode : public node
{
public:
    callNode(string name_, string varName_) : name(name_), varName(varName_) {}
    string getType() const override
    {
        return "call";
    }

    string name;
    string varName;
};

class expressionNode : public node
{
public:
    expressionNode(node* func_) : func(func_) {}
    string getType() const override
    {
        return "expression";
    }

    node* func;
};

class programNode : public node
{
public:
    programNode() {}
    string getType() const override
    {
        return "program";
    }

    vector<node*> executions;
};

class parser
{
public:
    parser(vector<token> tokens_);
    programNode* parse();
private:
    tokenCollection tokens;
    programNode* program;
    vector<node*> parseNodes;

    void parseLine(tokenLine* line);
    void parseVariable(tokenLine* line);
    void parseCall(tokenLine* line);
    void parseConditionalStatement(tokenLine* line);
    void parseAssignment(tokenLine* line);
    void parseLogicOperator(assignmentNode* assign, tokenLine* line);
    node* getNextAssignment(tokenLine* line);
    node* getAssignValueNode(tokenLine* line);
};