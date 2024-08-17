#pragma once
#include "lexer.h"

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
    assignmentNode(identifierNode* varName_, node* node_) : varName(varName_), node(node_) {}
    string getType() const override
    {
        return "assignment";
    }

    identifierNode* varName;
    node* node;
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
    programNode* parse(vector<token> tokens_);
private:

    vector<token> tokens;
    programNode* program;

    void parseVariable();
    void parseCall();
    void parseAssignment();
};