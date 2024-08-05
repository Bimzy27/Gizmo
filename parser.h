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

class operatorNode : public node
{
public:
    operatorNode(char op_, node* left_, node* right_) : op(op_), left(left_), right(right_) {}
    string getType() const override
    {
        return "operator";
    }

    char op;
    node* left;
    node* right;
};

class programNode : public node
{
public:
    programNode(node* start_) : start(start_) {}
    programNode() {}
    string getType() const override
    {
        return "program";
    }

    node* start;
};

class parser
{
public:
    programNode* parse(vector<token> tokens);
};